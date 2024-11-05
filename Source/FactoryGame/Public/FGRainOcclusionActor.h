// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "UI/FGDebugOverlayWidget.h"
#include "FGRainOcclusionActor.generated.h"

class UInstancedStaticMeshComponent;
class AFGBuildable;

DECLARE_STATS_GROUP( TEXT( "RainOcclusion" ), STATGROUP_RainOcclusion, STATCAT_Advanced );

UENUM()
enum class EFGRainOcclusionShape : uint8
{
	ROCS_Box,				/* Generic bounding box occlusion. */
	ROCS_Box_Special,		/* Box with and unique location.*/
	ROCS_Ramp,              /* Ramps, Double ramps and roofs. */
	ROCS_Triangle,          //TODO
	ROCS_CornerRamp,		/* Generic bound box occlusion, just generated a plane at the flat face instead.*/
	ROCS_CustomMesh         //TODO
};

UENUM()
enum class EFGRainOcclusionShapeScaling : uint8
{
	ROCSS_Center,
	ROCSS_Top,
	ROCSS_Bot
};

struct FSimpleComponentInfo
{
	TWeakObjectPtr<UStaticMesh> Mesh;
	FBox Bounds;
	FRotator Rotation;
	FVector Scale;
	float UpValue;
	EFGRainOcclusionShapeScaling CustomScaleType;
	float CustomScaleAmount;
};

struct FSimpleBuildingInfo
{
	TArray< FSimpleComponentInfo > mComponentData;
	EFGRainOcclusionShape mOcclusionType;

	static FSimpleBuildingInfo DefaultSquareFoundation( AFGBuildable* Source );
	//static FSimpleBuildingInfo DefaultTriangleFoundation( AFGBuildable* Source );
	//static FSimpleBuildingInfo DefaultRampFoundation( AFGBuildable* Source );


	
	FSimpleBuildingInfo( AFGBuildable* Source );
	FSimpleBuildingInfo()
	{
		
	}
};

/*	Proxies in this 
 * 
 */
UCLASS()
class FACTORYGAME_API AFGRainOcclusionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGRainOcclusionActor(); 
		
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	void ForceUpdateOcclusionShapes( const FVector& Location, const float& Range );

	void OnTraceCompleted( const FTraceHandle& Handle, FOverlapDatum& Data );
	
	UFUNCTION()
	void AddShape( AFGBuildable* Buildable );

	UFUNCTION()
	void RemoveShape( AFGBuildable* Buildable );

	UFUNCTION(BlueprintCallable,Category = "Rain Occlusion")
	static void SetupStaticMeshComponentFlags( UStaticMeshComponent* Component );

	void ResolveTracedEntries();

	UFUNCTION( BlueprintCallable )
	void SetUpdateRainOccluders(bool bActive);

	/* Custom meshes for the occlusion, we should use as little of these as possible. */
	UPROPERTY( VisibleAnywhere )
	TMap< UStaticMesh*, UInstancedStaticMeshComponent*> mCustomOccluderShapes;

	UInstancedStaticMeshComponent* SetupDefaultOccluderMeshComponent( FName Name );

	static FTransform GenerateLocation(const FSimpleComponentInfo& componentInfo, const EFGRainOcclusionShape& shape );

protected:
	/* Most common proxy used for occlusion. */
	UPROPERTY( VisibleAnywhere )
	UInstancedStaticMeshComponent* mBoxShapedOccluder;

	UPROPERTY( VisibleAnywhere )
	UInstancedStaticMeshComponent* mRampShapeOccluder;

	UPROPERTY( VisibleAnywhere )
	UInstancedStaticMeshComponent* mTriangleShapeOccluder;

	UPROPERTY( EditDefaultsOnly )
	int32 mNumEntriesToHandlePerFrame = 200;
	
private:
	TQueue< FVector, EQueueMode::Mpsc > mQueuedBoxRemovalTask;
	TQueue< FVector, EQueueMode::Mpsc > mQueuedBoxAddTask;
	TQueue< FSimpleBuildingInfo, EQueueMode::Mpsc > mResolvedEntries;

	FAsyncTask<class FGASyncBuildingGatheringTask>* mAsyncForceUpdateTask = nullptr;

	TArray< FOverlapResult > mCachedTraceData;
	int32 mCurrentFrameEntry = 0;
	
	FTraceHandle mTraceHandle;
	
	FOverlapDelegate mOverlapDelegate;

	/* Do we currently need to occlude?*/
	UPROPERTY( VisibleAnywhere )
	bool bIsActive;
};

struct FFGBuildingGatheringWorker
{
	FFGBuildingGatheringWorker()
	{
	}

	FFGBuildingGatheringWorker( TQueue< FSimpleBuildingInfo, EQueueMode::Mpsc>* Queue )
	{
		BuildingInfoQueue = Queue;
	}

	TQueue< FSimpleBuildingInfo, EQueueMode::Mpsc>* BuildingInfoQueue;

	TArray< FTransform > OutBoxTransforms;
	TArray< FTransform > OutTriangleShapes;
	TArray< FTransform > OutRampShapes;

	//TODO UNIMPLEMENTED
	TMap< UStaticMesh*, TArray< FTransform > > OutCustomShapes; 

	void DoWork();
};


class FGASyncBuildingGatheringTask : public FNonAbandonableTask
{
public:
	FGASyncBuildingGatheringTask (FFGBuildingGatheringWorker* inWorker)
	{
		Worker = inWorker;
	}

	FFGBuildingGatheringWorker* Worker;

	void DoWork()
	{
		Worker->DoWork();
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT( FGASyncBuildingGatheringTask, STATGROUP_ThreadPoolAsyncTasks )		
    }

	~FGASyncBuildingGatheringTask()
	{
		delete Worker;
	}
	
};
