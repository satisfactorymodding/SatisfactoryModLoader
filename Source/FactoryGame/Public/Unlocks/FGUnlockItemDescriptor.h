// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGRecipe.h"
#include "FGUnlockItemDescriptor.generated.h"

/**
 * Unlocks the item descriptor and makes it available in various UIs such as Programmable and Smart Splitters
 */
UCLASS( Abstract, Blueprintable, EditInlineNew, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockItemDescriptor : public UFGUnlock
{
	GENERATED_BODY()
public:
	// Begin FGUnlock interface
	virtual void Apply( AFGUnlockSubsystem* unlockSubsystem ) override;
	// End FGUnlock interface

	/** The item descriptors to be unlocked */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Unlock" )
	TArray<TSubclassOf<UFGItemDescriptor>> mItemDescriptors;
};
