// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "Buildables/FGBuildableConveyorBelt.h"
#include "Buildables/FGBuildableConveyorLift.h"
#include "FGSubsystem.h"
#include "FGConveyorItemSubSystem.generated.h"

class AConveyorBeltItemProxy;
class AFGBuildableConveyorBase;
/**
 * 
 */

DECLARE_STATS_GROUP( TEXT("Conveyor Renderer"), STATGROUP_ConveyorRenderer, STATCAT_Advanced );
DECLARE_STATS_GROUP( TEXT("Conveyor Renderer - Thread"), STATGROUP_ConveyorRenderer_Thread, STATCAT_Advanced );

/* Simple struct to subdivide instance component into buckets.*/
USTRUCT()
struct FInstanceLODs
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere )
	UStaticMesh* mMesh;

	UPROPERTY( VisibleAnywhere )
	TArray< class UFGConveyorInstanceMeshBucket* > mInstanceBucket;

	UPROPERTY( VisibleAnywhere )
	int32 mBucketSize;

	UPROPERTY()
	int32 mLodLevel;
	
	void UpdateVisibility( int32 NumInstances );

	/* Add X number of instance bucket components.*/
	void AddBucketComponents( int32 Num, AActor* Outer );

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
	TArray< TArray< FTransform > > mTransformsPerLodLevel;

	TArray<int32> mCount;

	int32 mCachedCount;
	
	/** Per lod level a FInstanceLODs struct is made which contains an array of pointers
	 *	instance groups, the instances are subdivided in smaller buckets so they can be
	 *	toggled on and off and reduces the rendering overhead of drawing them when un-used */
	UPROPERTY( VisibleAnywhere )
	TArray< FInstanceLODs > mItemLodBucket;

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
	TArray< TArray< FTransform > > LodData;

	FORCEINLINE void Push( int32 LodLevel, FTransform& t )
	{
		LodData[ LodLevel ].Push(t);
	}
	
	FORCEINLINE void Empty()
	{
		for ( auto& LOD : LodData )
		{
			LOD.Empty();
		}
	}

	FORCEINLINE void Init( int32 NumLods )
	{
		LodData.AddZeroed( NumLods );
	}
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

// TODO make buckets.
UCLASS( Blueprintable )
class FACTORYGAME_API AFGConveyorItemSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

	AFGConveyorItemSubsystem();
	
public:
	
	static AFGConveyorItemSubsystem* Get( UWorld* world );

	static void RegisterBelt( AFGBuildableConveyorBase* newBelt );
	static void UnRegisterBelt( AFGBuildableConveyorBase* removedBelt );

	static void SetIsConveyorRendererActive( bool newState )
	{
		mIsConveyorRendererActive = newState;
	}

	static bool IsConveyorRendererActive()
	{
		return AFGConveyorItemSubsystem::mIsConveyorRendererActive;
	}
	
private:
	// Begin AActor interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	// End AActor interface

	bool HandleDisabledState();
	
	/** Resolve the NewRegisteredActors and the NewRemovedActors queue at the beginning of the cycle */
	void ResolvedRegistered();
	
	/** Resolved all gathered removed belts & lifts*/
	void ResolveRemoved();
	
	/** Resolved a new conveyor item type to be added to the instance queue and texture */
	void ResolveNewTypes();
	
	void ComputeViewCullAndDistance( const FVector PlayerLocation, FConveyorActorContainer< AFGBuildableConveyorBelt* >* Conveyors, FConveyorActorContainer< AFGBuildableConveyorLift* >* Lifts );

	void GatherTransformData( const TArray<bool> DistancesToUpdate, FConveyorActorContainer< AFGBuildableConveyorBelt* >* Belt, FConveyorActorContainer< AFGBuildableConveyorLift* >* Lifts);

	void UpdateGPUData(const TArray<bool> DistancesToUpdate);

	void UpdateBuckets();
	
	/* Called in the beginning of the frame to ensure we are working with clean buffers. */
	void Cleanup( TArray< bool > LodsToUpdate );

	TArray< bool > UpdateTimers( float DeltaTime );

	FORCEINLINE void UpdateMaxInstancesEncountered( int32 Value )
	{
		mMaxNumberInstancesEncountered = FMath::Max( mMaxNumberInstancesEncountered, Value);
	}

	FORCEINLINE int32 GetMaxEncounteredNumberInstances() const
	{
		return  mMaxNumberInstancesEncountered;
	}
	
	static bool mIsConveyorRendererActive;

private:
	// Update counters
	TArray< float > Timers;
	
	int32 mCurrentUniqueTypes;

	UPROPERTY( VisibleAnywhere, Transient)
	TArray< AFGBuildableConveyorBelt* > mWorldBelts;

	UPROPERTY( VisibleAnywhere, Transient)
	TArray< AFGBuildableConveyorLift* > mLifts;

	/* Named map of the instance mesh components. */
	UPROPERTY( VisibleInstanceOnly, Transient)
	TMap< FName, FConveyorItemArray > mItemType;

	// Map per task per type.
	TArray< TMap< FName, FConveyorInstanceLodData > > mTransformGatherTaskData;
	
	/* Frame result of the current conveyor states, no need to make this a UPROPERTY() since it re-computed every frame.*/
	TArray< FConveyorActorContainer< AFGBuildableConveyorBelt* > > mBeltTaskResults;
	TArray< FConveyorActorContainer< AFGBuildableConveyorLift* > > mLiftTaskResults;
	
	/* Combined result of the current conveyor states, no need to make this a UPROPERTY() since it re-computed every frame.*/
	FConveyorActorContainer< AFGBuildableConveyorBelt* > mBeltTaskLODResults;
	FConveyorActorContainer< AFGBuildableConveyorLift* > mLiftTaskLODResults;
	
	/* End task data members. */
	////////////////////////////
	
	/* Thread safe t-pair queue with the new descriptors to register. */
	TQueue< TPair< FName, TSubclassOf< UFGItemDescriptor > >, EQueueMode::Mpsc > mNewTypes;

	/* Queue of newly added actors & Removed actors.. */
	TQueue< AFGBuildableConveyorBase*, EQueueMode::Mpsc > NewRegisteredActors;
	TQueue< AFGBuildableConveyorBase*, EQueueMode::Mpsc > NewRemovedActors;
		
	bool mIsDisabled;

	int32 mMaxNumberInstancesEncountered;
	int32 mMaxNumberInstancesEncounteredPreviousFrame;

	/* Primitive components to either hide or show this frame depending on their transforms.*/
	TQueue<UPrimitiveComponent*,EQueueMode::Mpsc> ShowList;
	TQueue<UPrimitiveComponent*,EQueueMode::Mpsc> HideList;

	// Settings
protected:
	/* The number of items the system will pre initialize.
	 * The higher the number the less hitches that can happen but increases memory usage. */
	UPROPERTY( EditDefaultsOnly )
	int32 mInitialPreAllocatedNumberOfItemTypes;

	/* the number of instances that the system will pre initialize 
	 * The higher the number the less hitches that can happen but increases memory usage. */
	UPROPERTY( EditDefaultsOnly )
	int32 mInitialPreAllocatedNumberOfItemsInstances;

	/* The step size the max instance will grow to avoid overflow in the texture. */
	UPROPERTY( EditDefaultsOnly )
	int32 mItemInstanceIncrementSize;

	UPROPERTY( EditDefaultsOnly )
	int32 mItemInstanceUpdateThreshold;
	
	/* The step size the max instance will grow to avoid overflow in the texture. */
	UPROPERTY( EditDefaultsOnly )
	int32 mItemTypeIncrementSize;

	UPROPERTY( EditDefaultsOnly )
	UStaticMesh* mLiftMesh;
	
	UPROPERTY( EditDefaultsOnly, Category = "Performance" )
	int32 mMaxParallelTasks; 
	
	UPROPERTY( EditDefaultsOnly, Category = "Performance")
	TArray< FLODDataEntry > mLodData;

	/* Desired split for mesh instance count. */
	UPROPERTY(EditDefaultsOnly, Category = "Performance")
	int32 mInstanceVertsSplit;

	/* Minimum instances per component */
	UPROPERTY(EditDefaultsOnly, Category = "Performance")
	int32 mMinInstancesPerBucket;
	
	UPROPERTY( EditDefaultsOnly, Category = "Performance")
	int32 mMaxInstancesPerBucket;

	UPROPERTY( EditDefaultsOnly, Category = "Performance")
	int32 mNumberOfChecksBeforeUsingCachedData;
};
