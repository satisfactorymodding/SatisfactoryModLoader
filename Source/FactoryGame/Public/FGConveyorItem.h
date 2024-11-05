// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "FGConveyorItem.generated.h"

struct FACTORYGAME_API FPreviousFrameLocationData
{
	explicit FPreviousFrameLocationData(const FMatrix& inTransform)
	{
		mTransform = inTransform;
		mPrevTransform = inTransform;
	}

private:
	FMatrix mTransform;
	FMatrix mPrevTransform;

	friend struct FConveyorBeltItem;
	friend class AFGConveyorItemSubsystem;
};



/**
 * Holds data for an item traveling on the conveyor.
 *
 * @note This item must not contain any object references as they will not get replicated correctly.
 * @note We do not yet support changes to variables, only initial replication will be done.
 */
USTRUCT()
struct FConveyorBeltItem
{
	GENERATED_BODY()

	/** Ctor */
	FConveyorBeltItem() :
		Item(),
		Offset( 0.0f )
	{
	}

	/** Ctor */
	explicit FConveyorBeltItem( const FInventoryItem& item ) :
		FConveyorBeltItem()
	{
		Item = item;
	}

	/** The type of this item. */
	UPROPERTY()
	FInventoryItem Item;

	/**
	 * The offset of this item along the conveyor belt in range [0,LENGTH].
	 */
	UPROPERTY()
	float Offset;

	// For chain actors (notably for lifts) this is the offset into the portion of the segment that it is on
	UPROPERTY()
	float LocalOffset;
	
	/** Client Only - Used to track how far behind (or maybe ahead) an item is based on time */
	UPROPERTY( NotReplicated )
	float TimeDebt = 0.f;

	UPROPERTY()
	float DistanceMoved = 0;
	
private:
	friend struct FConveyorBeltItems;
	friend class AFGConveyorChainActor;
};


/**
* Legacy Support Struct. Items used to be replicated via DeltaSerialize. This is no longer the case.
* This whole struct could be removed via save data migration.
*/
USTRUCT()
struct FConveyorBeltItems
{
	GENERATED_BODY()

	/** Ctor */
	FConveyorBeltItems() :
		IDCounter( 0 ),
		ArrayReplicationKey( INDEX_NONE )
	{
	}

	FORCEINLINE int32 Num() const
	{
		return Items.Num();
	}

	FORCEINLINE bool IsValidIndex( int32 index ) const
	{
		return Items.IsValidIndex( index );
	}

	FORCEINLINE void Add( const FConveyorBeltItem& item )
	{
		Items.Add( item );
	}

	FORCEINLINE void RemoveAt( int32 index )
	{
		Items.RemoveAt( index );
	}

	void Empty()
	{
		Items.Empty();
	}

	FORCEINLINE FConveyorBeltItem& operator[]( int32 index )
	{
		return Items[ index ];
	}

	FORCEINLINE const FConveyorBeltItem& operator[]( int32 index ) const
	{
		return Items[ index ];
	}

	FORCEINLINE void SetOwner( class AFGBuildableConveyorBase* _owner )
	{
		Owner = _owner;
	}


	/** Custom serialization of all items. */
	friend FArchive& operator<<( FArchive& ar, FConveyorBeltItems& items );

	FORCEINLINE bool IsRemovedAt( int16 index ) const
	{
		return !Items[index].Item.IsValid();
	}
	
	FORCEINLINE void RemoveItemFromListAt( int16 index, bool bMarkDirty = true )
	{
		Items.RemoveAt( index );
	}

	FORCEINLINE FConveyorBeltItem& GetItemUnsafe( int16 index )
	{
		return Items.GetData()[index];
	}

	FORCEINLINE const FConveyorBeltItem& GetItemUnsafe( int16 index ) const
	{
		return Items.GetData()[index];
	}

private:

private:
	friend class AFGConveyorChainActor;
	friend class AFGBuildableConveyorBase;
	friend class AFGBuildableConveyorBelt;
	friend class AFGBuildableConveyorLift;
	
	/** Counter for assigning new replication IDs. */
	UPROPERTY( NotReplicated )
	int32 IDCounter;

	/** This maps ReplicationID to our local index into the Items array */
	UPROPERTY( NotReplicated )
	TMap< int32, int32 > ItemMap;

	/** The items on the conveyor belt. */
	UPROPERTY()
	TArray< FConveyorBeltItem > Items;

	/** Like a dirty flag. */
	UPROPERTY( NotReplicated )
	int32 ArrayReplicationKey;

public:
	UPROPERTY( NotReplicated )
	float ConveyorLength;
	class AFGBuildableConveyorBase* Owner = nullptr;
};
