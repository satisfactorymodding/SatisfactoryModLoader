// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h" // MODDING EDIT: no PCH
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
};
FORCEINLINE bool IsValidForLoad( const FItemAmount& element ){ return element.ItemClass != nullptr; }
FORCEINLINE FString VarToFString( const FItemAmount& var ){ return FString::Printf( TEXT( "Num: %i [%s]" ), var.Amount, *VarToFString(var.ItemClass) ); }