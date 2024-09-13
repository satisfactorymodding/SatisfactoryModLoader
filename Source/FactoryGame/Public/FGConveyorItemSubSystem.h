// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

struct FConveyorItemData
{
	float Offset = 0.f;
	uint32 ItemID = 0;
	uint32 LUTSize = 0;
	TArray<FVector3f>* LUTPosPtr = nullptr;
	TArray<FQuat4f>* LUTQuat = nullptr;
	float DistanceMoved = 0.f;
			
	// Created later.
	FRenderTransform RenderTransform;
	FRenderTransform PrevRenderTransform;

	FConveyorItemData(float InOffset,int32 InItemID, TArray<FVector3f>* InLUTPos,TArray<FQuat4f>* InLUTQuat,int32 InLUTSize, float InDistanceMoved)
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
private:
	// Begin AActor interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	void InitializeConveyorItems();
	void Update();
	
	/* Called in the beginning of the frame to ensure we are working with clean buffers. */
	static bool mIsConveyorRendererActive;

private:

	// Queued up by custom code in the unreal's visibility logic.
	TQueue< const class UFGConveyorBeltVisibilityMesh*, EQueueMode::Mpsc > mVisibleConveyors;
	TQueue< const class UFGConveyorLiftVisibilityMesh*, EQueueMode::Mpsc > mVisibleLifts;
	
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
};