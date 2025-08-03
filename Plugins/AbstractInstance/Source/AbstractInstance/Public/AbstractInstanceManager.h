// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AbstractInstance.h"
#include "CoreMinimal.h"
#include "InstanceData.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "AbstractInstanceManager.generated.h"

struct FInstanceData;
struct FInstanceHandle;
class UHierarchicalInstancedStaticMeshComponent;
class UInstancedStaticMeshComponent;
class UAkInstancedGeometryComponent;

#define GetLocationFromT(T)			T.GetLocation()
#define GetRightVectorFromT(T)		T.GetRotation().GetRightVector()
#define GetUpVectorFromT(T)			T.GetRotation().GetUpVector()
#define GetForwardVectorFromT(T)	T.GetRotation().GetForwardVector()

USTRUCT()
struct ABSTRACTINSTANCE_API FInstanceIDAndIndex
{
	GENERATED_BODY()

	UPROPERTY()
	int32 InstanceID = INDEX_NONE;
	UPROPERTY()
	int32 ComponentIndex = INDEX_NONE;
	
};

USTRUCT()
struct ABSTRACTINSTANCE_API FInstanceAdditionData
{
	GENERATED_BODY()

	UPROPERTY()
	FInstanceIDAndIndex VisualData;
	
	UPROPERTY()
	FInstanceIDAndIndex CollisionData;
};

USTRUCT()
struct ABSTRACTINSTANCE_API FInstanceComponentData
{
	GENERATED_BODY()

	FInstanceComponentData() = default;
	FInstanceComponentData( AActor* owner, const FInstanceData& instanceData, bool castDistanceFieldShadows );

	/* Gets the Lightweight mesh component for a given index */
	FORCEINLINE ULightweightHierarchicalInstancedStaticMeshComponent* GetLightweightMeshComponent( int32 Index ) const { return InstancedStaticMeshComponents[Index]; }
	/* Gets the Lightweight collision component for a given index */
	FORCEINLINE ULightweightCollisionComponent* GetLightweightCollisionComponent( int32 Index ) const { return InstancedCollisionComponents[Index]; }

	/* Adds an instance handle to the tracking map */
	int32 AddInstanceHandle( const FInstanceOwnerHandlePtr& handleRefPtr )
	{
		const int32 meshCompIndex = handleRefPtr->GetMeshComponentIndex();
		return InstanceHandles.FindOrAdd( meshCompIndex ).Add( handleRefPtr );
	}
	
	/**
	 * Adds an instance. Depending on whether this instance type is specified to use multiple instance components a new mesh comp may be created.
	 * Additionally, if this component uses batched collision a collision Instance entry will be added to the appropriate collision comp.
	 */
	void AddInstance( const FTransform& Transform, bool WorldSpace, bool InitializeHidden, FInstanceAdditionData& OutInstanceAdditionData );

	/* Removes an Instance. Performs a remove swap so it also updates corresponding physics tracking info */
	void RemoveInstance( FInstanceOwnerHandlePtr& HandlePtr );
	
	UPROPERTY(VisibleInstanceOnly, Category = "Instance Component Data")
	TArray< ULightweightHierarchicalInstancedStaticMeshComponent* > InstancedStaticMeshComponents{};

	UPROPERTY(VisibleInstanceOnly, Category = "Instance Component Data")
	TArray<ULightweightCollisionComponent*> InstancedCollisionComponents{};

	UPROPERTY(VisibleInstanceOnly, Category = "Instance Component Data")
	UAkInstancedGeometryComponent* AkInstancedGeometryComponent {};

	// Map of all instance handles to their visual mesh component. For non-bucketed visuals this map will only have a single key
	TMap< int32, TArray<FInstanceOwnerHandlePtr> > InstanceHandles;

	/* Owning Actor. This actors lifetime must be guarenteed */
	AActor* Owner;
	/* Cached Copy of the instance data this component data is representing */
	FInstanceData InstanceData;

	/* Cached from Instance Data */
	bool bUsesBucketCollision{false};
	/* Cached version when initially made. */
	bool bCastDistanceFieldShadows{false};

	/* Cached version when initially made. */
	FFloatRange DrawDistance{};

	/* Tracking index for the component we are currently adding new instances into */
	int32 CurrentMeshComponentIndex = INDEX_NONE;

	int32 NumVisualInstancesPerComponent = 0;
	int32 NumCollisionComponentsPerVisual = 0;
	
private:
	/**
	 * Adds a collision Instance entry. Will potentially create a new collision comp if we are not bucketing the visual instance and our count exceeds the max allowed for a single collision component.
	 * This should only be called when adding a visual instance and this is handled internally. Adding Collision Instances without a visual representation will
	 * break the bucketing system and IDs will fail to align.
	 */
	void AddCollisionInstance( const FTransform& Transform, bool WorldSpace, FInstanceAdditionData& OutInstanceAdditionData );
	
	/* Finds a mesh component that has room for a new instance entry (per instance data Max mesh instance count) and updates the current mesh comp index. May create a new one if no valid component is found with space */
	void UpdateCurrentMeshComponentIndex();
	/* Adds a new mesh component. Should never be called manually. */
	int32 AddLightweightMeshComponent();

	/* Addes a new collision component. Should never be called manually */
	int32 AddLightweightCollisionComponent();

	/* Creates and Adds a AKInstancedGeometry component - Called on component data creation should not be called manually*/
	void AddAkGeometryComponent();
};

USTRUCT()
struct ABSTRACTINSTANCE_API FLazySpawnEntry
{
	GENERATED_BODY()

	FInstanceOwnerHandlePtr TargetHandle;
	FInstanceData InstanceData;
	TWeakObjectPtr<AActor> OwnerActor;
	FTransform T{};
	
	FLazySpawnEntry( const FInstanceOwnerHandlePtr& InHandle, const FInstanceData& SourceData, AActor* InOwner,const FTransform& ActorTransform )
	{
		TargetHandle = InHandle;
		InstanceData = SourceData;
		OwnerActor = InOwner;
		T = ActorTransform;
	}
	FLazySpawnEntry() = default;
};

UCLASS(BlueprintType)
class ABSTRACTINSTANCE_API AAbstractInstanceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbstractInstanceManager();

	UFUNCTION(BlueprintCallable, Category = "Lightweight Instances")
	static AAbstractInstanceManager* GetInstanceManager( UObject* WorldContext );

	virtual void Tick(float DeltaSeconds) override;

	/** Creates abstract instances from the provided data object */
	static void SetInstancedStatic( AActor* OwnerActor, const FTransform& ActorTransform, const UAbstractInstanceDataObject* InstanceData, TArray<FInstanceOwnerHandlePtr>& OutHandles, bool bInitializeHidden = false );
	/** Creates abstract instance from the given instance data */
	static void SetInstanceFromDataStatic( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceOwnerHandlePtr& OutHandle, bool bInitializeHidden = false );

	/** Creates an abstract instance from the provided instance data. If instance owner handle is provided, it will be overwritten to point to this instance. If no handle is provided, a new handle will be created and written into OutHandle */
	void SetInstanced( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceOwnerHandlePtr& OutHandle, bool bInitializeHidden = false );

	static void MarkDirtyDeferred( UInstancedStaticMeshComponent* MeshComponent );

	/** Removes the instance from the abstract instance manager. Handle will be reset after this function returns */
	void RemoveInstance( FInstanceOwnerHandlePtr& Handle );
	/** Removes the instances from the abstract instance manager. Array will be cleaned as a result */
	static void RemoveInstances( UObject* WorldContext, TArray<FInstanceOwnerHandlePtr>& Handles );

	/** Attempts to resolve a hit into the abstract instance handle. Will return a read-only copy of the abstract instance in OutHandle and true on success */
	UFUNCTION( BlueprintCallable, Category = "Lightweight Instances" )
	bool ResolveHit( const FHitResult& Result, FInstanceHandle& OutHandle );

	/** Attempts to resolve an overlap into the abstract instance handle. Will return a read-only copy of the abstract instance in OutHandle and true on success */
	bool ResolveOverlap( const FOverlapResult& Result, FInstanceHandle& OutHandle );

	/** Retrieves the actor owning the particular instance handle from the handle */
	UFUNCTION( BlueprintCallable, Category = "Lightweight Instances" )
	static AActor* GetOwnerByHandle( const FInstanceHandle& Handle ) { return Handle.Owner.Get(); } 

	UFUNCTION(BlueprintCallable, Category = "Lightweight Instances" )
	static const UHierarchicalInstancedStaticMeshComponent* GetHandleInfo( const FInstanceHandle& Handle, int32& OutInstanceID );

	static void SetCustomPrimitiveDataOnHandle( const FInstanceOwnerHandlePtr& Handle,const TArray<float>& Values, bool bMarkDirty = true );
	static void SetCustomPrimitiveDataOnHandles( const TArray<FInstanceOwnerHandlePtr>& Handles,const TArray<float>& Values, bool bMarkDirty = true );
	
	/* Called from the cvar sink. */
	void StartDrawDebug(bool bEnabled);
	void HideAllInstance(bool bIsHidden);

	FORCEINLINE bool CanLazyLoad() const { return false; }
	
protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void BuildInstanceEntryData( const FName& Name, const FInstanceData& InstanceData, FInstanceComponentData* &OutInstanceData );
	ULightweightCollisionComponent* CreateLightweightCollisionComponent( const FInstanceData& InstanceData );
	
	void HandleDeferredDirtyComponents();
	
	UPROPERTY( VisibleInstanceOnly )
	TMap<FName,FInstanceComponentData> InstanceMap;
	
	/* Set by cvar on begin play. */
	bool bAllowLazySpawn;

	/* Queue of instances to be lazy spawned.*/
	TQueue<FLazySpawnEntry> LazyLoadTasks;
	
	/* Queue of priority instanced to be spawned. */
	TQueue<FLazySpawnEntry> PriorityLazyLoadTasks;

	/* Set by cvar on tick */
	float PriorityDistance;

	/* Last actor that was resolved for lazy load, if the last actor and current dont match we fire a post lazy load event. */
	UPROPERTY()
	AActor* LastResolvedLazyTaskActor;
	
	/*Set that gets marked dirty in the end of the frame so we can avoid marking to many component dirty in the end of the frame.*/
	UPROPERTY()
	TSet<UInstancedStaticMeshComponent*> DeferredMarkDirtySet;

	FTimerHandle UpdateDeferredTimerHandle;

	UPROPERTY()
	AActor* CachedPlayerCharacter;
	
private:
	friend struct FInstanceComponentData;
	
	UFUNCTION()
	void DrawDebug();
	
	static FName BuildUniqueName( const FInstanceData& InstanceData );
	static FName BuildUniqueName( const UInstancedStaticMeshComponent* MeshComponent );
	
	UPROPERTY()
	class UAudioGeometryInstanceManager* AudioGeometryInstanceManager;
};

UCLASS()
class ABSTRACTINSTANCE_API ULightweightCollisionComponent : public UInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	// renderstate is handled by ULightweightCollisionComponent
	virtual bool ShouldCreateRenderState() const override { return false; }
};

UCLASS()
class ABSTRACTINSTANCE_API ULightweightHierarchicalInstancedStaticMeshComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Physicstate is handled by ULightweightCollisionComponent
	virtual bool ShouldCreatePhysicsState() const override { return false; }
};
