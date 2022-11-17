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

#define GetLocationFromT(T)			T.GetLocation()
#define GetRightVectorFromT(T)		T.GetRotation().GetRightVector()
#define GetUpVectorFromT(T)			T.GetRotation().GetUpVector()
#define GetForwardVectorFromT(T)	T.GetRotation().GetForwardVector()

USTRUCT( BlueprintType )
struct ABSTRACTINSTANCE_API FInstanceHandleWrapper
{
	GENERATED_BODY()
	FInstanceHandle* Handle;
	
	FInstanceHandleWrapper( FInstanceHandle* InHandle )
	{
		Handle = InHandle;
	}
	
	FInstanceHandleWrapper()
	{
		Handle = nullptr;
	}
};


USTRUCT()
struct ABSTRACTINSTANCE_API FInstanceComponentData
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly)
	UHierarchicalInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	UPROPERTY(VisibleInstanceOnly)
	TArray<UInstancedStaticMeshComponent*> InstancedCollisionComponents;

	TArray<FInstanceHandle*> InstanceHandles;

	/* Cached version when initially made. */
	bool bCastDistanceFieldShadows;

	/* Cached version when initially made. */
	FFloatRange DrawDistance;
};

USTRUCT()
struct ABSTRACTINSTANCE_API FLazySpawnEntry
{
	GENERATED_BODY()

	FInstanceHandle* TargetHandle;
	FInstanceData InstanceData;
	TWeakObjectPtr<AActor> OwnerActor;
	FTransform T;
	
	FLazySpawnEntry( FInstanceHandle* InHandle,const FInstanceData& SourceData, AActor* InOwner,const FTransform& ActorTransform )
	{
		TargetHandle = InHandle;
		InstanceData = SourceData;
		OwnerActor = InOwner;
		T = ActorTransform;
	}
	
	FLazySpawnEntry() {};
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
	static AAbstractInstanceManager* GetInstanceManager();

	virtual void Tick(float DeltaSeconds) override;

	static void SetInstancedStatic( AActor* OwnerActor, const FTransform& ActorTransform, const UAbstractInstanceDataObject* InstanceData, TArray<FInstanceHandle*>& OutHandle, bool bInitializeHidden = false );
	static void SetInstanceFromDataStatic( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceHandle* &OutHandle, bool bInitializeHidden = false );
	void SetInstanced( AActor* OwnerActor, const FTransform& ActorTransform, const FInstanceData& InstanceData, FInstanceHandle* &OutHandle, bool bInitializeHidden = false );

	static void MarkDirtyDeferred( UInstancedStaticMeshComponent* MeshComponent );
	
	void RemoveInstance( FInstanceHandle* Handle );
	static void RemoveInstances( UObject* WorldContext, TArray<FInstanceHandle*>& Handles, bool bEmptyHandleArray = true );

	UFUNCTION( BlueprintCallable, Category = "Lightweight Instances" )
	void RemoveInstance( UPARAM(ref) FInstanceHandle& InHandle );

	UFUNCTION( BlueprintCallable, Category = "Lightweight Instances" )
	bool ResolveHit( const FHitResult& Result, FInstanceHandle& OutHandle );

	bool ResolveOverlap( const FOverlapResult& Result, FInstanceHandle& OutHandle );

	UFUNCTION( BlueprintCallable, Category = "Lightweight Instances" )
	static AActor* GetOwnerByHandle( const FInstanceHandle& Handle ) { return Handle.Owner.Get(); } 

	UFUNCTION(BlueprintCallable, Category = "Lightweight Instances" )
	static UHierarchicalInstancedStaticMeshComponent* GetHandleInfo( const FInstanceHandle& Handle, int32 &OutInstanceID );

	static void SetCustomPrimitiveDataOnHandle( const FInstanceHandle* Handle,const TArray<float>& Values, bool bMarkDirty = true );
	static void SetCustomPrimitiveDataOnHandles( const TArray<FInstanceHandle*> &Handles,const TArray<float>& Values, bool bMarkDirty = true );
	
	/* Called from the cvar sink. */
	void StartDrawDebug(bool bEnabled);
	void HideAllInstance(bool bHide);

	FORCEINLINE bool CanLazyLoad() const { return bAllowLazySpawn; }
	
protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void BuildInstanceEntryData( const FName& Name, const FInstanceData& InstanceData, FInstanceComponentData* &OutInstanceData );

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
	UFUNCTION()
	void DrawDebug();

#if !AI_PIE
	static AAbstractInstanceManager* StaticManager;
#else // PIE support
	static TMap<UWorld*,AAbstractInstanceManager*> StaticManager_PIE;
#endif
	
	static FName BuildUniqueName( const FInstanceData& InstanceData );
	static FName BuildUniqueName( const UInstancedStaticMeshComponent* MeshComponent );
};
