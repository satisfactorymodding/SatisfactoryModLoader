// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableConveyorLift.h"
#include "FGConveyorInstanceSplineMesh.h"
#include "FGSubsystem.h"
#include "FGConveyorItemSubSystem.generated.h"

class AConveyorBeltItemProxy;
class AFGBuildableConveyorBase;
/**
 * 
 */

constexpr int32 NumTasks = 16;

#define WITH_PIE_SUPPORT 0 //WITH_EDITOR
#define NUM_LANES 16
#define DEBUG_CONVEYOR_RENDERER 0
#define LUT_STEPSIZE 30

DECLARE_STATS_GROUP( TEXT("Conveyor Renderer"), STATGROUP_ConveyorRenderer, STATCAT_Advanced );
DECLARE_STATS_GROUP( TEXT("Conveyor Renderer - Thread"), STATGROUP_ConveyorRenderer_Thread, STATCAT_Advanced );

class UFGConveyorInstanceMeshBucket;

struct FItemContainer
{
	TArray<UFGConveyorInstanceMeshBucket*> MeshBuckets;
	TArray<struct FConveyorItemData*> ItemData[NUM_LANES];
	
	UFGConveyorInstanceMeshBucket* CreateComponent(AActor* Outer, UStaticMesh* Mesh);
};

struct FLUTData
{
	TArray<FVector3f> Position;
	TArray<FQuat4f> Quat;

	FLUTData()
	{
		
	}
};

struct FDeferredLookupAdd
{
	FLUTData Data;
	TWeakObjectPtr<AFGConveyorChainActor> Owner;

	FDeferredLookupAdd(FLUTData& InData, AFGConveyorChainActor* InOwner)
	{
		Data = InData;
		Owner = InOwner;
	}
	
	FDeferredLookupAdd(const TArray<FVector3f>& InPosition,const TArray<FQuat4f>& InQuats, AFGConveyorChainActor* InOwner)
	{
		Data.Position = InPosition;
		Data.Quat = InQuats;
		Owner = InOwner;
	}
	
	FDeferredLookupAdd()
	{
		Data = FLUTData();
		Owner = nullptr;
	}
};

struct FConveyorItemData
{
	float Offset = 0.f;
	uint32 ItemID = 0;
	uint32 LUTSize = 0;
	const TArray<FVector3f>* LUTPosPtr = nullptr;
	const TArray<FQuat4f>* LUTQuat = nullptr;
	float DistanceMoved = 0.f;
			
	// Created later.
	FRenderTransform RenderTransform;
	FRenderTransform PrevRenderTransform;

	FConveyorItemData(float InOffset,int32 InItemID, const TArray<FVector3f>* InLUTPos,const TArray<FQuat4f>* InLUTQuat,int32 InLUTSize, float InDistanceMoved)
	{
		Offset = InOffset;
		ItemID = InItemID;
		LUTPosPtr = InLUTPos;
		LUTQuat = InLUTQuat;
		LUTSize = InLUTSize;
		DistanceMoved = InDistanceMoved;
	}
	
	FConveyorItemData(float InOffset,int32 InItemID,const FRenderTransform& InTransform, const FRenderTransform& InPrevTransform):
		LUTSize( 0 ),
		LUTPosPtr( nullptr ),
		LUTQuat( nullptr )
	{
		Offset = InOffset;
		ItemID = InItemID;
		RenderTransform = InTransform;
		PrevRenderTransform = InPrevTransform;
	}
};


// TODO make buckets.
UCLASS( Blueprintable )
class FACTORYGAME_API AFGConveyorItemSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

	AFGConveyorItemSubsystem();
	
public:
	static AFGConveyorItemSubsystem* Get( UWorld* world );

#if WITH_PIE_SUPPORT
	static TMap<UWorld*,AFGConveyorItemSubsystem*> mGlobalSystemPtrPIEMap;
#else
	static AFGConveyorItemSubsystem* mGlobalSystemPtr;
#endif

	FORCEINLINE void ReportVisibleBelt( const UFGConveyorBeltVisibilityMesh* Component )
	{
		mVisibleConveyors.Enqueue( Component );
		Component->SetRelevant( true );
	}

	FORCEINLINE void ReportVisibleLift( const UFGConveyorLiftVisibilityMesh* Component )
	{
		mVisibleLifts.Enqueue( Component );
		Component->SetRelevant( true );
	}

	bool IsKnown(UClass* Descriptor) const { return mKnownItems.Contains( Descriptor ); }
	void LazyAddConveyorItemOfClass(UClass* Descriptor);

	static void AddLookupTable(AFGConveyorChainActor* Actor, const TArray<FVector3f>& Position, const TArray<FQuat4f>& Quats);
	static void RemoveChainActorFromLookupTable(AFGConveyorChainActor* ChainActor);

private:
	// Begin AActor interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	void InitializeConveyorItems();
	void Update();

	// Resolves remove queue.
	void CleanupLookupTables();

	// Resolves add queue.
	void AddNewLookupTables();
	/* Called in the beginning of the frame to ensure we are working with clean buffers. */
	static bool mIsConveyorRendererActive;

private:
	/* Map of actors to lookup data.
	 * NOTE we dont want this as an UPROPERTY() because we don't want the GC to clean up the pointers.
	 * They act more as an unique ID then a pointer in this use case. */
	TMap<AFGConveyorChainActor*,FLUTData> LookupTableMap;

	// Queued up by custom code in the unreal's visibility logic.
	TQueue< const class UFGConveyorBeltVisibilityMesh*, EQueueMode::Mpsc > mVisibleConveyors;
	TQueue< const class UFGConveyorLiftVisibilityMesh*, EQueueMode::Mpsc > mVisibleLifts;

	// Queued up adds and removes for lookup data.
	TQueue< class AFGConveyorChainActor*, EQueueMode::Mpsc > mRemovedChainActors;
	TQueue< FDeferredLookupAdd, EQueueMode::Mpsc > mAddedChainActors;
	
	UPROPERTY()
	TArray< const UFGConveyorBeltVisibilityMesh* > mActiveConveyorBelts;
	
	UPROPERTY()
	TArray< const class UFGConveyorLiftVisibilityMesh* > mActiveConveyorLifts;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFGItemDescriptor> mLiftHandleItemDesc;

	UPROPERTY()
	TArray<TSubclassOf<UFGItemDescriptor>> mKnownItems;

	/* Array of conveyor items where array id is identical with the item "id" in the desc cdo. */
	TArray<FItemContainer> RenderBuckets;

	/* Render data per lane, used per task.*/
	TArray<FConveyorItemData> DataPerLane[NUM_LANES];

	/* Buckets of item ID requested this frame. */
	TQueue<int32,EQueueMode::Mpsc> BucketRequests;
	
	// Transient data.
	TArray<AFGBuildableConveyorBelt*> ActiveBelts;
	TArray<AFGBuildableConveyorLift*> ActiveLifts;

	bool bAreItemsInitialized = false;

	std::atomic<bool> bDidFinishTask = true;
};