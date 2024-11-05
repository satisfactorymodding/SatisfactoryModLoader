// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGItemDescriptor.h"
#include "ItemAmount.generated.h"

/**
 * Struct used to specify an amount of items.
 * E.g. a cost, a recipe product or ingredient.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FItemAmount
{
	GENERATED_BODY()

	FItemAmount() :
		ItemClass( nullptr ),
		Amount( 0 )
	{
	}

	FItemAmount( TSubclassOf< class UFGItemDescriptor > inClass, int32 inAmount ) :
		ItemClass( inClass ),
		Amount( inAmount )
	{
	}

	/** The item. */
	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere, Category = "Item" )
	TSubclassOf< class UFGItemDescriptor > ItemClass;

	/** The amount of this item. */
	UPROPERTY( SaveGame, BlueprintReadWrite, EditAnywhere, Category = "Item", meta = ( ClampMin = 0 ) )
	int32 Amount;

	/** Returns the amount of the given item in the given item amounts array. Returns 0 if no entry is found */
	static int32 GetAmountFromItemAmounts( const TArray<FItemAmount>& itemAmounts, const TSubclassOf< UFGItemDescriptor >& itemClass )
	{
		if( const FItemAmount* foundItemAmount = itemAmounts.FindByPredicate( [itemClass](const FItemAmount& itemAmount)
		{
			return itemAmount.ItemClass == itemClass;
		} ))
		{
			return foundItemAmount->Amount;
		}
		return 0;
	}

};

/**
 * Maps item descriptors to amounts. 
 */
USTRUCT()
struct FACTORYGAME_API FMappedItemAmount
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	TMap<TSubclassOf< class UFGItemDescriptor >, int32> ItemAmounts;
};
