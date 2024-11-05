// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGScannableDetails.h"
#include "FGUnlock.h"
#include "FGUnlockScannableObject.generated.h"


/**
 * 
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockScannableObject : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

protected:
	/** The schematics you get from this unlock */
	UPROPERTY( EditDefaultsOnly, Category = "Scannable Object" )
	TArray< FScannableObjectData > mScannableObjects;

	UFUNCTION( BlueprintPure, Category=Unlocks )
	FORCEINLINE TArray< FScannableObjectData > GetScannableObjectsToUnlock() const { return mScannableObjects; }
	
};
