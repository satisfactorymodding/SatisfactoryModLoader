// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

/* Simple struct to subdivide instance component into buckets.*/
USTRUCT()
struct FInstanceLODs
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere )
	UStaticMesh* mMesh;

	UPROPERTY( VisibleAnywhere )
	TArray< class UFGConveyorItemInstanceComponent* > mInstanceBucket;

	UPROPERTY( VisibleAnywhere )
	TArray< UMaterialInstanceDynamic* > mMaterialInstances;

	UPROPERTY( VisibleAnywhere )
	int32 mRow;

	UPROPERTY( VisibleAnywhere )
	int32 mBucketSize;

	UPROPERTY( VisibleAnywhere )
	int32 mLodLevel;

	void UpdateVisibility( int32 NumInstances );

	void AddBucketInstance( int32 Num, AActor* Outer );

	void UpdateBuffers( UTexture2D* PositionBuffer, UTexture2D* OrientationBuffer );

	void Initialize( AActor* Outer, UStaticMesh* Mesh, int32 Row, int32 LodLevel, UTexture2D* PositionBuffer, UTexture2D* OrientationBuffer );


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

	/* The row for texture pixel lookup. */
	int32 Id;

	/** Cleared at the end of the frame
	* 	[ Lod Level ][ Instance locations ]*/
	TArray< TArray< FTransform > > mTransformsPerLodLevel;

	TArray<int32> mCount;
	
	/** Per lod level a FInstanceLODs struct is made which contains an array of pointers
	 *	instance groups, the instances are subdivided in smaller buckets so they can be
	 *	toggled on and off and reduces the rendering overhead of drawing them when un-used */
	UPROPERTY( VisibleAnywhere )
	TArray< FInstanceLODs > mItemLodBucket;

	FORCEINLINE void UpdateCount()
	{
		if( mCount.Num() != mTransformsPerLodLevel.Num())
		{
			mCount.SetNum( mTransformsPerLodLevel.Num() );
		}
		
		for	(int32 i = 0; i < mTransformsPerLodLevel.Num(); i++)
		{
			mCount[ i ] =  mTransformsPerLodLevel[ i ].Num();
		}
	}

	FConveyorItemArray()
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

private:
	// Begin AActor interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	// End AActor interface

	/** Resolve the NewRegisteredActors and the NewRemovedActors queue at the beginning of the cycle */
	void ResolvedRegistered();
	
	/** Resolved all gathered removed belts & lifts*/
	void ResolveRemoved();
	
	/** Resolved a new conveyor item type to be added to the instance queue and texture */
	void ResolveNewTypes();
	
	void ComputeViewCullAndDistance( const FVector PlayerLocation, FConveyorActorContainer< const AFGBuildableConveyorBelt* >* Conveyors, FConveyorActorContainer< const AFGBuildableConveyorLift* >* Lifts );

	void GatherTransformData( const TArray<bool> DistancesToUpdate, const FConveyorActorContainer< const AFGBuildableConveyorBelt* >* Belt, FConveyorActorContainer< const AFGBuildableConveyorLift* >* Lifts);

	void BuildTextures( const TArray<bool> DistancesToUpdate );

	/* Check and resizes the texture buffers and intermediate data buffers that are used.
	 * When an resize occured it also updates all instance components and material instances. */
	bool Resize();

	void UpdateInstanceBounds( const TArray<bool> DistancesToUpdate );

	/* Kicks off the task graph based tasks. */
	void SubmitUpdateTask( const AActor* Pawn, const TArray< bool > LodsToUpdate );

	/* Called in the beginning of the frame to ensure we are working with clean buffers. */
	void Cleanup( TArray< bool > LodsToUpdate );

	TArray< bool > UpdateTimers( float DeltaTime );

	int32 GetMaxNumberInstances() const 	{ return mNearPositionBuffer->GetSizeX(); }
	int32 GetCurrentNumUniqueItems() const 	{ return mNearPositionBuffer->GetSizeY(); }

private:
	//////////////////////////////
	/* 2D Texture holding floats as position */
	UPROPERTY( VisibleAnywhere, Transient )
	UTexture2D* mNearPositionBuffer;
		
	/* 2D Texture holding uint8 as orientation. */
	UPROPERTY( VisibleAnywhere, Transient )
	UTexture2D* mNearOrientationBuffer;

	// Update counters
	TArray< float > Timers;

	int32 mCurrentInstanceBuckets;
	
	int32 mCurrentUniqueTypes;

	UPROPERTY( VisibleAnywhere )
	TArray< AFGBuildableConveyorBelt* > mWorldBelts;

	UPROPERTY( VisibleAnywhere )
	TArray< AFGBuildableConveyorLift* > mLifts;

	// TODO refactor to an array, we can use random access via the descriptors.
	/* Named map of the instance mesh components. */
	UPROPERTY( VisibleInstanceOnly )
	TMap< FName, FConveyorItemArray > mItemType;

	// new type
	TArray< TMap< FName, FConveyorInstanceLodData > > mTransformGatherTaskData;
	
	/* Frame result of the current conveyor states, no need to make this a UPROPERTY() since it re-computed every frame.*/
	TArray< FConveyorActorContainer< const AFGBuildableConveyorBelt* > > mBeltTaskResults;
	TArray< FConveyorActorContainer< const AFGBuildableConveyorLift* > > mLiftTaskResults;
	
	/* Combined result of the current conveyor states, no need to make this a UPROPERTY() since it re-computed every frame.*/
	FConveyorActorContainer< const AFGBuildableConveyorBelt* > mBeltTaskLODResults;
	FConveyorActorContainer< const AFGBuildableConveyorLift* > mLiftTaskLODResults;
	
	/* End task data members. */
	////////////////////////////
	
	/* Thread safe t-pair queue with the new descriptors to register. */
	TQueue< TPair< FName, TSubclassOf< UFGItemDescriptor > >, EQueueMode::Mpsc > mNewTypes;

	/* Queue of newly added actors & Removed actors.. */
	TQueue< AFGBuildableConveyorBase*, EQueueMode::Mpsc > NewRegisteredActors;
	TQueue< AFGBuildableConveyorBase*, EQueueMode::Mpsc > NewRemovedActors;

	// TODO deprecate.
	TArray< TQueue< FTransform, EQueueMode::Mpsc > > mTransformQueues;

	/* the range the texture data has to update. s*/
	int32 mUpdateRange;
	
	/* Buffer data */
	TArray< uint8 > mNearPositionBufferData;
	TArray< uint8 > mNearOrientationBufferData;

	FRenderCommandFence RenderFence;
	
	bool mIsDisabled;

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
	
	UPROPERTY( EditDefaultsOnly, Category = "Fallback" )
	UStaticMesh* mFallbackMesh;

	UPROPERTY( EditDefaultsOnly, Category = "Fallback" )
	UMaterialInterface* mFallbackMaterial;

	UPROPERTY( EditDefaultsOnly, Category = "Performance" )
	int32 mMaxParallelTasks; 
	
	UPROPERTY( EditDefaultsOnly, Category = "Performance")
	TArray< FLODDataEntry > mLodData;

	UPROPERTY( EditDefaultsOnly, Category = "Performance")
	int32 mMaxInstancesPerComponent;
	
public:
	UStaticMesh* GetFallbackmesh() 				{ return mFallbackMesh; }
	UMaterialInterface* GetFallbackMaterial() 	{ return mFallbackMaterial; }
};
