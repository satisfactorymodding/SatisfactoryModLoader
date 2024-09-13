// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "Replication/FGConditionalPropertyReplicator.h"
#include "Replication/FGConditionalReplicationInterface.h"
#include "FGSaveInterface.h"
#include "Resources/FGItemDescriptor.h"
#include "FactoryGame.h"
#include "FGDynamicStruct.h"
#include "Templates/SubclassOfField.h"
#include "FGInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FInventoryResized, int32, oldSize, int32, newSize );

/**
 * Describes an item that can be placed in the inventory.
 * An item has a type and optionally a state.
 * E.g. a weapon is of type 'Desc_NailGun' and has the state '9 nail loaded'.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FInventoryItem
{
	GENERATED_BODY()
public:
	/** A null item. */
	static const FInventoryItem NullInventoryItem;

public:
	FInventoryItem();
	explicit FInventoryItem( TSubclassOf< class UFGItemDescriptor > itemClass );

	/** Function called when serializing this struct to a FArchive. */
	bool Serialize( FArchive& ar );
	friend FArchive& operator<<( FArchive& ar, FInventoryItem& item );

	/** @return true if this is a valid item; otherwise false. */
	FORCEINLINE bool IsValid() const { return ItemClass != nullptr; }
	//FORCEINLINE bool IsValid() const { return ::IsValid( ItemClass ); }

	/** @return true if this item has a state; otherwise false. */
	FORCEINLINE bool HasState() const { return ItemState.IsValid(); }

	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetItemClass() const { return ItemClass; }
	FORCEINLINE const FFGDynamicStruct& GetItemState() const { return ItemState; }

	void SetItemClass(TSubclassOf< class UFGItemDescriptor > NewItemClass );
	void SetItemState( const FFGDynamicStruct& NewItemState );

	FORCEINLINE int32 GetItemStackSize() const { return CachedStackSize; }

	// Used to convert a legacy ItemStateActor to the new format.
	// Should only be called on the Authority side in cases where the Item is not stored in the Inventory. The FGInventoryComponent
	// handles the conversion automatically
	void Internal_ConvertLegacyItemState();

	// TODO make private later.
	/** Cached size of the item */
	mutable int32 CachedStackSize = INDEX_NONE;
	
private:
	/** The type of item */
	UPROPERTY( EditAnywhere )
	TSubclassOf< class UFGItemDescriptor > ItemClass;

	/** Optionally store an actor, e.g. an equipment, so we can remember it's state. */
	UPROPERTY( EditAnywhere )
	FFGDynamicStruct ItemState;
public:
	/** Legacy actor for the item state. We have to store it upon laod because killing actors during Serialize is risky */
	UPROPERTY( Transient )
	AActor* LegacyItemStateActor{};
};

/** Enable custom serialization of FInventoryItem */
template<>
struct TStructOpsTypeTraits< FInventoryItem > : public TStructOpsTypeTraitsBase2< FInventoryItem >
{
	enum
	{
		WithSerializer = true,
		WithCopy = true
	};
};



/**
 * Struct containing a stack of items, stacks is what the inventory handles.
 * When handling single items outside an inventory, i.e. conveyor belt, the FInventoryItem struct is used.
 * Note that single items in the inventory is described as a stack with 1 item.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FInventoryStack
{
	GENERATED_BODY()
public:
	FInventoryStack();
	explicit FInventoryStack( const FInventoryItem& item );
	FInventoryStack( int32 numItems, TSubclassOf< class UFGItemDescriptor > itemClass );

	/** @return true if this stack has any items; false if the stack is empty. */
	FORCEINLINE bool HasItems() const
	{
		return NumItems > 0 && Item.IsValid();
	}

public:
	/** Type of item in this stack. */
	UPROPERTY( EditAnywhere, SaveGame )
	FInventoryItem Item;

	/** Number of items in this stack. */
	UPROPERTY( EditAnywhere, SaveGame )
	int32 NumItems;

	/* */
	int32 CachedMaxStackSize = INDEX_NONE;
};
FORCEINLINE bool IsValidForLoad( const FInventoryStack& element ){ return element.Item.GetItemClass() != nullptr; }

template<>
struct TStructOpsTypeTraits<FInventoryStack> : public TStructOpsTypeTraitsBase2<FInventoryStack>
{
	enum
	{
		WithCopy = true
	};
};

/** Others can hook up to this to allow/disallow items */
DECLARE_DELEGATE_RetVal_TwoParams( bool, FItemFilter, TSubclassOf< UObject >, int32 );

DECLARE_DELEGATE_RetVal_TwoParams( bool, FFormFilter, TSubclassOf< UFGItemDescriptor >, int32 );

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams( FVector, FGetItemDropLocation, const class UFGInventoryComponent*, component, FInventoryStack, stack );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnItemAdded, TSubclassOf< UFGItemDescriptor >, itemClass, int32, numAdded, UFGInventoryComponent*, sourceInventory );

// Speedy Delegate to avoid dynamic or blueprint exposed calls for quick factory events
DECLARE_DELEGATE_ThreeParams( FOnItemAdded_Native, TSubclassOf< UFGItemDescriptor >, int32, UFGInventoryComponent* );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnItemRemoved, TSubclassOf< UFGItemDescriptor >, itemClass, int32, numRemoved, UFGInventoryComponent*, targetInventory );

// Speedy Delegate to avoid dynamic or blueprint exposed calls for quick factory events
DECLARE_DELEGATE_ThreeParams( FOnItemRemoved_Native, TSubclassOf< UFGItemDescriptor >, int32, UFGInventoryComponent* );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSlotUpdated, int32, index );

/**
 * @brief Handles the different parts of the inventory for a actor
 * Composed of several UFGInventoryComponents that does all the dirty work, this
 * object just collects them together and gives access to them
 * The outer object of this object needs to implement GetWorld
 */
UCLASS( BlueprintType, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGInventoryComponent : public UActorComponent, public IFGSaveInterface, public IFGConditionalReplicationInterface
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	UFGInventoryComponent();

	//~ Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	virtual void PostLoad() override;
	//~ End UObject interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGConditionalReplicationInterface
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual bool IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const override;
	// End IFGConditionalReplicationInterface

	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	// End UActorComponent interface

	/**
	* The default size of this inventory.
	*
	* @param defaultSize How many item slots does this component have as default
	*/
	void SetDefaultSize( int32 defaultSize = 1 );

	/**
	 * Changes the size of the inventory to something else than 1
	 *
	 * @param newSize How many item slots does this component have
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void Resize( int32 newSize = 1 );

	/**
	 * Sorts the inventory in alphabetic order in the following manner:
	 * 1) Equipment
	 * 2) other
	 **/
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void SortInventory();

	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SortInventory();

	/** Checks if our owner has authority, and assumes that if they have, then so do we */
	UFUNCTION( BlueprintCallable, Category = "Networking" )
	bool HasAuthority() const;

	//@todoinventory REFACTOR we need to consider state here somehow.
	/** @return true if the item is allowed in this inventory */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	bool IsItemAllowed( const TSubclassOf< UFGItemDescriptor > itemClass, const int32 idx = -1 ) const; //INDEX_NONE

	/**
	 * @return true if the index is a valid index.
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE bool IsValidIndex( const int32 idx ) const
	{
		return idx >= 0 && idx < mInventoryStacks.Num();
	}

	/**
	 * @return first empty index, -1 if none is found
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 FindEmptyIndex() const;

	/**
	* Returns the first slot index that has any items on it
	* If nothing exists in inventory -1 is returned
	*/
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 GetFirstIndexWithItem( int32 StartIndex = 0) const;

	/**
	 * Returns the first slot index that has an item of the specified type in it
	 * If nothing is found it will return -1
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 FindFirstIndexWithItemType( TSubclassOf<UFGItemDescriptor> itemDescriptor, int32 startIndex = 0 ) const;
	
	/**
	 * Adds one item to the inventory.
	 */
	FORCEINLINE bool AddItem( const FInventoryItem& item )
	{
		return AddStack( FInventoryStack( item ) ) == 1;
	}

	/**
	 * Tries to add an item to our inventory, stack it if possible.
	 * @note Server only
	 * @param stack - The stack to be added.
	 * @param allowPartialAdd - If true we add what we can and ignore the rest; otherwise it assumes everything fits and warns otherwise.
	 *                          @note It is the callers responsibility to take care of the items that where not added.
	 *
	 * @return Number of items added, may be less than the input if partial adds are allowed.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	virtual int32 AddStack( const FInventoryStack& stack, const bool allowPartialAdd = false );

	/**
	 * Add the given items to the inventory.
	 * @note Server only
	 *
	 * @param stacks - Stacks to add, caller must ensure that the stacks fit in the inventory.
	 *
	 * @note It is the callers responsibility to ensure that the inventory has enough space to store the items.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void AddStacks( UPARAM( ref ) const TArray< FInventoryStack >& stacks );

	/**
	 * Tries to add an Inventory Stack to our inventory at a given index, stack it if possible.
	 * @note Server only
	 *
	 * @param idx - A valid index in mInventoryStacks.
	 * @param stack - The stack to add.
	 * @param allowPartialAdd - If true we add what we can and ignore the rest; otherwise it assumes everything fits and warns otherwise.
	 *                          @note It is the callers responsibility to take care of the items that where not added.
	 * @param sourceInventory - The origin of the added stack, if applicable.
	 *
	 * @return Number of items added, may be less than the input if partial adds are allowed.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	virtual int32 AddStackToIndex( const int32 idx, const FInventoryStack& stack, const bool allowPartialAdd = false, UFGInventoryComponent* sourceInventory = nullptr );

	FORCEINLINE int32 AddSingleItemToEmptyIndex_Unsafe( const int32 idx, const FInventoryItem& item )
	{
		if ( item.IsValid() )
		{
			FInventoryStack& stackAtIdx = mInventoryStacks[ idx ];

			stackAtIdx.Item = item;
			stackAtIdx.NumItems = 1;

			OnItemsAdded( idx, 1 );
	
			return 1;
		}
		return 0;
	}

	/**
	 * Get the stack of a slot.
	 * @note true if valid index, it is the callers responsibility to check if the slot contains a stack or not.
	 *
	 * @param idx - A valid index in mInventoryStacks.
	 * @param out_stack - The stack on the location. If not a valid index this is undefined.
	 *
	 * @return true if valid index; false otherwise.
	 */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Inventory" )
	bool GetStackFromIndex( const int32 idx, FInventoryStack& out_stack ) const;

	/**
	 * Removes the number of specified items from the inventory.
	 * @note Server only
	 *
	 * @param itemClass - Type of items to remove.
	 * @param num - Number of items to remove. Must be >= 0. If count is more than the items available, a partial remove is done and a warning is raised.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void Remove( TSubclassOf< UFGItemDescriptor > itemClass, int32 num );

	/**
	 * Removes number of items in the specified index.
	 * @note Server only
	 *
	 * @param idx - A valid index in mInventoryStacks.
	 * @param num - Number of items to remove. Must be >= 0. If count is more than the items available, nothing is removed.
	 * @param targetInventory - The destination for the removed items, if applicable.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void RemoveFromIndex( const int32 idx, const int32 num, UFGInventoryComponent* targetInventory = nullptr );

	/** Clears the index, ALL items will be forever gone! */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void RemoveAllFromIndex( const int32 idx, UFGInventoryComponent* targetInventory = nullptr );

	/** Check if the entire inventory is empty. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE bool IsEmpty() const
	{
		for( const FInventoryStack& stack : mInventoryStacks )
		{
			if( stack.HasItems() )
			{
				return false;
			}
		}
		return true;
	}

	/** Check if the given index is empty. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE bool IsIndexEmpty( const int32 idx ) const
	{
		if( UNLIKELY( !IsValidIndex( idx ) ) )
		{
			UE_LOG( LogGame, Warning, TEXT( "RemoveFromIndex failed cause invalid index (%i) in component '%s'" ), idx, *GetName() );
			return false;
		}
		
		return !mInventoryStacks[ idx ].HasItems();
	}

	FORCEINLINE bool IsIndexEmpty_Unsafe( const int32 idx ) const
	{
		return !mInventoryStacks[ idx ].HasItems();
	}
	
	/** Opposite of IsIndexEmpty */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE bool IsSomethingOnIndex( const int32 idx ) const
	{
		return !IsIndexEmpty( idx );
	}

	/** Clears the inventory, ALL items will be forever gone! */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void Empty();

	/**
	 * Check if the inventory has the given items, good for checking building costs etc.
	 *
	 * @param itemClass - Item type to check.
	 * @param num - Item amount to check.
	 *
	 * @return - true if the inventory has the amount requested.
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	bool HasItems( TSubclassOf< UFGItemDescriptor > itemClass, int32 num ) const;

	/**
	 * Get the number of items we have of the specified class.
	 *
	 * @param itemClass - The items class. If null then all items are counted.
	 *
	 * @return Total amount of the item we have in the inventory.
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 GetNumItems( TSubclassOf< UFGItemDescriptor > itemClass ) const;

	/**
	 * Check if the inventory has enough space to store the given items.
	 * @param stacks - Stacks to check enough space for.
	 * @return - true if the items can be stored in the inventory; false if the inventory has insufficient space or the type for any of the items cannot be stored in this inventory.
	 *
	 * @note This can be slow for large inventories and item quantities as it need to check every grid location, try stacking and consider stacking limits etc.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	bool HasEnoughSpaceForStacks( const TArray< FInventoryStack >& stacks ) const;

	/** Check if the inventory has enough space to store the given items. */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	bool HasEnoughSpaceForStack( const FInventoryStack& stack ) const;

	/** @return true if we have enough space for the item; false if not or not allowed. */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	FORCEINLINE bool HasEnoughSpaceForItem( const FInventoryItem& stack ) const
	{
		return HasEnoughSpaceForStack( FInventoryStack( stack ) );
	}

	/** Set the state for items at slot. */
	void SetStateOnIndex( int32 index, const FFGDynamicStruct& itemState );

	/** The total size of the inventory, when accessing inventory linearly using indices. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE int32 GetSizeLinear() const { return mInventoryStacks.Num(); }

	/** Returns index of the stack that has percentually the most items */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 GetFullestStackIndex();

	/** Get all stacks that's in the players inventory */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	void GetInventoryStacks( TArray< FInventoryStack >& out_stacks, const bool getEmptyStacks = false ) const;

	/** Returns the indexes of relevant stacks depending on the given items classes, 
	indexes are sorted first by class and secondly in ascending stack size */ 
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	TArray<int32> GetRelevantStackIndexes( TArray< TSubclassOf< class UFGItemDescriptor > > relevantClasses, int32 stackLimit = -1, bool sortResult = false );

	/** Called when this inventory has been resized */
	UPROPERTY( BlueprintAssignable, Transient, Category = "Inventory", DisplayName = "OnInventoryResized" )
	FInventoryResized ResizeInventoryDelegate;

	/** Called when this inventory has something added to it, @note: Client does not guarantee order of Added/Remove delegate */
	UPROPERTY( BlueprintAssignable, Transient, Category = "Inventory", DisplayName = "OnItemAdded" )
	FOnItemAdded OnItemAddedDelegate;
	
	/** Called when something has been removed from the inventory, @note: Client does not guarantee order of Added/Remove delegate */
	UPROPERTY( BlueprintAssignable, Transient, Category = "Inventory", DisplayName = "OnItemRemoved" )
	FOnItemRemoved OnItemRemovedDelegate;

	/** Called when something is removed from the inventory (this is a quick version of the above to be used in performance critical areas) */
	FOnItemRemoved_Native OnItemRemovedDelegate_Native;
	
	/** Called when inventory slot for a specific index have been updated. Something was added/removed what items are allowed on slot. on @note: Client does not guarantee order of index updates */
	UPROPERTY( BlueprintAssignable, Transient, Category = "Inventory", DisplayName = "OnSlotUpdated" )
	FOnSlotUpdated OnSlotUpdatedDelegate;

	/** Called when something is added from the inventory (this is a quick version of the above to be used in performance critical areas) */
	FOnItemAdded_Native OnItemAddedDelegate_Native;

	/** Adds or replaces a arbitrary size for a slot. */
	UFUNCTION( BlueprintCallable, Category = "Slot Size" )
	void AddArbitrarySlotSize( int32 index, int32 arbitrarySlotSize );

	/** Removes an Arbitrary size for a slot. */
	UFUNCTION( BlueprintCallable, Category = "Slot Size" )
	void RemoveArbitrarySlotSize( int32 index );

	/** This returns the arbitrary slot size if one is set, otherwise the stack size */
	UFUNCTION( BlueprintPure, Category = "Slot Size" )
	int32 GetSlotSize( int32 index, TSubclassOf< UFGItemDescriptor > itemDesc = nullptr ) const;
	
	int32 GetSlotSizeForItem( int32 index, TSubclassOf< UFGItemDescriptor > itemDesc = nullptr, const FInventoryItem* Item = nullptr ) const;

	/**
	 * Set the allowed item type for this slot, can only be one item.
	 * @return Allowed item type if set; nullptr if any item is allowed or invalid index.
	 */
	UFUNCTION( BlueprintPure, Category = "Filter" )
	TSubclassOf< UFGItemDescriptor > GetAllowedItemOnIndex( int32 idx );

	/**
	 * Get the allowed item type for this slot.
	 * @param idx Slot index, function does nullptr if this is invalid.
	 * @param allowedItemClass Item type to allow, if nothing then all items are allowed.
	 */
	UFUNCTION( BlueprintCallable, Category = "Filter" )
	void SetAllowedItemOnIndex( int32 idx, TSubclassOf< UFGItemDescriptor > allowedItemClass );

		/** Returns true if we can split the stack that is on the passed idx */
	UFUNCTION( BlueprintPure, Category = "Split" )
	bool CanSplitStackAtIdx( int32 idx );

		/** Splits the stack at the current index and moves the passed amount of items to first valid slot */
	UFUNCTION( BlueprintCallable, Category = "Split" )
	void SplitStackAtIdx( int32 idx, int32 numItemsToMove );

		/** Can stuff in this inventory be rearranged, that is moved from one slot to the other?*/
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	FORCEINLINE bool GetCanBeRearranged() const { return mCanBeRearrange; }

		/** Setter for mCanBeRearranged*/
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void SetCanBeRearranged( bool canBeRearranged );

	/** Duplicates and overrides all relevant values from the other component */
	void CopyFromOtherComponent( UFGInventoryComponent* otherComponent );

	/** Notify component its owning buildable is dismantled (or is dismantling), don't allow movement in or out of this inventory */
	FORCEINLINE void SetLocked( const bool isLocked ) { mIsLocked = isLocked; }

	UFUNCTION( BlueprintPure, Category = "Inventory")
	FORCEINLINE bool IsLocked() const { return mIsLocked; }

	/** This should only be TRUE in special circumstance and should be set to false once those special circumstances are completed */
	FORCEINLINE void SetSuppressOnItemAddedDelegate( const bool suppress ) { mSuppressOnItemAddedDelegateCalls = suppress; }

	/** This should only be TRUE in special circumstance and should be set to false once those special circumstances are completed */
	FORCEINLINE void SetSuppressOnItemRemovedDelegate( const bool suppress ) { mSuppressOnItemRemovedDelegateCalls = suppress; }

	FORCEINLINE bool GetSuppressOnItemAddedDelegate() const { return mSuppressOnItemAddedDelegateCalls; }
	FORCEINLINE bool GetSuppressOnItemRemovedDelegate() const { return mSuppressOnItemRemovedDelegateCalls; }

	void CopyInTheseItemStacks( const TArray<FInventoryStack>& itemsStacks);

	/** Returns the player state from the outer player character */
	class AFGPlayerState* GetOwningPlayerState() const;

	// Returns true if either the session wide cheat NoCost is enabled or if the individual game mode NoBuildCost is enabled 
	bool GetNoBuildCost() const;

	/** Updates the relevancy owner for this item. This component will only replicate it's data when the relevancy owner allows it to */
	void SetReplicationRelevancyOwner( UObject* relevancyOwner );

	/** Marks inventory contents dirty for replication and schedules their re-sync */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void MarkInventoryContentsDirty();
protected:
	void OnRelevancyOwnerInvalidatedRelevantPropertiesCache();
	
	/** Used to call OnItemAdded/OnItemRemoved on clients */
	UFUNCTION()
	void OnRep_InventoryStacks( const TArray<FInventoryStack>& oldStacks );

	/** Used to broadcast slot updated events on clients */
	UFUNCTION()
	void OnRep_AllowedItemDescriptors( TArray< TSubclassOf < UFGItemDescriptor > > previousAllowedItems );

	/** Used to broadcast slot updated delegates when arbitrary slot sizes are replicated */
	UFUNCTION()
	void OnRep_ArbitrarySlotSizes( TArray<int32> previousArbitrarySlotSizes );

	/**
	 * Called when something gets added.
	 *
	 * @note Only called on the server.
	 *
	 * @param idx - The index the item got added to.
	 * @param num - The number of items that were added.
	 * @param sourceInventory - The inventory component the items originate from, if applicable.
	 */
	virtual void OnItemsAdded( const int32 idx, const int32 num, UFGInventoryComponent* sourceInventory = nullptr );

	/**
	 * Called when something gets removed
	 *
	 * @param idx - The index the item was removed from.
	 * @param num - The number of items removed.
	 * @param item - The item that was removed, if not all items where removed this is the same as the item at the index.
	 * @param targetInventory - The inventory component that the removed item is being moved to, if applicable.
	 */
	virtual void OnItemsRemoved( int32 idx, int32 num, const FInventoryItem& item, UFGInventoryComponent* targetInventory = nullptr );

	/**
	 * Get a non-const reference to a stack.
	 * @param idx A valid index. Asserts otherwise.
	 * @return The stack at idx.
	 */
	FInventoryStack& GetStackFromIndex( int32 idx );

	/**
	 * Same as the function above, but the returned reference is const
	 */
	const FInventoryStack& GetStackFromIndex( int32 idx ) const;
private:
	void UpdateRadioactivity( int32 idx, TSubclassOf<UFGItemDescriptor> itemClass );

public:
	/** Set this to filter out what items are allowed and not allowed in the inventory */
	FItemFilter mItemFilter;

	/** Set this to filter out items by EResourceForm */
	FFormFilter mFormFilter;

protected:
	/** When we make an inventory by adding the component to an actor we use this to specify its size */
	UPROPERTY( EditDefaultsOnly )
	int32 mDefaultInventorySize;

	/** When we resize the inventory we save how much bigger or smaller the inventory was made */
	UPROPERTY( SaveGame )
	int32 mAdjustedSizeDiff;

	/** For special situations where many stacks may be added in a single frame and we don't to trigger OnItemAdded delegates every time */
	bool mSuppressOnItemAddedDelegateCalls;

	/** For special situations where many stacks may be removed in a single frame and we don't to trigger OnItemRemoved delegates every time */
	bool mSuppressOnItemRemovedDelegateCalls;
	
	/** Locks the inventory. Indicating that no items are allowed and you should not be able to drag stuff from it either */
	bool mIsLocked;

	/** Tracks whether or not its necessary to replicate allowed item descriptors to clients*/
	bool mDoRepAllowedItemDescriptors;

	/** Tracks whether or not its necessary to replicate arbitrary slot sizes to clients */
	bool mDoRepArbitrarySlotSizes;

private:
	/** The owner of this component that dictates when it becomes relevant */
	UPROPERTY( Transient )
	TScriptInterface<IFGConditionalReplicationInterface> mReplicationRelevancyOwner;
	
	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;
	
	/** All items in the inventory */
	UPROPERTY( SaveGame, meta = ( FGReplicatedUsing = OnRep_InventoryStacks ) )
	TArray< FInventoryStack > mInventoryStacks;

	/** In some rare cases we don't want to use the StackSize to limit the slot, so this way we can have larger or smaller slots */
	UPROPERTY( SaveGame, meta = ( FGReplicatedUsing = OnRep_ArbitrarySlotSizes ) )
	TArray< int32 > mArbitrarySlotSizes;

	/** This are the allowed inventory items, this we we can "filter" in BluePrint as well. */
	UPROPERTY( SaveGame, meta = ( FGReplicatedUsing = OnRep_AllowedItemDescriptors ) )
	TArray< TSubclassOf < UFGItemDescriptor > > mAllowedItemDescriptors;

	/** Can stuff in this inventory be rearranged, that is moved from one slot to the other? */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	bool mCanBeRearrange;

	FName mCachedStackNameProperty = NAME_None;

	/** Fast serializer for mInventoryStacks that will attempt to fast & efficiently serialize item stacks */
	static bool NetDeltaSerializeInventoryStacksFast( FProperty* inventoryStacksProp, void* inventoryStacksPtr, FNetDeltaSerializeInfo& deltaParams );
};
