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


void FInstanceHandle::HideInstance(bool bMarkRenderStateDirty )
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

		SetIsBigOffsetHidden( true );
	}
}

void FInstanceHandle::HideInstance(UHierarchicalInstancedStaticMeshComponent* Hism, int32 Id, bool bMarkRenderStateDirty)
{
	// This is already "hidden" Dont offset.
	if( IsBigOffsetHidden )
	{
		return;
	}
	
	FTransform T;
	Hism->GetInstanceTransform(HandleID, T);
	Scale = T.GetScale3D();
	T.SetScale3D(FVector(0.001));
	T.AddToTranslation( -FVector(0,0,AIM_BigOffset) );

	Hism->UpdateInstanceTransform( HandleID, T,false, bMarkRenderStateDirty,false );

	SetIsBigOffsetHidden( true );
}

void FInstanceHandle::UnHideInstance( bool bMarkRenderStateDirty )
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

	SetIsBigOffsetHidden( false );
}

void FInstanceHandle::UpdateTransform( const FTransform& T ) const
{
	if( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
		Hism->UpdateInstanceTransform( HandleID,T,false,true,false );
		Scale = T.GetScale3D();
		
		if(UInstancedStaticMeshComponent* CollisionComp = GetCollisionInstanceComponent())
		{
			CollisionComp->UpdateInstanceTransform( CollisionHandleID, T, false, false );
		}
	}
}

void FInstanceHandle::UpdateScale( const FVector& NewScale ) const
{
	if(UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get())
	{
		FTransform T;
		Hism->GetInstanceTransform( HandleID, T,false);
		T.SetScale3D( NewScale );
		Scale = NewScale;
		Hism->UpdateInstanceTransform( HandleID, T, false );
		
		if(UInstancedStaticMeshComponent* CollisionComp = GetCollisionInstanceComponent())
		{
			CollisionComp->UpdateInstanceTransform( CollisionHandleID, T, false, true );
		}
	}
}

void FInstanceHandle::SetPrimitiveDataByArray( const TArray<float> &Data, bool bMarkDirty ) const
{
	if( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
#if WITH_EDITOR
		if( Hism->NumCustomDataFloats != Data.Num() ) 
		{
			UE_LOG(LogTemp,Error,TEXT("[%s]setting primitive value outside of inital size."), *this->GetOwner()->GetName() );
			return;
		}
#endif
		Hism->SetCustomData( HandleID, Data, bMarkDirty );
	}	
}

void FInstanceHandle::SetPrimitiveDataByID( const float Value, const int32 Index, bool bMarkDirty ) const
{
	if( UHierarchicalInstancedStaticMeshComponent* Hism = InstancedStaticMeshComponent.Get() )
	{
#if WITH_EDITOR
		if( !(Hism->NumCustomDataFloats <= Index) )
		{
		 	UE_LOG(LogTemp,Error,TEXT("[%s]setting primitive value outside of inital size."), *this->GetOwner()->GetName() );
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
