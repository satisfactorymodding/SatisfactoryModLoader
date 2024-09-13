// Copyright Ben de Hullu & Coffee Stain Studios 2022. All Rights Reserved.

#include "InstancedSplineMeshComponent.h"
#include "SceneInterface.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"

FSplineInstancedStaticMeshSceneProxy::FSplineInstancedStaticMeshSceneProxy(UInstancedStaticMeshComponent* InComponent, ERHIFeatureLevel::Type InFeatureLevel)
	: FInstancedStaticMeshSceneProxy(InComponent,InFeatureLevel)
{
	bHasPerInstanceLocalBounds = true;
	
	// Force update bounds.
	if (UseGPUScene(GetScene().GetShaderPlatform(), GetScene().GetFeatureLevel()))
	{
		if (auto Parent = Cast< UInstancedSplineMeshComponent>(InComponent))
		{
			const TArray<int32>& InstanceReorderTable = InComponent->InstanceReorderTable;
			const FVector TranslatedSpaceOffset = -InComponent->GetTranslatedInstanceSpaceOrigin();
			InstanceLocalBounds.Empty(InComponent->GetInstanceCount());
			
			for (int32 InstanceIndex = 0; InstanceIndex < InComponent->GetInstanceCount(); ++InstanceIndex)
			{
				const int32 RenderInstanceIndex = InstanceReorderTable.IsValidIndex(InstanceIndex) ? InstanceReorderTable[InstanceIndex] : InstanceIndex;
				const auto& SplineSegment = Parent->SplineInstances[RenderInstanceIndex];

				// TODO spline polish.
				InstanceLocalBounds.Add( StaticMesh->GetBounds().GetBox().ExpandBy(10));
			}
		}
	}
}

UInstancedSplineMeshComponent::UInstancedSplineMeshComponent()
{
	// Setup defaults.
	/*	0,1,2.	Start XYZ		// TODO make this based on the instance pos instead.
	 *	3,4,5.	Start Tangent
	 *	6,7,8	End Pos
	 *	9,10,11	End Tangent
	 *	12		Length			// TODO read this from the X scale instead.
	 *	13						// TODO make this a static bool in the shader instead. */
	
	bRuntimeOnly = false;

#if ENGINE_MAJOR_VERSION == 5
	/* force disable nanite for now. */
	bDisallowNanite = true;
#endif

	NumCustomDataFloats = 3 * 4;
}

void UInstancedSplineMeshComponent::BeginPlay()
{	
	Super::BeginPlay();
	
}

FBoxSphereBounds UInstancedSplineMeshComponent::CalcBounds(const FTransform& BoundTransform) const
{
	// Compute bounding box, based on `USplineMeshComponent::CalcBounds`
	const bool IsInvalid = !GetStaticMesh() || GetInstanceCount() == 0;
	if ( IsInvalid )
	{
		return FBoxSphereBounds(FBox(ForceInit));
	}

	// Fist instance.
	FBoxSphereBounds RenderBounds = CalculateInstanceBounds(
		BoundTransform,
		GetInstanceStartPos(0),
		GetInstanceStartTangent(0),
		GetInstanceEndPos(0),
		GetInstanceEndTangent(0));

	for ( int32 i = 1; i < GetInstanceCount(); i++ )
	{
		RenderBounds = RenderBounds + CalculateInstanceBounds(
			BoundTransform,
			GetInstanceStartPos(i),
			GetInstanceStartTangent(i),
			GetInstanceEndPos(i),
			GetInstanceEndTangent(i) );
	}

	RenderBounds.BoxExtent *= 1.25; // 25% upscale?
	return RenderBounds;
}

FPrimitiveSceneProxy* UInstancedSplineMeshComponent::CreateSceneProxy()
{
	static const auto NaniteProxyRenderModeVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Nanite.ProxyRenderMode"));
	const int32 NaniteProxyRenderMode = (NaniteProxyRenderModeVar != nullptr) ? (NaniteProxyRenderModeVar->GetInt() != 0) : 0;

	LLM_SCOPE(ELLMTag::InstancedMesh);

	ProxySize = 0;

	// Verify that the mesh is valid before using it.
	const bool bMeshIsValid =
		// make sure we have instances
		PerInstanceSMData.Num() > 0 &&
		// make sure we have an actual static mesh
		GetStaticMesh() &&
		GetStaticMesh()->IsCompiling() == false &&
		GetStaticMesh()->HasValidRenderData();

	if (bMeshIsValid)
	{
		check(InstancingRandomSeed != 0);
		
		// if instance data was modified, update GPU copy
		// generally happens only in editor 
		if (InstanceUpdateCmdBuffer.NumTotalCommands() != 0)
		{
			FlushInstanceUpdateCommands(true);
		}
		
		ProxySize = PerInstanceRenderData->ResourceSize;

		// Is Nanite supported, and is there built Nanite data for this static mesh?
		if (ShouldCreateNaniteProxy())
		{
			checkf(false,TEXT("Not implemented"));
			//return ::new Nanite::FSceneProxy(this);
		}
		// If we didn't get a proxy, but Nanite was enabled on the asset when it was built, evaluate proxy creation
		else if (GetStaticMesh()->HasValidNaniteData() && NaniteProxyRenderMode != 0)
		{
			// Do not render Nanite proxy
			return nullptr;
		}
		else
		{
			return ::new FSplineInstancedStaticMeshSceneProxy(this, GetWorld()->FeatureLevel);
		}
	}
	
	return nullptr;
}

FBoxSphereBounds UInstancedSplineMeshComponent::CalculateInstanceBounds(const FTransform& LocalToWorld, const FVector& Start, const FVector& StartTangent, const FVector& End, const FVector& EndTangent) const
{
	if (!GetStaticMesh())
	{
		return FBoxSphereBounds(FBox(ForceInit));
	}
	
	float MinT = 0.0f;
	float MaxT = 1.0f;

	const FBoxSphereBounds MeshBounds = GetStaticMesh()->GetBounds();
	
	const FVector AxisMask = GetAxisMask(ForwardAxis);
	const FVector FlattenedMeshOrigin = MeshBounds.Origin * AxisMask;
	const FVector FlattenedMeshExtent = MeshBounds.BoxExtent * AxisMask;
	const FBox MeshBoundingBox = FBox(FlattenedMeshOrigin - FlattenedMeshExtent, FlattenedMeshOrigin + FlattenedMeshExtent);
	
	FBox BoundingBox(ForceInit);
	BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(MinT, Start, StartTangent, End, EndTangent));
	BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(MaxT, Start, StartTangent, End, EndTangent));

	
	// Work out coefficients of the cubic spline derivative equation dx/dt
	const FVector A = 6.0f * Start + 3.0f * StartTangent + 3.0f * EndTangent - 6.0f * End;
	const FVector B = -6.0f * Start - 4.0f * StartTangent - 2.0f * EndTangent + 6.0f * End;
	const FVector C = StartTangent;

	// Minima/maxima happen where dx/dt == 0, calculate t values
	const FVector Discriminant = B * B - 4.0f * A * C;

	// Work out minima/maxima component-by-component.
	// Negative discriminant means no solution; A == 0 implies coincident start/end points
	if (Discriminant.X > 0.0f && !FMath::IsNearlyZero(A.X))
	{
		const float SqrtDiscriminant = FMath::Sqrt(Discriminant.X);
		const float Denominator = 0.5f / A.X;
		const float T0 = (-B.X + SqrtDiscriminant) * Denominator;
		const float T1 = (-B.X - SqrtDiscriminant) * Denominator;

		if (T0 >= MinT && T0 <= MaxT)
		{
			BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(T0, Start, StartTangent, End, EndTangent));
		}

		if (T1 >= MinT && T1 <= MaxT)
		{
			BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(T1, Start, StartTangent, End, EndTangent));
		}
	}

	if (Discriminant.Y > 0.0f && !FMath::IsNearlyZero(A.Y))
	{
		const float SqrtDiscriminant = FMath::Sqrt(Discriminant.Y);
		const float Denominator = 0.5f / A.Y;
		const float T0 = (-B.Y + SqrtDiscriminant) * Denominator;
		const float T1 = (-B.Y - SqrtDiscriminant) * Denominator;

		if (T0 >= MinT && T0 <= MaxT)
		{
			BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(T0, Start, StartTangent, End, EndTangent));
		}

		if (T1 >= MinT && T1 <= MaxT)
		{
			BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(T1, Start, StartTangent, End, EndTangent));
		}
	}

	if (Discriminant.Z > 0.0f && !FMath::IsNearlyZero(A.Z))
	{
		const float SqrtDiscriminant = FMath::Sqrt(Discriminant.Z);
		const float Denominator = 0.5f / A.Z;
		const float T0 = (-B.Z + SqrtDiscriminant) * Denominator;
		const float T1 = (-B.Z - SqrtDiscriminant) * Denominator;

		if (T0 >= MinT && T0 <= MaxT)
		{
			BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(T0, Start, StartTangent, End, EndTangent));
		}

		if (T1 >= MinT && T1 <= MaxT)
		{
			BoundingBox += MeshBoundingBox.TransformBy(CalcTransformInstance(T1, Start, StartTangent, End, EndTangent));
		}
	}

	return FBoxSphereBounds(BoundingBox.TransformBy(LocalToWorld));
}

FVector UInstancedSplineMeshComponent::GetInstanceStartPos(int32 Instance) const
{
	return SplineInstances[Instance].StartPos;
}

FVector UInstancedSplineMeshComponent::GetInstanceStartTangent(int32 Instance) const
{
	return SplineInstances[Instance].StartTangent;
}

FVector UInstancedSplineMeshComponent::GetInstanceEndPos(int32 Instance) const
{
	return SplineInstances[Instance].EndPos;
}

FVector UInstancedSplineMeshComponent::GetInstanceEndTangent(int32 Instance) const
{
	return SplineInstances[Instance].EndTangent;
}

static FVector SplineEvalPos(const FVector& StartPos, const FVector& StartTangent, const FVector& EndPos, const FVector& EndTangent, float A)
{
	const float A2 = A * A;
	const float A3 = A2 * A;

	return (((2 * A3) - (3 * A2) + 1) * StartPos) + ((A3 - (2 * A2) + A) * StartTangent) + ((A3 - A2) * EndTangent) + (((-2 * A3) + (3 * A2)) * EndPos);
}

static FVector SplineEvalDir(const FVector& StartPos, const FVector& StartTangent, const FVector& EndPos, const FVector& EndTangent, float A)
{
	const FVector C = (6 * StartPos) + (3 * StartTangent) + (3 * EndTangent) - (6 * EndPos);
	const FVector D = (-6 * StartPos) - (4 * StartTangent) - (2 * EndTangent) + (6 * EndPos);
	const FVector E = StartTangent;

	const float A2 = A * A;

	return ((C * A2) + (D * A) + E).GetSafeNormal();
}

FTransform UInstancedSplineMeshComponent::CalcTransformInstance( const float Alpha, const FVector& StartPos, const FVector& StartTangent, const FVector& EndPos, const FVector& EndTangent ) const
{
	// Then find the point and direction of the spline at this point along
	FVector SplinePos = SplineEvalPos(StartPos, StartTangent, EndPos, EndTangent, Alpha);
	const FVector SplineDir = SplineEvalDir(StartPos, StartTangent, EndPos, EndTangent, Alpha);

	// Find base frenet frame
	const FVector BaseXVec = (SplineUpDirection ^ SplineDir).GetSafeNormal();
	const FVector BaseYVec = (SplineDir ^ BaseXVec).GetSafeNormal();
	
	// Build overall transform
	FTransform SliceTransform;
	switch (ForwardAxis)
	{
	case ESplineMeshAxis::X:
		SliceTransform = FTransform(SplineDir, BaseXVec, BaseYVec, SplinePos);
		break;
	case ESplineMeshAxis::Y:
		SliceTransform = FTransform(BaseYVec, SplineDir, BaseXVec, SplinePos);
		break;
	case ESplineMeshAxis::Z:
		SliceTransform = FTransform(BaseXVec, BaseYVec, SplineDir, SplinePos);
		break;
	default:
		check(0);
		break;
	}

	return SliceTransform;
}

#if ENGINE_MAJOR_VERSION == 4
int32 UInstancedSplineMeshComponent::AddInstance(const FTransform& InstanceTransform)
#else
int32 UInstancedSplineMeshComponent::AddInstance(const FTransform& InstanceTransform, bool bWorldSpace)
#endif
{
	checkf( bValidAddFence, TEXT("Don't call AddInstance(const FTransform& InstanceTransform) on spline mesh components, call AddSplineInstance instead."));
	
	return Super::AddInstance(InstanceTransform);
}

void UInstancedSplineMeshComponent::ClearInstances()
{
	Super::ClearInstances();
	
	SplineInstances.Empty();
}

int32 UInstancedSplineMeshComponent::AddSplineInstance( const FVector StartPosition, const FVector StartTangent, const FVector EndPosition, const FVector EndTangent, bool bScaleLength, bool bRotateMesh, const bool bMarkDirty)
{
	// Fence to ensure we add the instance in the correct way.
	SetAddFenceValid();

	check(GetStaticMesh())
	const float MeshLength = GetStaticMesh()->GetBounds().BoxExtent.X * 2;
	
	// calculate direction
	const float InstanceScale = bScaleLength ? FVector::Distance(StartPosition,EndPosition) / MeshLength : 1;
	const FVector Dir = (EndPosition - StartPosition).GetSafeNormal();
	const FQuat Rotation =  bRotateMesh ? FRotationMatrix::MakeFromXZ(Dir,SplineUpDirection).ToQuat() : FQuat::Identity;
	const FTransform InstanceLocalTransform = FTransform( Rotation,StartPosition, FVector(InstanceScale,1,1) );
	
	// Instance location on spline.
	const int32 Index = AddInstance( InstanceLocalTransform );

	SetupPerInstancePrimitiveData( Index,StartPosition,StartTangent,EndPosition,EndTangent, InstanceScale );
	
	if ( bMarkDirty )
	{
		MarkRenderStateDirty();
	}
	
	// Invalidate the fence again.
	InvalidateAddFence();	
	
	// add instance to array
	if (!bRuntimeOnly)
	{
		SplineInstances.Add( FSplineMeshInstanceEntry(StartPosition, StartTangent, EndPosition, EndTangent) );
	}

	return Index;
}

#if WITH_EDITOR
void UInstancedSplineMeshComponent::DrawDebugBounds()
{
	FBoxSphereBounds bounds = CalcBounds(GetOwner()->GetTransform());
	DrawDebugBox(GetWorld(),bounds.Origin,bounds.BoxExtent,FColor::Red,true,10.f,1,5.f);
}
#endif

void UInstancedSplineMeshComponent::SetupPerInstancePrimitiveData(const int32 InstanceIndex, const FVector& StartPosition, const FVector StartTangent, const FVector& EndPosition, const FVector& EndTangent, const float& InstanceScale)
{
	const int32 StartPosIds[ 3 ] = {
		DefaultSplineShaderBindSettings.StartPositionPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 0,
		DefaultSplineShaderBindSettings.StartPositionPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 1,
		DefaultSplineShaderBindSettings.StartPositionPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 2 };

	const int32 StartTangentIds[ 3 ] = {
		DefaultSplineShaderBindSettings.StartTangentPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 0,
		DefaultSplineShaderBindSettings.StartTangentPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 1,
		DefaultSplineShaderBindSettings.StartTangentPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 2 };

	const int32 EndPosIds[ 3 ] = {
		DefaultSplineShaderBindSettings.EndPositionPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 0,
		DefaultSplineShaderBindSettings.EndPositionPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 1,
		DefaultSplineShaderBindSettings.EndPositionPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 2 };

	const int32 EndTangentIds[ 3 ] = {
		DefaultSplineShaderBindSettings.EndTangentPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 0,
		DefaultSplineShaderBindSettings.EndTangentPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 1,
		DefaultSplineShaderBindSettings.EndTangentPrimitiveDataStartIndex + NumPerInstancePrimitiveDataCountOffset + 2 };

	// Start pos
	
	SetCustomDataValue( InstanceIndex,StartPosIds[0], StartPosition.X,false);
	SetCustomDataValue( InstanceIndex,StartPosIds[1], StartPosition.Y,false);
	SetCustomDataValue( InstanceIndex,StartPosIds[2], StartPosition.Z,false);

	// Start tangent
	SetCustomDataValue( InstanceIndex,StartTangentIds[0], StartTangent.X,false);
	SetCustomDataValue( InstanceIndex,StartTangentIds[1], StartTangent.Y,false);
	SetCustomDataValue( InstanceIndex,StartTangentIds[2], StartTangent.Z,false);

	// End pos
	SetCustomDataValue( InstanceIndex,EndPosIds[0], EndPosition.X,false);
	SetCustomDataValue( InstanceIndex,EndPosIds[1], EndPosition.Y,false);
	SetCustomDataValue( InstanceIndex,EndPosIds[2], EndPosition.Z,false);

	// End tangent
	SetCustomDataValue( InstanceIndex,EndTangentIds[0], EndTangent.X,false);
	SetCustomDataValue( InstanceIndex,EndTangentIds[1], EndTangent.Y,false);
	SetCustomDataValue( InstanceIndex,EndTangentIds[2], EndTangent.Z,false);

	// Set instance length.
	if (DefaultSplineShaderBindSettings.InstanceScaleIndex != INDEX_NONE)
	{
		SetCustomDataValue( InstanceIndex,DefaultSplineShaderBindSettings.InstanceScaleIndex + NumPerInstancePrimitiveDataCountOffset, InstanceScale,false);
	}
}

FVector UInstancedSplineMeshComponent::GetAxisMask(ESplineMeshAxis::Type InAxis)
{
	switch (InAxis)
	{
	case ESplineMeshAxis::X:
		return FVector(0, 1, 1);
	case ESplineMeshAxis::Y:
		return FVector(1, 0, 1);
	case ESplineMeshAxis::Z:
		return FVector(1, 1, 0);
	default:
		check(0);
		return FVector::ZeroVector;
	}
}