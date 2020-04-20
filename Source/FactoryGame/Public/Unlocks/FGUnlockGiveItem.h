// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Unlocks/FGUnlock.h"
#include "../FGSchematic.h"
#include "FGUnlockGiveItem.generated.h"

/**
 * Unlock class for specifying items to give the player. Doesn't actually do anything on unlock.
 * More used as a container that other systems can use to find what items a schematic should give.
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockGiveItem : public UFGUnlock
{
	GENERATED_BODY()
	
public:
	/** Returns the items that this schematic gives when unlocked */
	UFUNCTION( BlueprintPure, Category = Unlocks )
	FORCEINLINE TArray< FItemAmount > GetItemsToGive() const { return mItemsToGive; }

	void AddItemsToGive( TArray< FItemAmount > items );

public: // MODDING EDIT: protected -> public
	/** The items you get from this unlock */
	UPROPERTY( EditDefaultsOnly )
	TArray< FItemAmount > mItemsToGive;


public:
	FORCEINLINE ~UFGUnlockGiveItem() = default;
};
