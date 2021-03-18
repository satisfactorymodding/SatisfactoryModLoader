// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "ItemDrop.generated.h"


/**
 * Specify items dropped by picking up foliage.
 */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FItemDrop
{
	GENERATED_BODY()

	FItemDrop() :
		ItemClass( nullptr )
	{
		NumItems.Min = 1;
		NumItems.Max = 2;
	}

	/** Item class */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DropPackage" )
	TSubclassOf< class UFGItemDescriptor > ItemClass;

	/** Range of items you can get */
	UPROPERTY( EditAnywhere, Category = "DropPackage" )
	FInt32Interval NumItems;

	/** Get a random amount of items in range */
	int32 GetRandomItemAmount() const;
};

/**
 * Specify items dropped by picking up foliage, with a random chance.
 */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FItemDropWithChance
{
	GENERATED_BODY()

	FItemDropWithChance() :
		DropChance( 1.0f )
	{
	}

	/** returns true if the item drop should drop */
	bool ShouldDrop() const;

	/** A chance between 0->1, 1 means 100% drop chance */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (UIMin = 0.0, UIMax = 1.0), Category = "DropPackage" )
	float DropChance;

	/** The drop to be given if we gain the item */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = (ShowOnlyInnerProperties) )
	FItemDrop Drop;
};
