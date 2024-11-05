// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockSAMIntensity.generated.h"

/**
 * Unlocks how intense the effects like VO on the SAM nodes should be
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockSAMIntensity : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface
	
	UFUNCTION( BlueprintPure, Category = Unlocks )
	FORCEINLINE int32 GetSAMIntensity() const { return mSAMIntensity; }

protected:
	/** How intense the effects like VO on the SAM nodes should be */
	UPROPERTY( EditDefaultsOnly )
	int32 mSAMIntensity;
};
