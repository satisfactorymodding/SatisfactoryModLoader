// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGInventoryComponent.h"
#include "FGInventoryLibrary.generated.h"


/**
 * Function library to provide the glue between c++ and the inventory in blueprint so we can handle inventory items with a state easy in blueprint.
 */
UCLASS()
class FACTORYGAME_API UFGInventoryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Dynamically create an inventory component of a given type with a given size. */
	template< class T >
	static T* CreateInventoryComponent( class AActor* owner, FName name )
	{
		fgcheck( owner );
		fgcheck( name != NAME_None );

		return CastChecked< T >( CreateInventoryComponentOfClass( owner, T::StaticClass(), name ) );
	}

	/** Dynamically create a default inventory component with a given size. */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static class UFGInventoryComponent* CreateInventoryComponent( class AActor* owner, FName name );

	/** Dynamically create an inventory component of a given class with a given size. */
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static class UFGInventoryComponent* CreateInventoryComponentOfClass( class AActor* owner,
																		 UPARAM( DisplayName = "Class" ) TSubclassOf< class UFGInventoryComponent > inClass,
																		 FName name );

	/** Manual break for inventory stack. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static void BreakInventoryStack( UPARAM( ref ) const FInventoryStack& stack,
									 UPARAM( DisplayName = "Num Items" ) int32& out_numItems,
									 UPARAM( DisplayName = "Item" ) FInventoryItem& out_item );

	/** Manual break for inventory item. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static void BreakInventoryItem( UPARAM( ref ) const FInventoryItem& item,
									UPARAM( DisplayName = "Class" ) TSubclassOf< class UFGItemDescriptor >& out_itemClass,
									UPARAM( DisplayName = "State" ) class AActor*& out_itemState );

	/** Manual make for inventory item. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static FInventoryItem MakeInventoryItem( UPARAM( DisplayName = "Class" ) TSubclassOf< class UFGItemDescriptor > itemClass );

	/** Manual make for inventory stack. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static FInventoryStack MakeInventoryStack( int32 numItems, FInventoryItem item );

	/** @return true if the inventory item is a valid item; otherwise false. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static FORCEINLINE bool IsValidItem( UPARAM( ref ) const FInventoryItem& item ) { return item.IsValid(); }

	/** @return true if this inventory item has a state; otherwise false. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static FORCEINLINE bool HasState( UPARAM( ref ) const FInventoryItem& item ) { return item.HasState(); }

	/** Returns the amount of inventory items converted to the appropriate units for displaying in the UI
	* @param amount - quantity of unmodified inventory items. eg. 1000 Liquid inventory will be divided by 1000.f to return 1 m^3
	*/
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static float GetAmountConvertedByForm( int32 amount, EResourceForm form );

	/** Returns the UI Suffix for production quantities based on a Resource Form Type */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static FText GetProductionSuffixFromFormType( EResourceForm form );

	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static float GetConversionScalarByForm( EResourceForm form );

	/** Returns the amount of inventory items converted to the appropriate units for displaying in the UI. Also returns the split itemAmount for ease of access in widgets.
	* @param itemAmount - FItemAmount to use as the base for conversion. The item form will be pulled from the itemAmount.ItemClass to determine the conversion.
	* @param itemClass - (Out) The item class of the FItemAmount
	* @param amountConverted - The amount converted to the correct representation in the UI. eg. 1000 Liquid inventory will be divided by 1000.f to return 1.f ( m^3 )
	*/
	UFUNCTION( BlueprintPure, Category = "Item" )
	static void GetAmountConvertedFromItemAmount( UPARAM( ref ) const FItemAmount& itemAmount, TSubclassOf< class UFGItemDescriptor >& itemClass, float& amountConverted );

	/** Returns the amount of stack items converted to the appropriate units for displaying in the UI, excluding suffix and form data. This also returns the split data for ease of access in Widgets.
	* @param inventoryStack - (In) FInventoryStack to use as the base for conversion. The item form will be pulled from the stacks ItemClass to determine the conversion.
	* @param buildableClass - (In) (Optional) if passed a valid buildable and the resource form is not SOLID, the converted maximimum stack will also be scaled by the buildables stack size
	* @param itemClass - (Out) The item class of the inventory stack.
	* @param numItemsConverted - (Out) The numItems converted to the correct representation for the UI. eg. 1000 Liquid inventory will be divided by 1000.f to return 1.f ( m^3 )
	* @param maxItemsConverted - (Out) The max stack size for this InventoryStack. If a buildableClass was passed and the resource form is not SOLID, this value will also be scaled to by the buildables stack size scalar.
	*/
	UFUNCTION( BlueprintPure, Category = "Item" )
	static void GetUIDataPartialForInventoryStack( UPARAM( ref ) const FInventoryStack& inventoryStack, const TSubclassOf< class AFGBuildableFactory > buildableFactory, TSubclassOf< class UFGItemDescriptor>& itemClass, float& numItemsConverted, float& maxItemsConverted );

	/** Returns the amount of stack items converted to the appropriate units for displaying in the UI including suffix and form data. This also returns the split data for ease of access in Widgets.
	* @param inventoryStack - (In) FInventoryStack to use as the base for conversion. The item form will be pulled from the stacks ItemClass to determine the conversion.
	* @param buildableClass - (In) (Optional) if passed a valid buildable and the resource form is not SOLID, the converted maximimum stack will also be scaled by the buildables stack size
	* @param itemClass - (Out) The item class of the inventory stack.
	* @param numItemsConverted - (Out) The numItems converted to the correct representation for the UI. eg. 1000 Liquid inventory will be divided by 1000.f to return 1.f ( m^3 )
	* @param maxItemsConverted - (Out) The max stack size for this InventoryStack. If a buildableClass was passed and the resource form is not SOLID, this value will also be scaled to by the buildables stack size scalar.
	* @param suffix - (Out) The UI suffix for this part form ( Tex. Solid = "Parts", Liquid = "m^3" )
	* @param form - (Out) The resource form of this ItemStack
	*/
	UFUNCTION( BlueprintPure, Category = "Item" )
	static void GetUIDataFullForInventoryStack( UPARAM( ref ) const FInventoryStack& inventoryStack, const TSubclassOf< class AFGBuildableFactory > buildableFactory, TSubclassOf< class UFGItemDescriptor>& itemClass, float& numItemsConverted, float& maxItemsConverted, FText& suffix, EResourceForm& form );
	
	/** @return a none item. */
	static FORCEINLINE FInventoryItem GetNullInventoryItem() { return FInventoryItem::NullInventoryItem; }

	/** @return true if the stack has any items; false if the stack is empty. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	static FORCEINLINE bool HasItems( UPARAM( ref ) const FInventoryStack& stack ) { return stack.HasItems(); }

	/**
	 * This is a UI helper function for drag n drop that automagically moves or swaps items.
	 * It moves or swaps an item from a one location to another location. Verifying that the move or swap is allowed.
	 * @note Server only
	 *
	 * @return true on success; false if something goes wrong during the move.
	 */
	//@todoinventory RENAME Stack
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static bool MoveInventoryItem( class UFGInventoryComponent* sourceComponent, int32 sourceIdx, class UFGInventoryComponent* destinationComponent, int32 destinationIdx );

	/**
	* Tries to grab all items in the source and add them to the dest. I can't decide what optimal grabbing is, so this is just the easiest implementation.
	* @note Server only
	*
	* @return true on success; false if something goes wrong during the move.
	*/
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static bool GrabAllItemsFromInventory( UFGInventoryComponent* sourceComponent, UFGInventoryComponent* destinationComponent, TSubclassOf< UFGItemDescriptor > onlyGrabOfDesc = nullptr );

	/**
	 * Helper to consolidate the given items into as few items as possible.
	 * E.g. consolidate this:    50 iron, 50 iron, 30 copper, 35 iron
	 *      into this:           135 iron, 30 copper
	 *
	 * @note This do not apply any stacking limits.
	 */
	//@todoinventory RENAME Stacks
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static void ConsolidateInventoryItems( UPARAM( ref ) TArray< FInventoryStack >& items );

	/**
	* Calculates how many inventory slots the passed number of items requires.
	*
	* ASSUMES CONSOLIDATED ARRAY
	*/
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static int32 GetMinNumSlotsForItems( UPARAM( ref ) TArray< FInventoryStack >& items );

	/**
	 * Helper to merge an inventory item into an array of other inventory items.
	 *
	 * @param items - Merge item into this array.
	 * @param item - This is the item to merge into the items array.
	 *
	 * @note This do not apply any stacking limits.
	 */
	//@todoinventory RENAME Stack
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static void MergeInventoryItem( UPARAM( ref ) TArray< FInventoryStack >& items, const FInventoryStack& item );

	/**
	* Helper to consolidate the given items into as few items as possible.
	* E.g. consolidate this:    50 iron, 50 iron, 30 copper, 35 iron
	*      into this:           135 iron, 30 copper
	*
	* @note This do not apply any stacking limits.
	*/
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static void ConsolidateItemsAmount( UPARAM( ref ) TArray< FItemAmount >& items );


	/** 
	* Removes all stacks whom's resource form does not match the passed form
	* @param items - Array of items by ref to remove from
	* @param validForm - Keep items of this form. Default == RF_SOLID
	*/
	UFUNCTION( BlueprintCallable, Category = "Inventory" )
	static void RemoveAllItemsNotOfResourceForm( UPARAM( ref ) TArray< FInventoryStack >& items, EResourceForm validForm = EResourceForm::RF_SOLID );

};