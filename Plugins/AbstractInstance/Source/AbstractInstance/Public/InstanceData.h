// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AkGeometryComponent.h"
#include "AkInstancedGeometryComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "InstanceData.generated.h"

class UAkInstancedGeometryComponent;
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
	TEnumAsByte<EComponentMobility::Type> Mobility{EComponentMobility::Static};

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
	int32 NumCustomDataFloats{0};

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

	UPROPERTY( EditDefaultsOnly, Category = "Audio Geometry" )
	bool bUseAkGeometry = false;

	/** If specified (greater than 0) then a new mesh component will be created after exceeding this number of instances per component */
	UPROPERTY( EditDefaultsOnly )
	int32 MaxMeshInstancePerComponent = 0;

	UPROPERTY( EditDefaultsOnly, Category = "Audio Geometry", DisplayName = "Physics geometry that will be send to audio", meta = ( EditCondition = "bUseAkGeometry" ) )
	AkInstancedMeshType MeshType = AkInstancedMeshType::BoundingBox;
	
	/** Override the acoustic properties of the collision mesh.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Geometry", DisplayName = "Acoustic Properties Override", meta = (EditCondition = "bUseAkGeometry"))
	FAkGeometrySurfaceOverride CollisionMeshSurfaceOverride;

	FInstanceData()
	{
		CollisionMeshSurfaceOverride.OcclusionValue = 0.8f;
	}
	
	bool operator==(const FInstanceData& Other) const
	{
		return Other.StaticMesh == this->StaticMesh && Other.OverridenMaterials == OverridenMaterials;
	}
	
public:
	UStaticMeshComponent* CreateStaticMeshComponent( UObject* Outer ) const;
};

/** Base class that can be used to store metadata on instance handles */
struct FInstanceHandleMetadata
{
	virtual ~FInstanceHandleMetadata() = default;
};

/**
 * A handle identifying a single abstract instance created by the Abstract Instance Manager
 * Handle can be used to resolve the actor which has created the instance, retrieve the information about the instance, and manipulate it
 * Handles capture the state of the instance at the time the handle is resolved using functions such as ResolveHit or ResolveOverlap
 * Handles do not hold ownership of the abstract instances and provide read-only access to the instance
 */
USTRUCT(BlueprintType)
struct ABSTRACTINSTANCE_API FInstanceHandle
{
	GENERATED_BODY()
	
	/** Returns true if this instance handle still points to a valid instance */
	FORCEINLINE bool IsInstanced() const
	{
		return HandleID != INDEX_NONE;
	}

	/** Returns the ID of this instance in the instance manager. Returns INDEX_NONE if the instance is not valid */
	FORCEINLINE uint32 GetHandleID() const
	{
		return HandleID;
	}

	/** Returns the index of the component this handle is managed by. This is utilized by the abstract instance manager when performing split instance groups */
	FORCEINLINE int32 GetMeshComponentIndex() const
	{
		return MeshComponentIndex;
	}

	/** The ID of this handle in its collision component (like the HandleID but for its physics representation) */
	FORCEINLINE uint32 GetCollisionHandleId() const
	{
		return CollisionHandleID;	
	}

	/** Returns the custom data currently set on the instance */
	const TArray<float>& GetCustomData() const
	{
		return CustomData;
	}

	/** Returns current instance transform in world space. Instance must be valid */
	FTransform GetWorldTransform() const;
	
	/** Returns the actor owning this abstract instance */
	FORCEINLINE AActor* GetOwner() const
	{
		return Owner.Get();
	}

	/** Returns the actor owning this abstract instance */
	FORCEINLINE TWeakObjectPtr<AActor> GetWeakOwner() const
	{
		return Owner;
	}
	
	/** Returns the actor owning this abstract instance cast to a provided type */
	template<typename T>
	FORCEINLINE T* GetOwner() const
	{
		return Cast<T>(Owner.Get() );
	}

	FORCEINLINE int32 GetNumPrimitiveData() const { return NumPrimitiveFloatData; }

	FORCEINLINE const UHierarchicalInstancedStaticMeshComponent* GetInstanceComponent() const
	{
		return InstancedStaticMeshComponent.Get();
	}
	FORCEINLINE const UInstancedStaticMeshComponent* GetCollisionInstanceComponent() const
	{
		return BatchCollisionMeshComponent.Get();
	}
protected:
	friend class AAbstractInstanceManager;
	friend struct FInstanceComponentData;
	
	// Instance id.
	uint32 HandleID = 0;
	// Potentially a tracking index for a manager that contains multiple vistual mesh components for the same instance data
	int32 MeshComponentIndex = INDEX_NONE;
	// The ID of the handle in its collision comp (if using batched collision)
	uint32 CollisionHandleID = 0;

	bool IsBigOffsetHidden = false;

	TWeakObjectPtr<AActor> Owner;
	
	/* Pointer to instance component. */
	TWeakObjectPtr< UHierarchicalInstancedStaticMeshComponent > InstancedStaticMeshComponent;
	TWeakObjectPtr< UInstancedStaticMeshComponent > BatchCollisionMeshComponent;
	TWeakObjectPtr< UAkInstancedGeometryComponent > AkInstancedGeometryComponent;

	// Transient data, flushed after adding to the system.
	TArray<float> CustomData;
	int32 NumPrimitiveFloatData{};
	
	/* Used for hiding */
	mutable FVector Scale{};
public:
	/** Metadata set on the instance. Can be used to store additional data associated with the instance handle */
	TSharedPtr<FInstanceHandleMetadata> Metadata;
};
	
/**
 * A handle identifying a single abstract instance created by the Abstract Instance Manager
 * Handle can be used to resolve the actor which has created the instance, retrieve the information about the instance, and manipulate it
 * Handles are created by calling AAbstractInstanceManager::SetInstanced, and removed by calling AAbstractInstanceManager::RemoveInstance(s)
 * All instances must be removed before or during EndPlay to avoid memory leaks when changing levels!!!
 *
 * The creator of the FInstanceHandle has the exclusive and full ownership of the instance handle's lifetime, and it is the owner's responsibility to free the instance
 * once the actor is destroyed or the instance is no longer necessary.
 */
struct ABSTRACTINSTANCE_API FInstanceOwnershipHandle : FInstanceHandle, TSharedFromThis<FInstanceOwnershipHandle, ESPMode::NotThreadSafe>
{
	/** Updated local space transform of the instance */
	void SetLocalTransform(const FTransform& NewLocalTransform) const;
	/** Updates the scale of the instance in local space */
	void SetLocalScale(const FVector& NewLocalState) const;

	/** Hides or unhides the instance */
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
		
	/** Hides or un-hides this instance */
	void HideInstance( bool bMarkRenderStateDirty = true );
	void UnHideInstance(bool bMarkRenderStateDirty = true);

	/** Updates primitive data set on this abstract instance */
	void SetPrimitiveDataByArray( const TArray<float>& Data, bool bMarkDirty ) const;
	void SetPrimitiveDataByID( float Value, const int32 Index, bool bMarkDirty ) const;
	
	/** Allows changing which actor the instance belongs to. This is a fairly low level function that should be used with caution */
	FORCEINLINE void SetOwner( AActor* owner )
	{
		Owner = owner;
	}
	
	FORCEINLINE UHierarchicalInstancedStaticMeshComponent* GetInstanceComponent() const
	{
		return InstancedStaticMeshComponent.Get();
	}

	FORCEINLINE UInstancedStaticMeshComponent* GetCollisionInstanceComponent() const
	{
		return BatchCollisionMeshComponent.Get();
	}

	/** Resets this instance handle to no longer point to any instance */
	void ResetHandle();
protected:
	friend class AAbstractInstanceManager; 
	
	/** Changes whenever the instance is considered hidden. This is for internal use by instance manager only! */
	FORCEINLINE void Internal_SetIsBigOffsetHidden( bool newIsBigOffsetHidden )
	{
		IsBigOffsetHidden = newIsBigOffsetHidden;
	}
};

// We do not need thread safety because handles are only supposed to be modified from the game thread. This avoids the overhead of using atomics
using FInstanceOwnerHandlePtr = TSharedPtr<FInstanceOwnershipHandle, ESPMode::NotThreadSafe>;
// Read-only version of the FInstanceOwnerHandlePtr - to be passed to the external code
using FInstanceHandlePtr = TSharedPtr<FInstanceHandle, ESPMode::NotThreadSafe>;

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