// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGConveyorChainActor.h"
#include "FGRemoteCallObject.h"
#include "FGSignificanceInterface.h"
#include "FGConveyorItem.h"
#include "FGFactoryConnectionComponent.h"
#include "FGBuildableConveyorBase.generated.h"


class UFGConnectionComponent;
using FG_ConveyorItemRepKeyType = uint32;
using FG_ConveyorVersionType = uint32;

enum { FG_CONVEYOR_REP_KEY_NONE = 0 };

enum class EConveyorChainFlags : uint8
{
	CCL_None	= 0b00000000,
	CCL_First	= 0b00000001,
	CCL_Mid		= 0b00000010,
	CCL_Last	= 0b00000100
};

/**
 * Valid state for picking up conveyor belt items.
 */
UCLASS()
class FACTORYGAME_API UFGUseState_ConveyorBeltValid : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltValid() { mIsUsableState = true; mWantAdditonalData = true; }

public:
	/** item that was looked at */
	FConveyorBeltItem mConveyorBeltItem;

	/** Index Of the item */
	int32 mItemIndex;
};

UCLASS()
class FACTORYGAME_API UFGUseState_ConveyorBeltFullInventory : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltFullInventory() { mIsUsableState = false; mWantAdditonalData = true; }

public:
	/** item that was looked at */
	FConveyorBeltItem mConveyorBeltItem;
};

/**
 * State for when the belt is empty.
 */
UCLASS()
class FACTORYGAME_API UFGUseState_ConveyorBeltEmpty : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltEmpty() { mIsUsableState = false; mWantAdditonalData = false; }
};

/**
*A class used for clients to be able to call the server through the local player character.
*/
UCLASS()
class FACTORYGAME_API UFGConveyorRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
	public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGConveyorRemoteCallObject = false;

	UFUNCTION( Reliable, Server, Category = "Use" )
	void Server_OnUse( class AFGBuildableConveyorBase* target, class AFGCharacterPlayer* byCharacter, float itemOffset, uint16 desiredItemClassIdx );
};



extern bool GIsConveyorFreezingEnabled;

/**
 * Shared base for conveyor belts and lifts.
 * Responsible for common logic such as the factory ticking, replication, interactions etc.
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableConveyorBase : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorBase();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	// End IFGUseableInterface
	
	// Begin AFGBuildable interface
	virtual bool ShouldBeConsideredForBase_Implementation() override;
	virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;
	virtual bool ShouldBlockGuidelinePathForHologram( const class AFGHologram* hologram ) const override;
	// End AFGBuildable interface
	
	// Begin AFGBuildableFactory interface
	virtual void Factory_Tick( float deltaTime ) override;
	virtual uint8 MaxNumGrab( float dt ) const override;
	virtual uint8 EstimatedMaxNumGrab_Threadsafe( float estimatedDeltaTime ) const override;
	// End AFGBuildableFactory interface
	
	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual	void SetupForSignificance() override;

	// Server Use
	void OnUseServerRepInput( class AFGCharacterPlayer* byCharacter, float itemOffset, TSubclassOf< class UFGItemDescriptor > desiredItemClass );

	virtual void BuildStaticItemInstances();
	void DestroyStaticItemInstancesNextFrame();
	FORCEINLINE bool GetHasAnyStaticInstances() const { return mFrozenItemsInstancedStaticMeshComponents.Num() > 0; }
	
	UFUNCTION( BlueprintPure, Category = "Significance" )
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant; }
	// End IFGSignificanceInterface

	FORCEINLINE float GetLength() const { return mLength; }
	FORCEINLINE float GetSpeed() const { return mSpeed; }

	/** @return The connection, safe to assume its always valid. */
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection0() const { return mConnection0; }
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection1() const { return mConnection1; }

	/** Map a world location to an offset along the conveyor. */
	virtual float FindOffsetClosestToLocation( const FVector& location ) const PURE_VIRTUAL( , return 0.0f; );
	/** Get the location and direction of the conveyor at the given offset. */
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const PURE_VIRTUAL( , );

	/** Gets the distance between the first component and the component its connected to. Used for ConveyorChain spline offset calculations and generation */
	virtual float GetDistanceBetweenFirstConnection();
	/** Gets the distance between the first component and the component its connected to. Used for ConveyorChain spline offset calculations and generation */
	virtual float GetDistanceBetweenLastConnection();

	/** Conveyor Ticking Function accessors and settors */
	FORCEINLINE void SetConveyorBucketID(int32 ID) { mConveyorBucketID = ID; }
	FORCEINLINE int32 GetConveyorBucketID() const { return mConveyorBucketID; }
	FORCEINLINE void SetConveyorChainFlags( uint8 chainFlags ){ mConveyorChainFlags = chainFlags; }
	FORCEINLINE uint8 GetConveyorChainFlags() const { return mConveyorChainFlags; }
	FORCEINLINE bool HasConveyorChainFlag( uint8 flag ) const { return mConveyorChainFlags && flag; }
	FORCEINLINE void SetNextTickConveyor( AFGBuildableConveyorBase* nextConveyor ) { mNextConveyor = nextConveyor; }
	FORCEINLINE AFGBuildableConveyorBase* GetNextTickConveyor( ) const { return mNextConveyor; }
	FORCEINLINE AFGConveyorChainActor* GetConveyorChainActor() const { return mConveyorChainActor; }
	FORCEINLINE bool GetIsConveyorLift() const { return mIsConveyorLift; }
	FORCEINLINE void GetConveyorBeltItems(TArray< FConveyorBeltItem* >& out_items )
	{
		if( mConveyorChainActor )
		{
			mConveyorChainActor->GetItemsForSegment( this, out_items );
		}
	}

	/** Assigns a Chain Actor to a Conveyor. This will also clear temporary ism instances for clients if there are any */
	void SetConveyorChainActor( AFGConveyorChainActor* chainActor );
	

	/** Returns how much room there currently is on the belt. If the belt is empty it will return the length of the belt */
	FORCEINLINE float GetAvailableSpace() const
	{
		for ( int32 i = mItems.Num() - 1; i >= 0; --i )
		{
			return mItems[ i ].Offset;
		}

		return GetLength();
	}


	void ReportInvalidStateAndRequestConveyorRepReset();

	FORCEINLINE void MarkItemTransformsDirty()
	{
		mPendingUpdateItemTransforms = true;
	}

	/** Returns how much room there was on the belt after the last factory tick. If the belt is empty it will return the length of the belt */
	FORCEINLINE float GetCachedAvailableSpace_Threadsafe() const
	{
		return mCachedAvailableBeltSpace;
	}

#if !UE_BUILD_SHIPPING 
	void DebugDrawStalled() const;
#endif
	
#if UE_BUILD_SHIPPING // Shipping uses a force inline without debug logic.
	FORCEINLINE void SetStalled(bool stall) const { mIsStalled = stall; }
#else
	void SetStalled(bool stall) const;
#endif

	void EmptyBelt() { mItems.Empty(); }

	
protected:
	// Begin Factory_ interface
	virtual bool Factory_PeekOutput_Implementation( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const override;
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface

	virtual bool Factory_QuickPullConveyorToConveyor( FConveyorBeltItem& out_item, float availableSpace, float deltaTime );

	// Begin AFGBuildable interface
	virtual void GetDismantleInventoryReturns( TArray< FInventoryStack >& out_returns ) const override;
	// End AFGBuildable interface

	/** Called when the visuals, radiation etc need to be updated. */
	virtual void TickItemTransforms( float dt ) PURE_VIRTUAL(,);

	/* When using the exp - conveyor renderer tick the radio activity of the items. */
	virtual void TickRadioactivity() PURE_VIRTUAL(,);
	virtual void Factory_UpdateRadioactivity( class AFGRadioactivitySubsystem* subsystem ) PURE_VIRTUAL(,);
	
	//@todonow These can possibly be moved to private once Belt::OnUse has been moved to base.
	/** Find the item closest to the given location. */
	const FConveyorBeltItem* FindItemClosestToLocation( const FVector& location ) const;

	/** Checks if there is an item at index. */
	FORCEINLINE bool Factory_HasItemAt( int32 index ) const
	{
		return mItems.IsValidIndex(index);
	}
	
	/** Lets you know what type of item is on a specific index. */
	FORCEINLINE const FConveyorBeltItem& Factory_PeekItemAt( int32 index ) const
	{
		fgcheck(mItems.IsValidIndex(index));
		return mItems[index];
	}
	/** Remove an item from the belt at index. */
	void Factory_RemoveItemAt( int32 index );

	/* Destroys all ISMs generated for frozen conveyors.*/
	UFUNCTION()
	virtual void DestroyStaticItemInstances();

	/** Function used to generate cached clearance data for this conveyor. */
	virtual void GenerateCachedClearanceData( TArray< FFGClearanceData >& out_clearanceData );

	UFUNCTION()
	void OnRep_ChainInformation();

	void PlayPickupFX( int32 itemIndex  ) const;
	
private:
	/** Take the first element on the belt. */
	void Factory_DequeueItem();
	/** Put a new item onto the belt. */
	void Factory_EnqueueItem( const FInventoryItem& item, float initialOffset );

	/**
	 * @param out_availableSpace - amount of space until next item
	 *
	 * @return true if there is enough room for an item of size itemSize
	 */
	FORCEINLINE bool HasRoomOnBelt( float& out_availableSpace ) const
	{
		out_availableSpace = GetAvailableSpace();
		return out_availableSpace > AFGBuildableConveyorBase::ITEM_SPACING;
	}

	/**
	*	Thread safe version to check available room on a belt. This uses a cached position of the last item offset to ensure thread safety
	*
	*	@param out_availableSpace - amount of space until the next item
	*
	*	@return true if there is enough room for an item of size itemSize
	*/
	bool HasRoomOnBelt_ThreadSafe( float& out_availableSpace ) const
	{
		out_availableSpace = mCachedAvailableBeltSpace;

		return out_availableSpace > ITEM_SPACING;
	}
	

	friend class AFGConveyorItemSubsystem;

public:
	/** Default height above ground for conveyors. */
	static constexpr float DEFAULT_CONVEYOR_HEIGHT = 100.f;

	/** Spacing between each conveyor item, from origo to origo. */
	static constexpr float ITEM_SPACING = 120.0f;

	// TODO make this a cvar?
	static constexpr float NumSecStalledToConsiderFrozen = 2;
	
	FORCEINLINE bool IsStalled() const { return mCanEverStall && mIsStalled && mItems.Num() != 0; }

	/*Increment num frames items didnt move, used for conveyor renderer optimization. */
	FORCEINLINE void IncrementMovementStalledCounter(float Delta)
	{
		mTimeStalled += Delta;
	}
	
	/*Flushes num frames items didnt move, used for conveyor renderer optimization. */
	FORCEINLINE void FlushMovementStalledCounter()
	{
		mTimeStalled = 0;
		bIsRenderingFrozen = false;
		bWasFrozen = true;
	}
	
	FORCEINLINE bool IsMovementStalled() const			{ return mTimeStalled > NumSecStalledToConsiderFrozen && GIsConveyorFreezingEnabled; }
	FORCEINLINE void SetRenderingFrozen() const			{ bIsRenderingFrozen = true; }
	FORCEINLINE bool IsRenderingFrozen() const			{ return bIsRenderingFrozen; }
	FORCEINLINE bool WasFrozen() const					{ return bWasFrozen; }
	FORCEINLINE void ResetWasFrozen() const				{ bWasFrozen = false;}
	
	bool mPendingUpdateItemTransforms;

private:
	/* Used to block updating when items cannot move.*/
	mutable uint8 mIsStalled:1;

	/* Belts directly connected cannot stall.*/
	uint8 mCanEverStall:1;
	
protected:
	friend class AFGConveyorChainActor;
	friend struct FConveyorChainSplineSegment;
	
	/** Speed of this conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor" )
	float mSpeed;

	/** Length of the conveyor. */
	float mLength;

	/** All the locally simulated resource offsets on the conveyor belt.
	 * This array is an items queue, first items in the array is the last item on the belt. */
	UPROPERTY( Meta = ( NoAutoJson ) )
	FConveyorBeltItems mItems;

	/** First connection on conveyor belt, Connections are always in the same order, mConnection0 is the input, mConnection1 is the output. */
	UPROPERTY( VisibleAnywhere, Category = "Conveyor" )
	class UFGFactoryConnectionComponent* mConnection0;
	/** Second connection on conveyor belt */
	UPROPERTY( VisibleAnywhere, Category = "Conveyor" )
	class UFGFactoryConnectionComponent* mConnection1;

	/** Stores how much space is available on this belt after its tick runs (thread safe way to access how much space there is to enqueue new items) */
	float mCachedAvailableBeltSpace;

	/** When ticking this conveyor should tick this conveyor next */
	UPROPERTY()
	AFGBuildableConveyorBase* mNextConveyor;

	UPROPERTY()
	uint8 mConveyorChainFlags;

	UPROPERTY(Transient)
	TArray<UInstancedStaticMeshComponent*> mFrozenItemsInstancedStaticMeshComponents;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ChainInformation )
	AFGConveyorChainActor* mConveyorChainActor = nullptr;

	UPROPERTY( Replicated )
	int32 mChainSegmentIndex = INDEX_NONE;
	
	/** For conveyor chain support this is a quick way to tell if this base conveyor is a lift or not */
	bool mIsConveyorLift = false;
	
private:
	int16 mLastItemsDirtyKey = -2;

	/** Clearance data generated upon request for this conveyor. */
	TArray< FFGClearanceData > mCachedClearanceData;

	/** Indicates if the factory is within significance distance */
	bool mIsSignificant;

	/** The id for the conveyor bucket this conveyor belongs to */
	int32 mConveyorBucketID = INDEX_NONE;

	/** Temp new item. Used when quick pulling conveyor to conveyor as a temp storage before adding the item. More performant than a scoped allocation every factory tick  */
	FConveyorBeltItem mNewItem;

	float mTimeStalled = 0;
	
	mutable bool bIsRenderingFrozen = false;
	mutable bool bWasFrozen = false;
	
};


