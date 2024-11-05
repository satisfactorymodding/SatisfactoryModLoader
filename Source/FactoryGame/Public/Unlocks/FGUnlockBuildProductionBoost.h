// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockBuildProductionBoost.generated.h"

/**
 * Unlock the ability to insert production boosting shards into buildings
 */
UCLASS( Blueprintable, EditInlineNew, Abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockBuildProductionBoost : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface
};
