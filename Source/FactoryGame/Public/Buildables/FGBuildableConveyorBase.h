// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "FGRemoteCallObject.h"
#include "FGSignificanceInterface.h"
#include "FGBuildableConveyorBase.generated.h"


using FG_ConveyorItemRepKeyType = uint32;
using FG_ConveyorVersionType = uint32;

enum { FG_CONVEYOR_REP_KEY_NONE = 0 };


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

	UFUNCTION( Reliable, Server, WithValidation, Category = "Use" )
	void Server_OnUse( class AFGBuildableConveyorBelt* target, class AFGCharacterPlayer* byCharacter, uint32 itemRepID, float itemOffset );

	UFUNCTION(Reliable, Server, WithValidation, Category = "Client to Server Report")
	void Server_ReportInvalidStateAndRequestConveyorRepReset(class AFGBuildableConveyorBase* target);


	//UFUNCTION( Reliable, Server, WithValidation, Category = "Sync" )
	//void Server_RequestCleanSync( class AFGBuildableConveyorBelt* target );
};


/**
* Holds data for an item traveling on the conveyor.
*/
USTRUCT()
struct FACTORYGAME_API FConveyorBeltItem
{
	GENERATED_BODY()
public:
	FConveyorBeltItem() :
		Item(),
		Offset( 0.0f )
	{
	}

	explicit FConveyorBeltItem( const FInventoryItem& item ) :
		FConveyorBeltItem()
	{
		Item = item;
	}

	//[Gafgar:Fri/20-11-2020] just explicitly adding these "the rule of 5" to make sure that is not the issue of a bug we are ahving. Once confirmed we can remove them.
	virtual ~FConveyorBeltItem()
	{

	}

	FConveyorBeltItem(const FConveyorBeltItem& b)
	{
		Item = b.Item;
		Offset = b.Offset;
		bIsRemoved = b.bIsRemoved;
		bIsMadeUp = b.bIsMadeUp;
		PredictedRemoveRepVersion = b.PredictedRemoveRepVersion;
		MostRecentConveyorRepKey = b.PredictedRemoveRepVersion;
		ReplicationID = b.ReplicationID;
		ReplicationKey = b.ReplicationKey;
	}

	FConveyorBeltItem(FConveyorBeltItem&& b)
	{
		Item = b.Item;
		Offset = b.Offset;
		bIsRemoved = b.bIsRemoved;
		bIsMadeUp = b.bIsMadeUp;
		PredictedRemoveRepVersion = b.PredictedRemoveRepVersion;
		MostRecentConveyorRepKey = b.PredictedRemoveRepVersion;
		ReplicationID = b.ReplicationID;
		ReplicationKey = b.ReplicationKey;
	}

	const FConveyorBeltItem& operator=(const FConveyorBeltItem& b)
	{
		Item = b.Item;
		Offset = b.Offset;
		bIsRemoved = b.bIsRemoved;
		bIsMadeUp = b.bIsMadeUp;
		PredictedRemoveRepVersion = b.PredictedRemoveRepVersion;
		MostRecentConveyorRepKey = b.PredictedRemoveRepVersion;
		ReplicationID = b.ReplicationID;
		ReplicationKey = b.ReplicationKey;
		return *this;
	}
	const FConveyorBeltItem& operator=(FConveyorBeltItem&& b)
	{
		Item = b.Item;
		Offset = b.Offset;
		bIsRemoved = b.bIsRemoved;
		bIsMadeUp = b.bIsMadeUp;
		PredictedRemoveRepVersion = b.PredictedRemoveRepVersion;
		MostRecentConveyorRepKey = b.PredictedRemoveRepVersion;
		ReplicationID = b.ReplicationID;
		ReplicationKey = b.ReplicationKey;
		return *this;
	}


	/** The type of this item. */
	UPROPERTY()
	FInventoryItem Item;

	/**
	* The offset of this item along the conveyor belt in range [0,LENGTH].
	*/
	UPROPERTY()
	float Offset;
	bool bIsRemoved = false;
	bool bIsMadeUp = false; //If true, it means we had to guesstimate the item due to dropped or missing packets.

	//Sets to a rep key value of the current version on the client when sending a pickup command. 
	//When receiving a package building on this state, it will be reset to FG_CONVEYOR_REP_KEY_NONE, if it's a non FG_CONVEYOR_REP_KEY_NONE value it will on the client be handled like if it's removed. 
	//Making things more responsive, and in 99% of the cases a remove should go through without an issue, meaning this should be a very accurate prediction. However, only remove it visually. Let the item movement and so on not take this into account. Let that be in sync with the server.
	FG_ConveyorVersionType PredictedRemoveRepVersion = FG_CONVEYOR_REP_KEY_NONE;

	FG_ConveyorVersionType MostRecentConveyorRepKey; //used to detect implicit removes and such. To be updated on every delta received that handled this item
	
private:
	friend struct FConveyorBeltItems;

	friend class AFGBuildableConveyorBelt; //[DavalliusA:Mon/03-06-2019] for debugging only for now

	FG_ConveyorItemRepKeyType ReplicationID = FG_CONVEYOR_REP_KEY_NONE;

	FG_ConveyorItemRepKeyType ReplicationKey = FG_CONVEYOR_REP_KEY_NONE;

};


/** Custom INetDeltaBaseState used by our custom NetDeltaSerialize. Representing a snapshot of the state, enough to calculate a delta between this state and another.*/
class FConveyorBeltItemsBaseState : public INetDeltaBaseState
{
public:



	FConveyorBeltItemsBaseState()
	{
	}

	~FConveyorBeltItemsBaseState()
	{
	}

	FConveyorBeltItemsBaseState( const FConveyorBeltItemsBaseState& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ConveyorRepKey = other.ConveyorRepKey;
		lastSentSpacing = other.lastSentSpacing;
		NewestItemID = other.NewestItemID;
		ConveyorVersion = other.ConveyorVersion;
	}

	FConveyorBeltItemsBaseState( FConveyorBeltItemsBaseState&& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ConveyorRepKey = other.ConveyorRepKey;
		lastSentSpacing = other.lastSentSpacing;
		NewestItemID = other.NewestItemID;
		ConveyorVersion = other.ConveyorVersion;
	}

	const FConveyorBeltItemsBaseState& operator=( const FConveyorBeltItemsBaseState& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ConveyorRepKey = other.ConveyorRepKey;
		lastSentSpacing = other.lastSentSpacing;
		NewestItemID = other.NewestItemID;
		ConveyorVersion = other.ConveyorVersion;
		
		return *this; // MODDING EDIT: how does it work without this?
	}

	const FConveyorBeltItemsBaseState& operator=( FConveyorBeltItemsBaseState&& other )
	{
		TypeToBitIDMap = other.TypeToBitIDMap;
		ItemList = other.ItemList;
		ConveyorRepKey = other.ConveyorRepKey;
		lastSentSpacing = other.lastSentSpacing;

		NewestItemID = other.NewestItemID;
		ConveyorVersion = other.ConveyorVersion;
		
		return *this; // MODDING EDIT: how does it work without this?
	}

	//must be implemented
	virtual bool IsStateEqual(INetDeltaBaseState* otherState) override
	{
		FConveyorBeltItemsBaseState* other = static_cast<FConveyorBeltItemsBaseState*>(otherState);
		if (ConveyorVersion != other->ConveyorVersion)
		{
			return false;
		}
		if (ItemList.Num() != other->ItemList.Num())
		{
			return false;
		}
		if (lastSentSpacing != other->lastSentSpacing)
		{
			return false;
		}
		for (int32 i = 0; i < ItemList.Num(); ++i)
		{
			if (ItemList[i] != other->ItemList[i])
			{
				return false;
			}
		}
		for (auto it = TypeToBitIDMap.CreateIterator(); it; ++it)
		{
			auto ptr = other->TypeToBitIDMap.Find(it.Key());
			if (!ptr || *ptr != it.Value())
			{
				return false;
			}
		}
		return true;
	}

	/**Translation of class type to an int id, so we can minimize each send size. Nb elements will be used to find a sed*/
	TMap< TSubclassOf< class UFGItemDescriptor >, uint8 > TypeToBitIDMap;

	struct ItemHolder
	{
		ItemHolder( FG_ConveyorItemRepKeyType _id, bool _removed ) : RepID( _id ), bIsRemoved( _removed ){}
		FG_ConveyorItemRepKeyType RepID = FG_CONVEYOR_REP_KEY_NONE; //Should be in sync on server and client. Unique ID, taken from the RepID on the item. Should be possible to look up an item based on this ID too. (should incremented for every item added to the conveyor and an unbroken series)
		uint8 TypeIndex = -1; //Replicated. assigned on creation should always be up to date. At the moment we never remove types from the type map. If we can do that we should update all these too.
		//uint8 TypeMapVersion; //used to make sure our mapping corresponds to the correct type map version
		
		//[Gafgar:Wed/30-09-2020] this should only be needed for the actual items right? not these delta bases. As they are on server only right?
		//FG_ConveyorVersionType MostRecentConveyorRepKey; //stores the version this item was added/modified. Enables us to find implicit deltes and such.
		
		bool bIsRemoved = false; //so we can detect if the item was removed since last rep.
		bool wasRemovedOnLastDelta = false; //easy way to keep track by keeping this in here, and it fits with the padding of the struct anyway.
	
		inline bool operator!=( const ItemHolder& B ) const
		{
			return B.RepID != RepID || B.bIsRemoved != bIsRemoved;
		}
		inline bool operator==( const ItemHolder& B ) const
		{
			return B.RepID == RepID && B.bIsRemoved == bIsRemoved;
		}
	};

	
	FG_ConveyorItemRepKeyType NewestItemID = FG_CONVEYOR_REP_KEY_NONE; //we need to store it, so we stil lcan send it when the conveyor is empty
	float lastSentSpacing = 0; //used to know what spacing the client will use in case we tell it to use the last spacing.
	TArray<ItemHolder> ItemList; //[DavalliusA:Thu/11-04-2019] see if we can move this to a static size, or templateify the size, so we can keep it in one memory chunk for each history entry.

	
	
	/** The replication key from the conveyor at which this state was created. ACtually replicated as FG_ConveyorVersionType, but looping. We store 32bit so we know the loop */
	uint32 ConveyorRepKey = FG_CONVEYOR_REP_KEY_NONE; //this rep key increments on every change on server that will require replication of the conveyor
	uint32 ConveyorVersion; //will need to be in sync with the conveyor. If this value is different, 
							//there has been a reset in between the replications, and we need to send this as a reset event. 
							//Should only happen when we encounter unrecoverable states, or we run out of space and needs a reset to recover.
	

};


/**
* Struct to help replicate the conveyor belt items array.
* It's a lean version of fast TArray replication that guarantee the same order of the elements on server and client.
* It lacks support for:
*   - Item changes (initial replication only) there is a todo in the source file on how this can be added if needed.
*   - Mapping of object references (objects that are replicated that is). Look at fast TArray replication on how to implement this if needed.
*/
USTRUCT()
struct FConveyorBeltItems
{

	enum class EConveyorSpawnStyle : int8
	{
		CSS_default = -1, //even spacing or if it don't matter/the conveyor is full after the add
		CSS_A_from_front_B_Spacing = 0,
		CSS_A_from_front_burst,
		CSS_Individual,
		CSS_MAX
	};

	

	GENERATED_BODY()

	FConveyorBeltItems();

	FORCEINLINE int16 Num() const
	{
		return ( int16 )Items.Num();
	}

	FORCEINLINE bool IsValidIndex( int16 index ) const
	{
		return Items.IsValidIndex( index );
	}

	FORCEINLINE void Add( const FConveyorBeltItem& item )
	{
		Items.Add( item );
		Items.Last().ReplicationID = FG_CONVEYOR_REP_KEY_NONE;
		MarkItemDirty( Items.Last() );
		if( Items.Num() > 1 )
		{
			//@todomissmatch checkf( Items.Last().ReplicationID == Items[ Items.Num() - 2 ].ReplicationID + 1, TEXT( "Make sure the items build in ID numbers like intended. Otherwise other math will fail later. New item: %d, item before: %d" ), Items.Last().ReplicationID, Items[ Items.Num() - 2 ].ReplicationID );
		}
		NewestItemID = Items.Last().ReplicationID; //[DavalliusA:Mon/06-05-2019] make sure this is always up to date
	}

	//Enforce a good number sequence of items and set counter values to be in sync. Should only be used post load, before network serialization.
	void PostLoadResetAllItemIDs()
	{
		if( Items.Num() > 0 )
		{
			IDCounter = Items[ 0 ].ReplicationID;
			for( auto itm : Items )
			{
				itm.ReplicationID = IDCounter++;
				if( IDCounter == FG_CONVEYOR_REP_KEY_NONE )
				{
					++IDCounter;
				}
			}
			NewestItemID = Items.Last().ReplicationID; //[DavalliusA:Mon/06-05-2019] make sure this is always up to date
		}
		else
		{
			NewestItemID = IDCounter - 1;
		}
	}


	FORCEINLINE void RemoveItemFromListAt( int16 index )
	{
		Items.RemoveAt( index );

		MarkArrayDirty();
	}

	FORCEINLINE bool IsRemovedAt( int16 index ) const
	{
		return Items[ index ].bIsRemoved || !Items[index].Item.IsValid();
	}

	FORCEINLINE void FlagForRemoveAt( int16 index )
	{
		Items[ index ].bIsRemoved = true;
	}

	FORCEINLINE FConveyorBeltItem& operator[]( int16 index )
	{
		return Items[ index ];
	}

	FORCEINLINE const FConveyorBeltItem& operator[]( int16 index ) const
	{
		return Items[ index ];
	}


	int32 GetIndexForItemByRepKey(FG_ConveyorItemRepKeyType itemID) const;

	//Get the item for a given rep ID of an item, but account for the accuracy of the index with the network ID precision
	int32 GetIndexForItemByRepKeyNetBitLimit(uint32 itemID) const;

	FG_ConveyorVersionType GetRepKey() const
	{
		return ArrayReplicationKey;
	}

	FG_ConveyorVersionType GetRepKeyRecived() const
	{
		return ArrayReplicationKeyLastSerialized;
	}
	/** Custom delta serialization. */
	bool NetDeltaSerialize( FNetDeltaSerializeInfo& parms );

	void ApplySpacingToItem(int32 targetIndex, int32 nbReadsDone, EConveyorSpawnStyle spacingStyle, int16 spacingParamA, int16 spacingParamB, uint32 individualSpacingParam);

	/** Used to recover if a non recoverable read state is found. Will cause a fresh relocation of this conveyor to ALL clients, and a visual jump. So use with care. */
	void SignalReadErrorAndRequestReset(FBitReader& reader);

	void CleanupAndSignalVersionChange();

	/** Mark the array dirty. */
	void MarkArrayDirty();

	void UpdateLastestIDFromState();

	/** Custom serialization of all items. */
	friend FArchive& operator<<( FArchive& ar, FConveyorBeltItems& items );


	FORCEINLINE void SetOwner( class AFGBuildableConveyorBase* _owner )
	{
		Owner = _owner;
	}

	FORCEINLINE int16 GetCombinedDirtyKey()
	{
		return ArrayReplicationKey + ArrayReplicationKeyLastSerialized;
	}

	float ConsumeAndUpdateConveyorOffsetDebt( float dt );


	FORCEINLINE TArray< FConveyorBeltItem >& AnimRemoveList()
	{
		return AnimRemoveItems;
	}


	float ConveyorLength; 
	int16 DebugID = INDEX_NONE; //Used for identifying conveyors during debugging and debug prints. And can with a compile flag be synced between clients and servers. not really needed for any logics.
private:
	/** Mark a single item dirty. */
	void MarkItemDirty( FConveyorBeltItem& item );

private:
	/** Counter for assigning new replication IDs. */
	FG_ConveyorItemRepKeyType IDCounter = FG_CONVEYOR_REP_KEY_NONE + 1;

	TMap< TSubclassOf< class UFGItemDescriptor >, uint8 > ClientTypeToBitIDMap;



	TArray< FConveyorBeltItem > Items; //0 = first added item (item to be removed/move out next), max/end/n = newest item/item added most recently.
	TArray< FConveyorBeltItem > AnimRemoveItems; //holding items we should no longer include in logics, and are just rolling out with animation/visually
	FG_ConveyorItemRepKeyType NewestItemID = FG_CONVEYOR_REP_KEY_NONE;

	/** Like a dirty flag. */
	uint32 ArrayReplicationKey = FG_CONVEYOR_REP_KEY_NONE+1;

	uint32 ArrayReplicationKeyLastSerialized = FG_CONVEYOR_REP_KEY_NONE; //Used to not increase the version number when it's not needed. So we can limit how quickly we overflow/go out of range


	float LastRecivedSpacing = 0; //used so we can know what length we last received, so we can apply it when needed. //@TODO:[Gafgar:Wed/04-11-2020] potential problem with dropped packets here as it's not rolled back in any way. But as it's only visual with spacing, it should not be an issue and works for the most time.
	float ConveyorOffsetDebt = 0; //used to adjust for removes and adds that were received with bad timing
	float DeltaSinceLastNetUpdate = 0; //@TODO:[DavalliusA:Tue/11-06-2019] store a time in the delta log, so we can know the time since for the individual deltas? This can get arbitrary quickly...

	uint32 ConveyorVersion = 0; //If incremented, it will cause all deltas with old base states to be reset deltas. If we are making a delta and it's base is different from this, we will treat it as a reset.


	uint8 NumPacketsRecievedWhileWaitingForReset = 0;
	bool bIsAwaitingResetPacket = true; //this means we we've gotten a reset signal from the server and will treat all history events till the next real event differently. Must be true by default, as we expct the frist packet we get to be a reset.


	class AFGBuildableConveyorBase* Owner = nullptr;
	
	friend class AFGBuildableConveyorBelt;
};


/** Enable custom net delta serialization for the above struct. */
template<>
struct TStructOpsTypeTraits< FConveyorBeltItems > : public TStructOpsTypeTraitsBase2< FConveyorBeltItems >
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};


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

	void SetConveyorBucketID( int32 ID );

	FORCEINLINE int32 GetConveyorBucketID() const { return mConveyorBucketID; }

	/** Returns how much room there currently is on the belt. If the belt is empty it will return the length of the belt */
	FORCEINLINE float GetAvailableSpace() const
	{
		for ( int32 i = mItems.Num() - 1; i >= 0; --i )
		{
			if ( !mItems[ i ].bIsRemoved )
			{
				return mItems[ i ].Offset;
			}
		}

		return GetLength();
	}

	/** Returns how much room there was on the belt after the last factory tick. If the belt is empty it will return the length of the belt */
	float GetCachedAvailableSpace_Threadsafe() const;

	void ReportInvalidStateAndRequestConveyorRepReset();

	FORCEINLINE void MarkItemTransformsDirty() { mPendingUpdateItemTransforms = true; }
protected:
	// Begin Factory_ interface
	virtual bool Factory_PeekOutput_Implementation( const class UFGFactoryConnectionComponent* connection, TArray< FInventoryItem >& out_items, TSubclassOf< UFGItemDescriptor > type ) const override;
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface

	// Begin AFGBuildable interface
	virtual void GetDismantleInventoryReturns( TArray< FInventoryStack >& out_returns ) const override;
	// End AFGBuildable interface

	/** Called when the visuals, radiation etc need to be updated. */
	virtual void TickItemTransforms( float dt, bool bOnlyTickRadioActive = true ) PURE_VIRTUAL(,);

	/* When using the exp - conveyor renderer tick the radio activity of the items. */
	virtual void TickRadioactivity() PURE_VIRTUAL(,);
	
	//@todonow These can possibly be moved to private once Belt::OnUse has been moved to base.
	/** Find the item closest to the given location. */
	int32 FindItemClosestToLocation( const FVector& location ) const;

	/** Checks if there is an item at index. */
	bool Factory_HasItemAt( int32 index ) const;
	/** Lets you know what type of item is on a specific index. */
	const FConveyorBeltItem& Factory_PeekItemAt( int32 index ) const;

	/** Remove an item from the belt at index. */
	void Factory_RemoveItemAt( int32 index );

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
	bool HasRoomOnBelt_ThreadSafe( float& out_availableSpace ) const;

	friend class AFGConveyorItemSubsystem;

public:
	/** Default height above ground for conveyors. */
	static constexpr float DEFAULT_CONVEYOR_HEIGHT = 100.f;

	/** Spacing between each conveyor item, from origo to origo. */
	static constexpr float ITEM_SPACING = 120.0f;

protected:

	/** Speed of this conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor" )
	float mSpeed;

	/** Length of the conveyor. */
	float mLength;

	/** All the locally simulated resource offsets on the conveyor belt. */
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	FConveyorBeltItems mItems;

	/** First connection on conveyor belt, Connections are always in the same order, mConnection0 is the input, mConnection1 is the output. */
	UPROPERTY( VisibleAnywhere, Category = "Conveyor" )
	class UFGFactoryConnectionComponent* mConnection0;
	/** Second connection on conveyor belt */
	UPROPERTY( VisibleAnywhere, Category = "Conveyor" )
	class UFGFactoryConnectionComponent* mConnection1;

	/** Stores how much space is available on this belt after its tick runs (thread safe way to access how much space there is to enqueue new items) */
	float mCachedAvailableBeltSpace;

private:
	int16 mLastItemsDirtyKey = -2;
	bool mPendingUpdateItemTransforms;

	/** Indicates if the factory is within significance distance */
	bool mIsSignificant;

	/** The id for the conveyor bucket this conveyor belongs to */
	int32 mConveyorBucketID;

};
