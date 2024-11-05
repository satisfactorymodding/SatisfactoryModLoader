// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Unlocks/FGUnlock.h"
#include "FGUnlockTape.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGUnlockTape : public UFGUnlock
{
	GENERATED_BODY()
public:
	// Begin FGUnlock interface
	virtual void Unlock( class AFGUnlockSubsystem* unlockSubssytem ) override;
	virtual void Apply(AFGUnlockSubsystem* unlockSubssytem) override;
	// End FGUnlock interface
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tape")
	TArray< TSubclassOf< class UFGTapeData > > mTapeUnlocks;
};
