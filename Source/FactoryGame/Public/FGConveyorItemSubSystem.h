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

DECLARE_STATS_GROUP( TEXT("Conveyor Renderer"), STATGROUP_ConveyorRenderer, STATCAT_Advanced );
DECLARE_STATS_GROUP( TEXT("Conveyor Renderer - Thread"), STATGROUP_ConveyorRenderer_Thread, STATCAT_Advanced );

/* Simple struct to subdivide instance component into buckets.*/
USTRUCT()
struct FInstanceLODs
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere )
	UStaticMesh* mMesh = nullptr;

	UPROPERTY( VisibleAnywhere )
	TArray< class UFGConveyorInstanceMeshBucket* > mInstanceBucket = {};

	UPROPERTY( VisibleAnywhere )
	int32 mBucketSize = 0;

	UPROPERTY()
	int32 mLodLevel = 0;
	
	void UpdateVisibility( int32 NumInstances );

private:
	void AddInstance_Internal( AActor* Outer );

public:
	FInstanceLODs()
	{
	}
};

USTRUCT()
struct FConveyorItemArray
{
	GENERATED_BODY()
	
	/** Cleared at the end of the frame
	* 	[ Lod Level ][ Instance locations ]*/
	TArray< TArray< FTransform > > mTransformsPerLodLevel = {};
	TArray< TArray< FTransform > > mPrevTransformsPerLodLevel = {};

	TArray<int32> mCount = {};

	int32 mCachedCount = 0;
	
	/** Per lod level a FInstanceLODs struct is made which contains an array of pointers
	 *	instance groups, the instances are subdivided in smaller buckets so they can be
	 *	toggled on and off and reduces the rendering overhead of drawing them when un-used */
	UPROPERTY( VisibleAnywhere )
	TArray< FInstanceLODs > mItemLodBucket = {};

	FORCEINLINE void UpdateCount()
	{
		// Setup if we have too.
		if( UNLIKELY(mCount.Num() != mTransformsPerLodLevel.Num()))
		{
			mCount.SetNum( mTransformsPerLodLevel.Num() );
		}
		
		for	(int32 i = 0; i < mTransformsPerLodLevel.Num(); i++)
		{
			mCount[ i ] =  mTransformsPerLodLevel[ i ].Num();
		}

		int32 Count = 0;
		
		for	(int32 i = 0; i < mCount.Num(); i++)
		{
			Count = FMath::Max( Count, mCount[i] );
		}

		mCachedCount = Count;
	}

	FORCEINLINE int32 GetMaxCount()
	{
		return mCachedCount;
	}

	FConveyorItemArray() : mCachedCount(0)
	{
	}
};

struct FConveyorInstanceLodData
{	
	/* 2D array containing transform data per lod */
	TArray< TArray< FTransform > > LodData = {};
	TArray< TArray< FTransform > > PrevLodData = {};

	FORCEINLINE void Push( int32 LodLevel, const FTransform& t,const FTransform& PrevT )
	{
		LodData[ LodLevel ].Add(t);
		PrevLodData[ LodLevel ].Add(PrevT);
	}
	
	FORCEINLINE void Empty()
	{
		for ( auto& LOD : LodData )
		{
			LOD.Empty();
		}
		
		for ( auto& LOD : PrevLodData )
		{
			LOD.Empty();
		}
	}

	FORCEINLINE void Init( int32 NumLods )
	{
		LodData.AddZeroed( NumLods );
		PrevLodData.AddZeroed( NumLods );
	}
};

USTRUCT()
struct FConveyorLodData
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<UFGConveyorInstanceMeshBucket*> Buckets;
};

USTRUCT()
struct FConveyorBucketData
{
	GENERATED_BODY()
	
	/*Cached CDO for debugging.*/
	UPROPERTY()
	TSubclassOf<UFGItemDescriptor> Desc = nullptr;
	
	UPROPERTY()
	TArray<FConveyorLodData> LodBuckets;

	void CreateComponent(AActor* Outer);
};

template< class Type >
struct FConveyorActorContainer
{
	TArray< TArray< Type > > Actors;
	
public:
	/* Push actor to lod level array.*/
	FORCEINLINE void Push( Type Actor, int32 LodLevel )
	{
		Actors[ LodLevel ].Push( Actor );	
	}

	/* Remove data without deallocating data. */
	FORCEINLINE void Reset()
	{
		for ( auto& LOD : Actors )
		{
			LOD.Reset();
		}
	}

	FORCEINLINE void Init( int32 NumLods )
	{
		Actors.AddZeroed( NumLods );
	}

	FORCEINLINE int32 Num( TArray< bool > UpdateList ) const
	{
		int32 Count = 0;

		for	(int32 i = 0; i < Actors.Num(); i++)
		{
			Count = UpdateList[i] ? Actors[i].Num() : 0;
		}

		return Count;
	}

	FConveyorActorContainer()
	{}
};

USTRUCT( BlueprintType )
struct FLODDataEntry
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly )
	float Distance;

	UPROPERTY( EditDefaultsOnly )
	float TargetFPS;

	/* Should we check if the player can see the top of the conveyor belts or not?
	 * Recommended to only do this on the first lod. */
	UPROPERTY( EditDefaultsOnly )
	bool bViewCheck;
	
	UPROPERTY( EditDefaultsOnly )
	bool bRotate;

	// Shadows
	UPROPERTY( EditDefaultsOnly )
	bool bCastShadows;
	
	FLODDataEntry()
	{
		Distance = 0;
		TargetFPS = -1;
		bRotate = true;
		bCastShadows = true;
	}
};

struct FPrepEntry
{
	float Offset;
	FInterpCurvePoint<float>* ReparamTableCurve;
	FInterpCurvePoint<FVector>* PositionCurve;
	int32 NumReparamPoints;
	int32 NumPositionPoints;
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

	FORCEINLINE void ReportVisibleBelt( const UFGConveyorInstancedSplineMeshComponent* Component )
	{
		mVisibleConveyors.Enqueue( Component );
		Component->SetRelevant( true );
	}

	FORCEINLINE void ReportVisibleLift( const UFGConveyorLiftVisibilityMesh* Component )
	{
		mVisibleLifts.Enqueue( Component );
		Component->SetRelevant( true );
	}
	
private:
	// Begin AActor interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	void InitializeConveyorItems();
	void GatherTransformData_ISPC( const TArray<bool> DistancesToUpdate, FConveyorActorContainer< AFGBuildableConveyorBelt* >* Belt, FConveyorActorContainer< AFGBuildableConveyorLift* >* Lifts);
	
	/* Called in the beginning of the frame to ensure we are working with clean buffers. */
	void Cleanup( TArray< bool > LodsToUpdate );

	TArray< bool > UpdateTimers( float DeltaTime );
	
	static bool mIsConveyorRendererActive;

private:
	// Update counters
	TArray< float > Timers;
	
	/* Named map of the instance mesh components. */
	UPROPERTY( VisibleInstanceOnly, Transient)
	TMap< FName, FConveyorItemArray > mItemType;

	// Deprecated.
	TArray<FName> mCachedKeys;
	
	/* Frame result of the current conveyor states, no need to make this a UPROPERTY() since it re-computed every frame.*/
	TArray< FConveyorActorContainer< AFGBuildableConveyorBelt* > > mBeltTaskResults;
	TArray< FConveyorActorContainer< AFGBuildableConveyorLift* > > mLiftTaskResults;
	
	/* Combined result of the current conveyor states, no need to make this a UPROPERTY() since it re-computed every frame.*/
	FConveyorActorContainer< AFGBuildableConveyorBelt* > mBeltTaskLODResults;
	FConveyorActorContainer< AFGBuildableConveyorLift* > mLiftTaskLODResults;
	
	/* End task data members. */
	////////////////////////////
	
	TQueue< const class UFGConveyorInstancedSplineMeshComponent*, EQueueMode::Mpsc > mVisibleConveyors;
	TQueue< const class UFGConveyorLiftVisibilityMesh*, EQueueMode::Mpsc > mVisibleLifts;
	
	UPROPERTY()
	TArray< const UFGConveyorInstancedSplineMeshComponent* > mActiveConveyorBelts;
	
	UPROPERTY()
	TArray< const class UFGConveyorLiftVisibilityMesh* > mActiveConveyorLifts;
	
	/* Active conveyor belts. */
	UPROPERTY()
	TArray<FConveyorBucketData> ItemRenderMeshData;

	/* Idiling conveyor belts. */
	UPROPERTY()
	TArray<UHierarchicalInstancedStaticMeshComponent*> ItemIdleRenderMeshData;

	TQueue<TSubclassOf<UFGItemDescriptor>,EQueueMode::Mpsc> mUnsetTypes;
	
	int32 ItemTypeCounter = 0;

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Performance")
	TArray< FLODDataEntry > mLodData;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFGItemDescriptor> mLiftHandleItemDesc;

	/* Conveyor handle item dummy.*/
	UPROPERTY()
	FConveyorBeltItem mHandleDummy;

private:
	// Cache data.
	TArray<FVector3f>	mTaskDataStartPositions[NumTasks] =				{};	
	TArray<FVector3f> 	mTaskDataStartTangents[NumTasks] =				{};	
	TArray<FVector3f> 	mTaskDataEndPositions[NumTasks] =				{};		
	TArray<FVector3f> 	mTaskDataEndTangents[NumTasks] =				{};
	
	/* Cached array for item alphas to compute the offset, should never be emptied only reset! */
	TArray<float>		mTaskDataAlphas[NumTasks] =						{};
	
	/* Cached array for item transforms, should never be emptied only reset! */
	TArray<FTransform3f> mTaskDataBeltTransforms[NumTasks] =			{};
	TArray<FConveyorBeltItem*> mTaskDataItems[NumTasks] =				{};
	TArray<FPrepEntry> mEntryData[NumTasks] =							{};
	TArray<FMatrix> mMatrixTaskData[NumTasks] =							{};
	TArray<FPreviousFrameLocationData*> mTaskHandles[NumTasks] =		{};
	
	// [static: TaskID] [Lod] [Item id]
	TArray<TArray<TArray<FPreviousFrameLocationData*>>> mSortedItem[NumTasks] =	{};
	
	UPROPERTY()
	TArray<TSubclassOf<UFGItemDescriptor>> mKnownItems;
};