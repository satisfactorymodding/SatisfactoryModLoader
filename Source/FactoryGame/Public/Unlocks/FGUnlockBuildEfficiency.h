// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockBuildEfficiency.generated.h"

/**
 * Unlock the ability to see build efficiency in buildings
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockBuildEfficiency : public UFGUnlock
{
	GENERATED_BODY()

public:
	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface


public:
	FORCEINLINE ~UFGUnlockBuildEfficiency() = default;
};
