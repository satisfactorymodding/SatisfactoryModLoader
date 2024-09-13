// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "InstanceData.generated.h"

class ULightweightCollisionComponent;

USTRUCT( BlueprintType )
struct ABSTRACTINSTANCE_API FInstanceData
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY( EditDefaultsOnly )
	FTransform RelativeTransform = FTransform::Identity;

	UPROPERTY( EditDefaultsOnly )
	TArray<UMaterialInterface*> OverridenMaterials;

	UPROPERTY( EditDefaultsOnly )
	TArray<float> DefaultPerInstanceCustomData;

	UPROPERTY( EditDefaultsOnly )
	bool bUseBatchedCollision = true;

	UPROPERTY( EditDefaultsOnly )
	TEnumAsByte<EComponentMobility::Type> Mobility;

	/* Useful of avoiding Z-Fighting*/
	UPROPERTY( EditDefaultsOnly )
	bool bApplyRandomOffsetOnInstance = false;

	/* Useful for fighting Z-Fighting by having a minor scale offset. */
	UPROPERTY( EditDefaultsOnly )
	bool bApplyRandomScaleOnInstancesBasedOnOrientation = false;
	
	UPROPERTY( EditDefaultsOnly, meta = ( EditCondition = bApplyRandomScaleOnInstancesBasedOnOrientation ) )
	bool bScaleByRightVector = false;
	
	/* Max range of random offset added when instanced.*/
	UPROPERTY( EditDefaultsOnly, meta = ( EditCondition = bApplyRandomOffsetOnInstance ) )
	FVector PositionOffset = FVector::ZeroVector;
	
	UPROPERTY( EditDefaultsOnly, meta = ( EditCondition = bApplyRandomScaleOnInstancesBasedOnOrientation ) )
	FVector ScaleOffset = FVector::ZeroVector;
	
	UPROPERTY( EditDefaultsOnly )
	int32 NumCustomDataFloats;

	UPROPERTY( EditDefaultsOnly )
	FName CollisionProfileName = FName("BlockAll");

	UPROPERTY( EditDefaultsOnly )
	bool bCastShadows = true;

	UPROPERTY( EditDefaultsOnly )
	bool bCastDistanceFieldShadows = true;

	UPROPERTY( EditDefaultsOnly )
	float MaxDrawDistance = -1;

	UPROPERTY( EditDefaultsOnly )
	float MaxWPODistance = 50000;

	UPROPERTY( EditDefaultsOnly )
	uint8 bWorldPositionOffsetWritesVelocity = false;
	
	/*	TODO: UNIMPLEMENTED.
	 * Do we allow the instances to be spawned after initial submit?
	 * allowing this could allow for a smoother loading experience but could also cause gameplay issues
	 * if the instance collision is needed for other gameplay elements like roads or floors. */
	UPROPERTY( EditDefaultsOnly )
	bool bAllowLazyInstance = false;

	bool operator==(const FInstanceData& Other) const
	{
		return Other.StaticMesh == this->StaticMesh && Other.OverridenMaterials == OverridenMaterials;
	}
	
public:
	UStaticMeshComponent* CreateStaticMeshComponent( UObject* Outer ) const;
};

USTRUCT( BlueprintType )
struct ABSTRACTINSTANCE_API FInstanceHandle
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool IsInstanced() const
	{
		return HandleID != INDEX_NONE;
	}

	TArray<float> GetCustomData()const
	{
		return CustomData;
	}

	FORCEINLINE UHierarchicalInstancedStaticMeshComponent* GetInstanceComponent() const
	{
		return InstancedStaticMeshComponent.Get();
	}
	
	FORCEINLINE UInstancedStaticMeshComponent* GetCollisionInstanceComponent() const
	{
		return BatchCollisionMeshComponent.Get();
	}

	FORCEINLINE uint32 GetHandleID() const
	{
		return HandleID;
	}

	FORCEINLINE bool IsValid() const
	{
		return true; // TODO
		//return InstancedStaticMeshComponent.IsValid() && BatchCollisionMeshComponent.IsValid() && IsInstanced() && CollisionHandleID != INDEX_NONE;
	}

	FORCEINLINE void SetInstanceVisibility(bool bNewState, bool bMarkRenderStateDirty = true)
	{
		if (bNewState)
		{
			UnHideInstance(bMarkRenderStateDirty);
		}
		else
		{
			HideInstance(bMarkRenderStateDirty);
		}
	}

	FORCEINLINE TSubclassOf< AActor > GetInstancedBasedOnClass() { return BuildableClass; }
	
	void HideInstance( bool bMarkRenderStateDirty = true );
	void HideInstance( UHierarchicalInstancedStaticMeshComponent* Hism, int32 Id, bool bMarkRenderStateDirty = true );

	void UnHideInstance(bool bMarkRenderStateDirty = true);
	
	void UpdateTransform(const FTransform& T) const;
	void UpdateScale(const FVector& NewScale) const;

	FORCEINLINE void SetIsBigOffsetHidden( bool newIsBigOffsetHidden ) { IsBigOffsetHidden = newIsBigOffsetHidden; }

	FORCEINLINE void SetOwner( AActor* owner )
	{
		Owner = owner;
	}
	
	FORCEINLINE AActor* GetOwner() const
	{
		return Owner.Get();
	}

	FORCEINLINE TWeakObjectPtr<AActor> GetWeakOwner() const
	{
		return Owner;
	}
	
	template<typename T>
	FORCEINLINE T* GetOwner() const
	{
		return Cast<T>(Owner.Get() );
	}

	void SetPrimitiveDataByArray( const TArray<float> &Data, bool bMarkDirty ) const;
	void SetPrimitiveDataByID( const float Value, const int32 Index, bool bMarkDirty ) const;
	int32 GetNumPrimitiveData() const { return NumPrimitiveFloatData; }
private:
	// Instance id.
	uint32 HandleID = INDEX_NONE;

	uint32 CollisionHandleID = INDEX_NONE;

	bool IsBigOffsetHidden = false;

	UPROPERTY(VisibleInstanceOnly)
	TWeakObjectPtr<AActor> Owner;
	
	/* Pointer to instance component. */
	UPROPERTY(VisibleInstanceOnly)
	TWeakObjectPtr< UHierarchicalInstancedStaticMeshComponent > InstancedStaticMeshComponent;
	
	UPROPERTY(VisibleInstanceOnly)
	TWeakObjectPtr< UInstancedStaticMeshComponent > BatchCollisionMeshComponent;

	// Transient data, flushed after adding to the system.
	TArray<float> CustomData;

	int32 NumPrimitiveFloatData;
	
	UPROPERTY()
	TSubclassOf< class AActor > BuildableClass;
	
	/* Used for hiding */
	mutable FVector Scale;
	
public:
	
	FInstanceHandle( uint32 inIndex, uint32 inCollisionID, AActor* inOwner, UHierarchicalInstancedStaticMeshComponent* inInstancedStaticMeshComponent, UInstancedStaticMeshComponent* inBatchCollision )
	{
		HandleID = inIndex;
		CollisionHandleID = inCollisionID;
		Owner = inOwner;
		InstancedStaticMeshComponent = inInstancedStaticMeshComponent;
		BatchCollisionMeshComponent = inBatchCollision;
		
		check( inBatchCollision );
		check( inInstancedStaticMeshComponent );
		check( inOwner );
	}
	
	FInstanceHandle()
	{
		HandleID = INDEX_NONE;
		CollisionHandleID = INDEX_NONE;
	}

	friend class AAbstractInstanceManager; 
};

UCLASS( EditInlineNew )
class ABSTRACTINSTANCE_API UAbstractInstanceDataObject : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY( EditDefaultsOnly )
	TArray<FInstanceData> Instances;

public:
	TArray<FInstanceData> GetInstanceData() const
	{
		return Instances;
	}
	
	FORCEINLINE bool HasValidInstanceData() const
	{
		return Instances.Num() > 0;
	}

#if WITH_EDITOR
	static void ConvertActorWithStaticMeshComponentsToAbstractData(AActor* Source);

	void AddInstance(FInstanceData& InData);
#endif
};