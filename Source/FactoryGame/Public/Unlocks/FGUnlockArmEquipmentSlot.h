// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockArmEquipmentSlot.generated.h"

/**
 * Unlock a number of arm equipment slots
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockArmEquipmentSlot : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Unlock( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

#if WITH_EDITORONLY_DATA
	void Init( int32 numArmEquipmentSlotsToUnlock ) { mNumArmEquipmentSlotsToUnlock = numArmEquipmentSlotsToUnlock; }
#endif

protected:
	/** Number of arm equipment slots this unlock adds to the players inventory */
	UPROPERTY( EditDefaultsOnly )
	int32 mNumArmEquipmentSlotsToUnlock;
};
