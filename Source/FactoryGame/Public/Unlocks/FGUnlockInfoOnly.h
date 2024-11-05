// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockInfoOnly.generated.h"

class UTexture2D;

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

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, meta = ( Multiline = true ) )
	FText mUnlockDescription;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UTexture2D* mUnlockIconBig;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UTexture2D* mUnlockIconSmall;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	UTexture2D* mUnlockIconCategory;

};
