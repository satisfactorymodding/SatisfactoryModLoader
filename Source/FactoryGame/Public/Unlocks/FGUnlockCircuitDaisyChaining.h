// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Unlocks/FGUnlock.h"
#include "FGUnlockCircuitDaisyChaining.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGUnlockCircuitDaisyChaining : public UFGUnlock
{
	GENERATED_BODY()
public:
	// Begin FGUnlock interface
	virtual void Apply(AFGUnlockSubsystem* unlockSubssytem) override;
	// End FGUnlock interface
};
