// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockInventorySlot.generated.h"

/**
 * Unlock a number of inventory slots
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockInventorySlot : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Unlock( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

#if WITH_EDITORONLY_DATA
	void Init( int32 numInventorySlotsToUnlock ) { mNumInventorySlotsToUnlock = numInventorySlotsToUnlock; }
#endif

protected:
	/** Number of inventory slots this unlock adds to the players inventory */
	UPROPERTY( EditDefaultsOnly )
	int32 mNumInventorySlotsToUnlock;
};
