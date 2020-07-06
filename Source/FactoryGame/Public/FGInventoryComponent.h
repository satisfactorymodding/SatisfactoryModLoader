#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "SharedInventoryStatePtr.h"
#include "FGSaveInterface.h"
#include "Resources/FGItemDescriptor.h"
#include "ItemAmount.h"
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
	FORCEINLINE FInventoryItem(const FInventoryItem& other) = default; // MODDING EDIT

	/** Function called when serializing this struct to a FArchive. */
	bool Serialize( FArchive& ar );
	friend FArchive& operator<<( FArchive& ar, FInventoryItem& item );

	/** @return true if this is a valid item; otherwise false. */
	FORCEINLINE bool IsValid() const { return ::IsValid( ItemClass ); }

	/** @return true if this item has a state; otherwise false. */
	FORCEINLINE bool HasState() const { return ItemState.IsValid(); }

public:
	/** The type of item */
	UPROPERTY( EditAnywhere )
	TSubclassOf< class UFGItemDescriptor > ItemClass;

	/** Optionally store an actor, e.g. an equipment, so we can remember it's state. */
	UPROPERTY()
	FSharedInventoryStatePtr ItemState;

public:
	FORCEINLINE ~FInventoryItem() = default;
};
FORCEINLINE FString VarToFString( FInventoryItem var ){ return FString::Printf( TEXT( "%s: {%s}" ), *VarToFString(var.ItemClass), *VarToFString(var.ItemState) ); }

/** Enable custom serialization of FInventoryItem */
template<>
struct FACTORYGAME_API TStructOpsTypeTraits< FInventoryItem > : public TStructOpsTypeTraitsBase2< FInventoryItem >
{
	enum
	{
		WithSerializer = true,
		WithCopy = true
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits< FInventoryItem >() = default;
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
	FORCEINLINE FInventoryStack(const FInventoryStack& other) = default; // MODDING EDIT
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

public:
	FORCEINLINE ~FInventoryStack() = default;
};
FORCEINLINE bool IsValidForLoad( const FInventoryStack& element ){ return element.Item.ItemClass != nullptr; }

template<>
struct FACTORYGAME_API TStructOpsTypeTraits<FInventoryStack> : public TStructOpsTypeTraitsBase2<FInventoryStack>
{
	enum
	{
		WithCopy = true
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits<FInventoryStack>() = default;
};

/** Others can hook up to this to allow/disallow items */
DECLARE_DELEGATE_RetVal_TwoParams( bool, FItemFilter, TSubclassOf< UObject >, int32 );

DECLARE_DELEGATE_RetVal_TwoParams( bool, FFormFilter, TSubclassOf< UFGItemDescriptor >, int32 );

DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams( FVector, FGetItemDropLocation, const UFGInventoryComponent*, component, FInventoryStack, stack );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnItemAdded, TSubclassOf< UFGItemDescriptor >, itemClass, int32, numAdded );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnItemRemoved, TSubclassOf< UFGItemDescriptor >, itemClass, int32, numRemoved );

/**
 * @brief Handles the different parts of the inventory for a actor
 * Composed of several UFGInventoryComponents that does all the dirty work, this
 * object just collects them together and gives access to them
 * The outer object of this object needs to implement GetWorld
 */
UCLASS( BlueprintType, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGInventoryComponent : public UActorComponent, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	virtual void PreNetReceive() override;

	UFGInventoryComponent();

	//~ Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
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

	// Begin UActorComponent interface
	virtual void OnRegister() override;
	// End UActorComponent interface

	/**
	* The default size of this inventory.
	*
	* @param defaultSize How many itemslots does this component have as default
	*/
	void SetDefaultSize( int32 defaultSize = 1 );

	/**
	 * Changes the size of the inventory to something else than 1
	 *
	 * @param newSize How many itemslots does this component have
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
	UFUNCTION( BlueprintPure, CustomThunk, Category = "Inventory" )
	bool IsItemAllowed( TSubclassOf< UFGItemDescriptor > item, const int32 idx = -1 ) const; //INDEX_NONE

	//[FreiholtzK:Mon/16-12-2019] Temporary debug code that should be removed after we have managed to find what passes in a null item descriptor here
	DECLARE_FUNCTION( execIsItemAllowed )
	{
		P_GET_OBJECT( UClass, Z_Param_item );
		P_GET_PROPERTY( UIntProperty, Z_Param_idx );
		P_FINISH;
		static bool hasCaughtNullpeter = false;
		if( Z_Param_item == nullptr && !hasCaughtNullpeter )
		{
			hasCaughtNullpeter = true;
			const FString Trace = Stack.GetStackTrace();
			UE_LOG( LogBlueprintUserMessages, Log, TEXT( "\nUFGInventoryComponent::IsItemAllowed is called with nullpeter from BP:\n%s" ), *Trace );
		}
		P_NATIVE_BEGIN;
		*( bool* )Z_Param__Result = P_THIS->IsItemAllowed( Z_Param_item, Z_Param_idx );
		P_NATIVE_END;
	}

	/**
	 * @return true if the index is a valid index.
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	bool IsValidIndex( int32 idx ) const;

	/**
	 * @return first empty index, -1 if none is found
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 FindEmptyIndex() const;

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
	 *
	 * @param allowPartialAdd - If true we add what we can and ignore the rest; otherwise it assumes everything fits and warns otherwise.
	 *                          @note It is the callers responsibility to take care of the items that where not added.
	 *
	 * @return Number of items added, may be less than the input if partial adds are allowed.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	virtual int32 AddStack( const FInventoryStack& stack, bool allowPartialAdd = false );

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
	 * Tries to add an item to our inventory at a give index, stack it if possible.
	 * @note Server only
	 *
	 * @param idx - A valid index in mInventoryStacks.
	 * @param item - The item to add.
	 * @param allowPartialAdd - If true we add what we can and ignore the rest; otherwise it assumes everything fits and warns otherwise.
	 *                          @note It is the callers responsibility to take care of the items that where not added.
	 *
	 * @return Number of items added, may be less than the input if partial adds are allowed.
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	virtual int32 AddStackToIndex( int32 idx, const FInventoryStack& stack, bool allowPartial = false );

	/**
	 * Get the item of a slot.
	 * @note true if valid index, it is the callers responsibility to check if the slot contains an item or not.
	 *
	 * @param idx - A valid index in mInventoryStacks.
	 * @param out_item - The item on the location. If not a valid index this is undefined.
	 *
	 * @return true if valid index; false otherwise.
	 */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Inventory" )
	bool GetStackFromIndex( int32 idx, FInventoryStack& out_stack ) const;

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
	 */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void RemoveFromIndex( int32 idx, int32 num );

	/** Clears the index, ALL items will be forever gone! */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	void RemoveAllFromIndex( int32 idx );

	/** Check if the entire inventory is empty. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	bool IsEmpty() const;

	/** Check if the given index is empty. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	bool IsIndexEmpty( int32 idx ) const;

	/** Opposite of IsIndexEmpty */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	bool IsSomethingOnIndex( int32 idx ) const;

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
	 * @param itemClass - The items class.
	 *
	 * @return Total amount of the item we have in the inventory.
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 GetNumItems( TSubclassOf< UFGItemDescriptor > itemClass ) const;

	/**
	 * Check if the inventory has enough space to store the given items.
	 * @param stacks - Stacks to check enough space for.
	 * @return - true if the items can be stored in the inventory; false if the inventory has insufficent space or the type for any of the items cannot be stored in this inventory.
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
	void SetStateOnIndex( int32 index, const FSharedInventoryStatePtr& itemState );

	/** The total size of the inventory, when accessing inventory linearly using indices. */
	MODDING_SHIPPING_FORCEINLINE
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 GetSizeLinear(){ return mInventoryStacks.Num(); }

	/** Returns index of the stack that has percentually the most items */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 GetFullestStackIndex();

	/** Get all stacks that's in the players inventory */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	void GetInventoryStacks( TArray< FInventoryStack >& out_stacks ) const;

	/** Returns the indexes of relevant stacks depending on the given items classes, 
	indexes are sorted first by class and secondly in ascending stack size */ 
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	TArray<int32> GetRelevantStackIndexes( TArray< TSubclassOf< class UFGItemDescriptor > > relevantClasses, int32 stackLimit );

	/** Called when this inventory has been resized */
	UPROPERTY( BlueprintAssignable, Category = "Inventory", DisplayName = "OnInventoryResized" )
	FInventoryResized ResizeInventoryDelegate;

	/** Called when this inventory has something added to it, @note: Client doesn't garantuee order of Added/Remove delegate */
	UPROPERTY( BlueprintAssignable, Category = "Inventory", DisplayName = "OnItemAdded" )
	FOnItemAdded OnItemAddedDelegate;

	/** Called when something has been removed from the inventory, @note: Client doesn't garantuee order of Added/Remove delegate */
	UPROPERTY( BlueprintAssignable, Category = "Inventory", DisplayName = "OnItemRemoved" )
	FOnItemRemoved OnItemRemovedDelegate;

	/** Adds or replaces a arbitrary size for a slot. */
	UFUNCTION( BlueprintCallable, Category = "Slot Size" )
	void AddArbitrarySlotSize( int32 index, int32 arbitrarySlotSize );

	/** Removes an Arbitrary size for a slot. */
	UFUNCTION( BlueprintCallable, Category = "Slot Size" )
	void RemoveArbitrarySlotSize( int32 index );

	/** This returns the arbitrary slot size if one is set, otherwise the stack size */
	UFUNCTION( BlueprintPure, Category = "Slot Size" )
	int32 GetSlotSize( int32 index, TSubclassOf< UFGItemDescriptor > itemDesc = nullptr ) const;

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
	FORCEINLINE void SetLocked( bool isLocked ) { mIsLocked = isLocked; }

	UFUNCTION( BlueprintPure, Category = "Inventory ")
	FORCEINLINE bool IsLocked() const { return mIsLocked; }

protected:
	/** Used to call OnItemAdded/OnItemRemoved on clients */
	UFUNCTION()
	void OnRep_InventoryStacks();

	/**
	 * Called when something gets added.
	 *
	 * @note Only called on the server.
	 *
	 * @param item - The index the item got added to.
	 * @param item - The number of items that were added.
	 */
	virtual void OnItemsAdded( int32 idx, int32 num );

	/**
	 * Called when something gets removed
	 *
	 * @param idx - The index the item was removed from.
	 * @param num - The number of items removed.
	 * @param item - The item that was removed, if not all items where removed this is the same as the item at the index.
	 */
	virtual void OnItemsRemoved( int32 idx, int32 num, FInventoryItem item );

	/**
	 * Get a non-const reference to a stack.
	 * @param idx A valid index. Asserts otherwise.
	 * @return The stack at idx.
	 */
	FInventoryStack& GetStackFromIndex( int32 idx );
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

	/** Locks the inventory. Indicating that no items are allowed and you should not be able to drag stuff from it either */
	bool mIsLocked;

private:
	/** All items in the inventory */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_InventoryStacks )
	TArray< FInventoryStack > mInventoryStacks;

	/** Stored last frames data in PreNetReceive, so that we can derive what has happened since last inventory state we received */
	TArray< FInventoryStack > mClientLastFrameStacks;

	/** In some rare cases we don't want to use the StackSize to limit the slot, so this way we can have larger or smaller slots */
	UPROPERTY( SaveGame, Replicated )
	TArray< int32 > mArbitrarySlotSizes;

	/** This are the allowed inventory items, this we we can "filter" in BluePrint as well. */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf < UFGItemDescriptor > > mAllowedItemDescriptors;

	/** Can stuff in this inventory be rearranged, that is moved from one slot to the other? */
	UPROPERTY( SaveGame, Replicated )
	bool mCanBeRearrange;

public:
	FORCEINLINE ~UFGInventoryComponent() = default;
};
