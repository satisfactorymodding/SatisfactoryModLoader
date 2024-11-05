// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tests/FGGameplayTest.h"
#include "FGGameplayTest_OnlineStats.generated.h"

/**
 * Test used for querying online stats to make sure they exist in the backend
 */
UCLASS()
class FACTORYGAME_API UFGGameplayTest_OnlineStats : public UFGGameplayTest
{
	GENERATED_BODY()

protected:
	virtual void OnTestStarted() override;
};
