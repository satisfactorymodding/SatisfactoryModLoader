// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "Components/SplineComponent.h"
#include "FGConveyorItem.h"
#include "FGConveyorChainTypes.generated.h"


class UFGItemDescriptor;
class AFGConveyorChainSubsystem;

namespace FGConveyorChainQuickWrap
{
	FORCEINLINE static int FastWrapIndexIncrement( int32 index, int32 size )
	{
		return index + 1 == size ? 0 : index + 1;
	}
	FORCEINLINE static int FastWrapIndexDecrement( int32 index, int32 size )
	{
		return index - 1 == -1 ? size - 1 : index - 1;
	}

	FORCEINLINE static int FastWrapRangeAddition( int32 current, int32 amt, int32 size )
	{
		current += amt;
		do
		{
			current = current >= size ? current - size : current;
		}
		while( current >= size );

		return current;
	}

	FORCEINLINE static int FastWrapRangeSubtraction( int32 current, int32 amt, int32 size )
	{
		current -= amt;
		do
		{
			current = current < 0 ? current + size : current;
		}
		while( current < 0 );

		return current;
	}

}

namespace ConveyorChainNetHelpers
{
	FORCEINLINE static int32 GetNumItemsInWrappedRange( int32 startIndex, int32 endIndex, int32 maxIndex )
	{
		// It wraps around
		if( startIndex > endIndex )
		{
			return ( maxIndex - startIndex ) +  endIndex;
		}
		else
		{
			return (endIndex - startIndex);
		}
	}

	// These are the numbers used to determine which ChainActor class to spawn for a given length of belts/lifts.
	// These numbers are then in turn used in the FGReplicationGraph to set the replication culldistance
	// Tex. If a chain is < 20000.f (200m) in length it gets spawned the default AFGConveyorChainActor.
	// If for example a chain is < 50000.f (500m) we spawn a different parent AFGConveyorChainActor_Medium.
	// We work down and if its just exceptionally long it will get spawned a AFGConveyorChainActor_NoCull which will not reasonably net cull
	constexpr float ChainRepCullDist_Small = 20000.f;
	constexpr float ChainRepCullDist_Medium = 50000.f;
	constexpr float ChainRepCullDist_Large = 100000.f;
	constexpr float ChainRepCullDist_Huge = 300000.f;
	constexpr float ChainRepCullDist_NoCull = 1000000.f; // Just really big so it doesn't cull. May decide to move this to an always relevant node instead

	constexpr uint16 MAX_SIZE_NumRemovals = MAX_uint16;
	constexpr uint16 MAX_SIZE_RemovalDeltaTime = MAX_uint16; 
	constexpr uint16 MAX_SIZE_NumAdditions = MAX_uint16;
	constexpr uint16 MAX_SIZE_AdditionDeltaTime = MAX_uint16;
}

USTRUCT()
struct FACTORYGAME_API FConveyorItemRemovalItem
{
	GENERATED_BODY()

	// How many indices back is this removed (we don't use the items actual index as these aren't synced between server and clients)
	UPROPERTY()
	uint32 IndexDistanceFromFront = 0;

	// Item class index is the subsystems index that maps to a specific item class
	UPROPERTY()
	uint32 ItemClassIndex = MAX_uint16;

	// Used by clients to flag item pickups as handled. For those items we don't want to progress the LastItemRemoval index
	UPROPERTY()
	bool WasHandled = false;
};


/**
 *	This struct is the means by which we replicate Item Removals to a chain. It utilizes deltaserialization
 *	The delta serialization is actually very straightforward and "dumb" to avoid server overhead. Essentially each
 *	item removal to an array is written into a rolling array. The server tracks the last sent index for each client.
 *	When it is determining what to replicate in deltaSerialize it checks the last replicated position in the array and sends all
 *	removals up to the current position in the array. If the server detects that the array has wrapped and eaten its tail for a given client
 *	it sends a control bit to the client indicating it needs a full reset. The client in turn requests a full chain item update for that chain.
 *
 *	The system optimizes data usage by only sending full info when there is an item removed from any index but 0
 *	This is only the case when a player picks up an item. So if there's no specific item pickups we don't bother sending each individual item,
 *	rather just the number of items to remove.
 */
USTRUCT()
struct FACTORYGAME_API FConveyorItemRemovalItems
{
	GENERATED_BODY()

	void Initialize( int32 maxNumRemovals, AFGConveyorChainActor* chainActor )
	{
		RemovalItems.SetNum( maxNumRemovals );
		MaxRemovalItems = maxNumRemovals;
		ChainActor = chainActor;
	}
	
	/** Custom delta serialization. */
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& params );

	void ClientReset( int32 currentIndex )
	{
		LastRemovalIndex = currentIndex;
		CurrentRemovalIndex = currentIndex;
	}
	
	UPROPERTY()
	TArray< FConveyorItemRemovalItem > RemovalItems;

	// Each chain will compute its total Update Time (cumulative of all DeltaTime passed to its factory tick function)
	UPROPERTY()
	float CurrentSubsystemTime = 0.f;

	// The removal items is a fixed size array that we write into and round robin
	UPROPERTY()
	int32 CurrentRemovalIndex = 0;

	// Used by client when they recieve a removal update to track from where they need to apply removals up to the currentRemovalIndex
	UPROPERTY()
	int32 LastRemovalIndex = 0;
	
	// The number of items we track before overwriting is dynamic depending on the speed of the slowest belt in the chain
	UPROPERTY()
	int32 MaxRemovalItems = 0;

	UPROPERTY()
	AFGConveyorChainActor* ChainActor = nullptr;
};

template<>
struct TStructOpsTypeTraits< FConveyorItemRemovalItems > : public TStructOpsTypeTraitsBase2< FConveyorItemRemovalItems >
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};

USTRUCT()
struct FACTORYGAME_API FConveyorItemAdditionItem
{
	GENERATED_BODY()

	UPROPERTY()
	float AddedAtTime = -1.f;

	UPROPERTY()
	TSubclassOf< UFGItemDescriptor > ItemClass = nullptr;
};

/**
 *	This struct is the means by which we replicate Item Additions to a chain. It utilizes deltaserialization
 *	The delta serialization is actually very straightforward and "dumb" to avoid server overhead. Essentially each
 *	item addition to an array is written into a rolling array. The server tracks the last sent index for each client.
 *	When it is determining what to replicate in deltaSerialize it checks the last replicated position in the array and sends all
 *	items up to the current position in the array. If the server detects that the array has wrapped and eaten its tail for a given client
 *	it sends a control bit to the client indicating it needs a full reset. The client in turn requests a full chain update for that chain.
 */
USTRUCT()
struct FACTORYGAME_API FConveyorItemAdditionItems
{
	GENERATED_BODY()

	void Initialize( int32 maxNumAdditions, AFGConveyorChainActor* chainActor )
	{
		AdditionItems.SetNum( maxNumAdditions );
		MaxAdditionItems = maxNumAdditions;
		ChainActor = chainActor;
	}
	
	/** Custom delta serialization. */
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& params );

	void ClientReset( int32 currentIndex)
	{
		LastAdditionIndex = currentIndex;
		CurrentAdditionIndex = currentIndex;
	}
	
	UPROPERTY()
	TArray< FConveyorItemAdditionItem > AdditionItems;

	// Each chain will compute its total Update Time (cumulative of all DeltaTime passed to its factory tick function)
	UPROPERTY()
	float CurrentSubsystemTime = 0.f;

	// The Addition items is a fixed size array that we write into and round robin
	UPROPERTY()
	int32 CurrentAdditionIndex = 0;

	// Used by client when they recieve an addition update to track from where they need to apply additions up to the CurrentAdditionIndex
	UPROPERTY()
	int32 LastAdditionIndex = 0;
	
	// The number of items we track before overwriting is dynamic depending on the speed of the slowest belt in the chain
	UPROPERTY()
	int32 MaxAdditionItems = 0;

	UPROPERTY()
	AFGConveyorChainActor* ChainActor;
};

template<>
struct TStructOpsTypeTraits< FConveyorItemAdditionItems > : public TStructOpsTypeTraitsBase2< FConveyorItemAdditionItems >
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};


/**
 *	A chain actor consists of an array of ChainSplineSegments. These segments represent either a belt or a lift.
 *	Each segment does not actually "own" the items that exist on it. Those are stored on the chain actor itself.
 *	Rather, each segment has a First and Last index that refer to its items position in the chain actors item array.
 *	We then use these segments to determine which items are on a given belt of lift.
 */

USTRUCT()
struct FACTORYGAME_API FConveyorChainSplineSegment
{
	GENERATED_BODY()

public:
	FConveyorChainSplineSegment()=default;
	FConveyorChainSplineSegment( const FConveyorChainSplineSegment& other )=default;
	FConveyorChainSplineSegment( FConveyorChainSplineSegment&& other )=default;
	FConveyorChainSplineSegment& operator=( const FConveyorChainSplineSegment& other )=default;
	FConveyorChainSplineSegment& operator=( FConveyorChainSplineSegment&& other )=default;
	FConveyorChainSplineSegment( class AFGConveyorChainActor* chainActor, class AFGBuildableConveyorBase* conveyorBase, float startsAtOffset, float startsAtLength );

	/** Serialization for saving from Chain Actor */
	friend FArchive& operator<<( FArchive& ar, FConveyorChainSplineSegment& splineSeg );
	
	void Initialize( USplineComponent* splineComponent, float offset );

	/** Initializes the chain segment from replicated data */
	void ClientInitalize( class AFGConveyorChainActor* chainActor, USplineComponent* splineComponent );

	/** Sets the start and end indices this segment is referencing in the chain actor array */
	FORCEINLINE void SetItemIndices( int32 first, int32 last ) { FirstItemIndex = first; LastItemIndex = last; }

	/** This segments position in the chains segment array */
	void SetIndexInChainArray( int32 index );
	
	FORCEINLINE bool IsEmpty() const { return FirstItemIndex == INDEX_NONE; }
	
	/** Remove item from this segment ( shifts indices, doesn't actually add or remove an item. segments don't own items ) */
	void ShiftExistingItemFromFront();
	
	/** Adds an item to the back ( shifts indices, doesn't actually add or remove an item. segments don't own items ) */
	void ShiftExistingItemToBack( int32 index );

	/** Forces an item onto the front of the spline (used when migrating from belts to chains in case item shuffling has pushed the items back ) */
	void ShiftExistingItemToFront( int32 index );

	/** Moves an item off the back of the segment (used when migrating from belts to chains in case item shuffling has pushed items back) */
	void ShiftExistingItemFromBack();
	
	/** When an item is picked up, change First and Last indices accordingly*/
	void RemoveItemFromIndex( int32 index );

	/** When an item was removed in front of use we shift our indices accordingly */
	void ShiftFirstAndLastForItemRemoval();
	
	/** This will only be called by our bulk netserialization of spline point data per chain actor */
	bool NetSerialize( FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess );

	/** Helper for getting the item distance an item ACTUAL starts at along a conveyor (used when converting item positions back to their original belt) */
	FORCEINLINE float GetItemStartsAtLength() const { return StartsAtLength + OffsetAtStart; }

	/** Called from postload to set the speed of the seg. This isn't saved since belt speeds theoretically can change so we apply on load from our conveyor */
	FORCEINLINE void SetSpeed( float inSpeed ) { Speed = inSpeed; } 
	
public:
	UPROPERTY()
	class AFGConveyorChainActor* ChainActor = nullptr;
	
	UPROPERTY()
	class AFGBuildableConveyorBase* ConveyorBase = nullptr;

	UPROPERTY()
	TArray< FSplinePointData > SplinePointData;

	// Our belts / lifts dont actually always meet 1:! so sometimes items need to "teleport" to keep the same total distance
	UPROPERTY()
	float OffsetAtStart = 0.f;

	// How far into the chain this segments position is
	UPROPERTY()
	float StartsAtLength = 0.f;

	// How far in the chain does segment end
	UPROPERTY()
	float EndsAtLength = 0.f;

	// The full length of this spline chain
	UPROPERTY()
	float TotalLength = 0.f;

	// This is grabbed from the conveyor it represents on load
	UPROPERTY()
	float Speed = 0.f;

	// Inclusive
	UPROPERTY()
	int32 FirstItemIndex = INDEX_NONE;

	// Inclusive
	UPROPERTY()
	int32 LastItemIndex = INDEX_NONE;
	
	UPROPERTY()
	int32 IndexInChainArray = INDEX_NONE;
};
