// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Unlocks/FGUnlock.h"
#include "FGUnlockInfoOnly.generated.h"

/**
 * Simple class to be used to add unlock data into the UI without unlocking anything
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockInfoOnly : public UFGUnlock
{
	GENERATED_BODY()

protected:
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FText mUnlockName;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FText mUnlockDescription;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UTexture2D* mUnlockIconBig;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UTexture2D* mUnlockIconSmall;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UTexture2D* mUnlockIconCategory;

};
