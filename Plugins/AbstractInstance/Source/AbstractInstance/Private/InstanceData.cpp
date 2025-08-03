// Copyright Ben de Hullu. All Rights Reserved.

#include "InstanceData.h"
#include "AbstractInstance.h"
#include "Engine/InstancedStaticMesh.h"
#include "Components/InstancedStaticMeshComponent.h"

UStaticMeshComponent* FInstanceData::CreateStaticMeshComponent( UObject* Outer ) const
{
	UStaticMeshComponent* OutComponent = NewObject< UStaticMeshComponent >( Outer );
	OutComponent->OverrideMaterials = OverridenMaterials;
	OutComponent->SetStaticMesh( StaticMesh );
	OutComponent->SetWorldTransform(  RelativeTransform );

	return OutComponent;
}

void FInstanceOwnershipHandle::HideInstance(bool bMarkRenderStateDirty )
{
	// This is already "hidden" Dont offset.
	if( IsBigOffsetHidden )
	{
		return;
	}
	
	if ( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
		FTransform T;
		Hism->GetInstanceTransform(HandleID, T, false);
		Scale = T.GetScale3D();
		T.SetScale3D(FVector(0.001));
		T.AddToTranslation( -FVector(0,0,AIM_BigOffset) );

		Hism->UpdateInstanceTransform( HandleID, T,false, bMarkRenderStateDirty,false );
		Internal_SetIsBigOffsetHidden( true );
	}
}

void FInstanceOwnershipHandle::UnHideInstance( bool bMarkRenderStateDirty )
{
	// This isn't "hidden" Dont offset.
	if( !IsBigOffsetHidden )
	{
		return;
	}
	
	if ( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
		FTransform T;
		Hism->GetInstanceTransform( HandleID, T );
		T.SetScale3D(Scale);
		T.AddToTranslation( FVector(0,0,AIM_BigOffset) );
		Hism->UpdateInstanceTransform(HandleID, T, false, bMarkRenderStateDirty, false);
	}
	Internal_SetIsBigOffsetHidden( false );
}

void FInstanceOwnershipHandle::ResetHandle()
{
	HandleID = INDEX_NONE;
	CollisionHandleID = INDEX_NONE;
	Owner.Reset();
	InstancedStaticMeshComponent.Reset();
	BatchCollisionMeshComponent.Reset();
}

FTransform FInstanceHandle::GetWorldTransform() const
{
	if( const UHierarchicalInstancedStaticMeshComponent* MeshComponent = InstancedStaticMeshComponent.Get() )
	{
		FTransform InstanceRelativeTransform;
		if ( MeshComponent->GetInstanceTransform( GetHandleID(), InstanceRelativeTransform, false ) )
		{
			// Adjust scale of the transform to avoid returning wrong transform when the instance is hidden, and remove the offset
			if (IsBigOffsetHidden)
			{
				InstanceRelativeTransform.SetScale3D( Scale );
				InstanceRelativeTransform.AddToTranslation( FVector( 0.0f, 0.0f, AIM_BigOffset ) );
			}
			// Now that we have a correct local space instance transform, convert it to world space
			return InstanceRelativeTransform * MeshComponent->GetComponentTransform();
		}
	}
	return FTransform::Identity;
}

void FInstanceOwnershipHandle::SetLocalTransform( const FTransform& NewLocalTransform ) const
{
	if( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
		Hism->UpdateInstanceTransform( HandleID, NewLocalTransform, false, true, false );
		Scale = NewLocalTransform.GetScale3D();
		
		if(UInstancedStaticMeshComponent* CollisionComp = GetCollisionInstanceComponent())
		{
			CollisionComp->UpdateInstanceTransform( CollisionHandleID, NewLocalTransform, false, false );
		}
	}
}

void FInstanceOwnershipHandle::SetLocalScale( const FVector& NewLocalState ) const
{
	if(UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get())
	{
		FTransform T;
		Hism->GetInstanceTransform( HandleID, T,false );
		T.SetScale3D( NewLocalState );
		Scale = NewLocalState;
		Hism->UpdateInstanceTransform( HandleID, T, false );
		
		if(UInstancedStaticMeshComponent* CollisionComp = GetCollisionInstanceComponent())
		{
			CollisionComp->UpdateInstanceTransform( CollisionHandleID, T, false, true );
		}
	}
}

void FInstanceOwnershipHandle::SetPrimitiveDataByArray( const TArray<float> &Data, bool bMarkDirty ) const
{
	if( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
#if WITH_EDITOR
		if( Hism->NumCustomDataFloats != Data.Num() ) 
		{
			UE_LOG(LogTemp, Error, TEXT("[%s] Setting primitive value outside of initial size."), *GetOwner()->GetName() );
			return;
		}
#endif
		Hism->SetCustomData( HandleID, Data, bMarkDirty );
	}	
}

void FInstanceOwnershipHandle::SetPrimitiveDataByID( const float Value, const int32 Index, bool bMarkDirty ) const
{
	if( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
#if WITH_EDITOR
		if( Hism->NumCustomDataFloats > Index )
		{
		 	UE_LOG(LogTemp, Error, TEXT("[%s] Setting primitive value outside of initial size."), *GetOwner()->GetName() );
		 	return;
		}
#endif
		Hism->SetCustomDataValue( HandleID,Index,Value, bMarkDirty );
	}
}

#if WITH_EDITOR
void UAbstractInstanceDataObject::ConvertActorWithStaticMeshComponentsToAbstractData( AActor* Source )
{
}

void UAbstractInstanceDataObject::AddInstance( FInstanceData& InData )
{
	Instances.AddUnique( InData );
}
#endif
