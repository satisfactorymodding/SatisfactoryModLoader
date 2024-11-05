// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "FGConveyorChainTypes.h"
#include "FGSaveInterface.h"
#include "Engine/NetConnection.h"
#include "GameFramework/Actor.h"
#include "FGConveyorChainActor.generated.h"

struct FConveyorItemSpacingRange;
struct FConveyorItemDescRange;
class AFGBuildableConveyorBase;


UCLASS()
class FACTORYGAME_API AFGConveyorChainActor : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	AFGConveyorChainActor();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Serialize( FArchive& ar ) override;

	void BuildLUT();

	bool bHasValidLUT = false;
	
	/*
	*	On Server we want to know when this actor is culled for a connection. When it is culled we clear the removal/addition index
	*	so we will not erroneous start replicate deltas before the client actually has requested the spline or item update if the client
	*	receives this chain again in the future
	*/
	virtual void NotifyActorChannelClosedForNetConnection(UNetConnection* NetConnection) override;
	// End AActor Interface

	// Begin Impostor Factory Functions
	void Factory_Tick( float deltaTime );
	void Factory_EnqueueItem( const FInventoryItem& item, float initialOffset, float timeDebt = 0.f);
	bool Factory_PeekOutput( TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type = nullptr );
	bool Factory_GrabOutput( FInventoryItem& out_item, TSubclassOf< UFGItemDescriptor > type = nullptr );
	void Factory_RemoveItemAt( int32 index, TSubclassOf< UFGItemDescriptor> expectedClass );
	// End Imposter Factory Functions

	// Core logic for removing an item from the array
	void RemoveItemAt_Internal( int32 index );
	
	// Begin Save Interface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End Save Interface

	// Utilizing deferred spawn we assign the start and end conveyors before any processing
	void SetStartAndEndConveyors( AFGBuildableConveyorBase* start, AFGBuildableConveyorBase* end );

	// Called on post load - removes any conveyor items that may no longer be valid
	void SanitizeItemsFromLoad();
	
	/*
	 *	Register with Subsytem which will in turn build the chain
	 *	On Client and Server we build the spline chain. However on client it may have to wait for replication
	 *	On Server only we copy the items from the belts (these in turn will be replicated to the client via RPCs on request)
	 */
	void RegisterWithSubsystem();

	// When a conveyor is removed we are notified. This will cause the chain to self delete. Copying its information back onto the belts the remain
	void RevertChainActor();
	
	// Called by the Subsystem when this belt registers on begin play
	bool BuildChain();

	// Builds the spline component (should already have its points added) and sets the reparam table size
	void RebuildSplineComponent( int32 reparamStepsPerSeg );

	// Called when building. Copies all items from their belts into the chain and removes the items from the belts
	void MoveItemsFromBeltsToChain();

	// Called when Destructing (a belt was likely dismantled)
	void MoveItemsFromChainToBelts();

	// Called when Destructing by clients. This migration occurs just to create a visual temporarily for clients so items dont disappear and reapper)
	void ClientMoveItemsFromChainToBelts();

	// CLIENT ONLY - Called when splineSegment Data has been replicated fully for this actor. Builds the spline Component and notifies subsystem we are ready for an Item update
	void NetUpdateBuildSpline();

	// CLIENT ONLY - Called when we receive a bulk data update from the conveyor chain RCO to create and apply item ranges
	void NetUpdateBuildItemsFromRanges(int32 numItems, const TArray< FConveyorItemDescRange >& descRanges, const TArray< FConveyorItemSpacingRange >& spacingRanges, int32 currentRemovalIndex, int32 currentAdditionIndex );

	// CLIENT ONLY - When delta rep detects this chain is too far out of sync it needs a full rebuild
	void MarkChainForItemUpdate();
	
	// Returns the number of items in a given segment
	int32 GetNumItemsInSegment(const FConveyorChainSplineSegment& splineSegment ) const;

	// Returns the number of items between the LeadItemIndex and the TailItemIndex. Ie. The total number of ACTUAL items on a belt
	int32 GetNumActualItems() const;

	// Returns true if the given index falls within the On or In the range between mLeadItemIndex and mTailItemIndex
	bool IsItemIndexValid( int32 index ) const;

	/** Does this index fall inside this segment? */
	bool IsItemIndexValidForSegment( FConveyorChainSplineSegment* segment, int32 index ) const;

	// Returns the distance (number of indices) an item is from the mLeadItemIndex
	int32 GetIndexDistanceFromLeadItem( int32 index ) const;

	/** Returns the item from a given index */
	FConveyorBeltItem* GetItemForIndex( int32 index );

	// Gets an array of the elements in a given conveyor
	void GetItemsForSegment( class AFGBuildableConveyorBase* conveyorBase, TArray< FConveyorBeltItem* >& out_Items );
	void GetItemsForSegmentIndex( int32 segIndex, TArray< FConveyorBeltItem* >& out_Items);

	// Finds the item closest to a location. This takes conveyor and an offset along that belt. This is called by the belts themselves
	FConveyorBeltItem* FindItemClosestToLocation(  const FVector& location, bool discountLifts, int32& out_ItemIndex, TSubclassOf< class UFGItemDescriptor > desiredClass = nullptr );
	FConveyorBeltItem* FindItemClosestToOffset( float offset, float maxDistance, bool discountLifts,  int32& out_ItemIndex, TSubclassOf< class UFGItemDescriptor > desiredClass = nullptr );

	// Called from conveyor belts when they receive a Use RPC from the client. 
	FConveyorBeltItem* FindItemPickupForClient( float offset, TSubclassOf< UFGItemDescriptor > desiredClass, int32& out_ItemIndex );

	// Gets the Location and Rotation of an item in world space
	FVector GetLocationAtDistanceAlongSpline( float offset,  ESplineCoordinateSpace::Type cordSpace ) const;
	
	// Gets the Location and Rotation of an item in world space
	void GetLocationAndRotationOfItem( int32 index, FVector& out_Location, FRotator& out_Rotation );
	
	// Gets the distance along the spline closest to the location
	float FindOffsetClosestToLocation( const FVector& location );

	// Returns the segment for a given base conveyor
	FConveyorChainSplineSegment* GetSegmentForConveyorBase(  AFGBuildableConveyorBase* conveyorBase );

	// Returns the segment for a given item index (this is intended for debugging)
	FConveyorChainSplineSegment* GetSegmentForItemIndex( int32 itemIndex );

	// Given an offset this is the segment that "offest" falls in
	FConveyorChainSplineSegment* GetSegmentForOffset( float offset );

	FORCEINLINE bool HasRoomOnChain( float& out_availableSpace );
	float GetAvailableSpace();

	FORCEINLINE int32 GetNumChainSegments() const { return mChainSplineSegments.Num(); }
	FORCEINLINE bool HasBuildChainSegments() const { return mChainSplineSegments.Num() > 0; }

	// Sets the conveyor items array to its maximum size - called on both client and server but at different points
	void InitializeConveyorItemArray();

	// Client has received a conveyor via replication add it to our list of available
	void AddClientAvailableConveyor( class AFGBuildableConveyorBase* conveyorBase );
	// A conveyor was removed that belonged to this chain (may not actually be deleted but rather just net culled)
	void RemoveClientAvailableConveyor( class AFGBuildableConveyorBase* conveyorBase );
	// Client only function for actually removing the items notified by the item removal array
	void HandleClientRemovals();
	// Client only function for actually removing the items notified by the item removal array
	void HandleClientAdditions();

	// Adds an entry to the connection map so we know where to pick up when DeltaSerialization takes over the replication
	void AddConnectionEntryForItemStateIndices( UNetConnection* connection );
	// Clears an entry into the connection map. Used when a chain actor is net culled so we don't attempt to replicate deltas
	void RemoveConnectionEntryForItemStateIndices( UNetConnection* connection );

	// Used by splitters to help build efficient distribution tables
	virtual uint8 EstimatedMaxNumGrab_Threadsafe( float estimatedDeltaTime ) const;
	
	/** Returns how much room there was on the belt after the last factory tick. If the belt is empty it will return the length of the belt */
	FORCEINLINE float GetCachedAvailableSpace_Threadsafe() const
	{
		return mCachedAvailableBeltSpace;
	}

	float GetAndUseTimeDebtForItem( int32 itemIndex, float dt );
	
private:
	void DebugDrawChainInfo();
	void DebugDrawItemTimeDebt( int32 itemIndex );
	
private:
	friend struct FConveyorChainSplineSegment;
	friend struct FConveyorChainItemRPCData;
	friend struct FConveyorChainSegmentRPCData;
	friend struct FConveyorItemRemovalItems;
	friend struct FConveyorItemAdditionItems;
	friend class AFGConveyorItemSubsystem;
	
	UPROPERTY( EditAnywhere )
	USceneComponent* mSceneComponent;
	
	UPROPERTY( EditAnywhere )
	USplineComponent* mSplineComponent;

	UPROPERTY()
	TArray< FConveyorChainSplineSegment > mChainSplineSegments;

	// Quick way of resolving conveyors to their segment so the renderer can quickly get all the items for a given belt/lift
	UPROPERTY()
	TMap< AFGBuildableConveyorBase*, int32 > mConveyorToSplineSegment; 

	// This array size is set on initialization of the chain and will never resize
	UPROPERTY()
	TArray< FConveyorBeltItem > mConveyorChainItems;
	
	// The conveyor at the front of the chain ie. The one that will be grabbed from by a buildable
	UPROPERTY()
	class AFGBuildableConveyorBase* mFirstConveyor = nullptr;

	// The conveyor at the end of a chain ie. The one that will be pulling from a buildable
	UPROPERTY()
	class AFGBuildableConveyorBase* mLastConveyor = nullptr;

	// The "first" connection of the "last" conveyor. That is, the connection component that grabs items from buildings onto the chain
	UPROPERTY()
	class UFGFactoryConnectionComponent* mConnection0;

	// The "last" connection of the "first" conveyor. That is, the connection component that buildings will pull items off the chain from
	UPROPERTY()
	class UFGFactoryConnectionComponent* mConnection1;

	UPROPERTY( Replicated)
	float mTotalLength;

	// Index of the item at the front of the line - Inclusive
	UPROPERTY( )
	int32 mLeadItemIndex = INDEX_NONE;

	// Index of the item at the back of the line - Inclusive
	UPROPERTY( )
	int32 mTailItemIndex = INDEX_NONE;

	// Replicated Removals
	UPROPERTY( Replicated )
	FConveyorItemRemovalItems mItemRemovals;
	
	// Replicated Additions
	UPROPERTY( Replicated )
	FConveyorItemAdditionItems mItemAdditions;

	// We use the subsystem a lot so cache it so we don't need frequent Gets
	UPROPERTY()
	class AFGConveyorChainSubsystem* mConveyorChainSubsystem;

	// Map of connections to the current replication index of removals
	UPROPERTY()
	TMap< UNetConnection*, int32 > mConnectionToBaseStateRemovalIndex;

	// Map of connections to the current replication index of additions
	UPROPERTY()
	TMap< UNetConnection*, int32 > mConnectionToBaseStateAdditionIndex;

	// For quicker iteration store the connection map keys here
	UPROPERTY()
	TArray< UNetConnection* > mNetConnectionKeys;

	// Cached list of Conveyors that "belong" to this chain. This is used client side as conveyors are added and removed
	// we do this so we can assign a chain to a segment when its actually available. This in turn is used by the conveyor
	// item subsystem to render the items
	UPROPERTY()
	TArray< class AFGBuildableConveyorBase* > mClientAvailableConveyors;

	// Size (num) of the chain item array. Cached to avoid numberous .Num() calls since this never changes
	UPROPERTY( )
	int32 mNumItems = 0;

	// Based on the speed of the slowest belt. This is replicated so clients can initialize the item removal / addition arrays to the same size as the server
	UPROPERTY( Replicated )
	float mSpeedOfSlowestBelt = 0.f;

	// Total number of chain segments (just to avoid frequent .Num() calls)
	int32 mNumChainSegments = 0;

	// For clients whether or not they should attempt to assign conveyors to segments
	bool mClientAvailableConveyorsChanged = false;

	/** Stores how much space is available on this belt after its tick runs (thread safe way to access how much space there is to enqueue new items) */
	float mCachedAvailableBeltSpace;

	bool mFirstItemUpdate = false;
};

UCLASS()
class FACTORYGAME_API AFGConveyorChainActor_RepSizeMedium : public AFGConveyorChainActor
{
	GENERATED_BODY()
};

UCLASS()
class FACTORYGAME_API AFGConveyorChainActor_RepSizeLarge : public AFGConveyorChainActor
{
	GENERATED_BODY()
};

UCLASS()
class FACTORYGAME_API AFGConveyorChainActor_RepSizeHuge : public AFGConveyorChainActor
{
	GENERATED_BODY()
};

// Larger than Huge just don't cull. This should be very rare but can definitely happen.
UCLASS()
class FACTORYGAME_API AFGConveyorChainActor_RepSizeNoCull : public AFGConveyorChainActor
{
	GENERATED_BODY()
};

