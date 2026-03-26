// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGUnlock.h"
#include "FGUnlockVisualizationMode.generated.h"

class UFGVisualizationModeDescriptor;
/**
 * Unlocks the specified visualization modes for the player
 */
UCLASS( Abstract, Blueprintable, DefaultToInstanced, EditInlineNew )
class FACTORYGAME_API UFGUnlockVisualizationMode : public UFGUnlock
{
	GENERATED_BODY()
public:
	UFGUnlockVisualizationMode();

	// Begin FGUnlock interface
	virtual void Apply( AFGUnlockSubsystem* unlockSubsystem ) override;
	// End FGUnlock interface

	/** Returns al ist of visualization modes unlocked by this unlock */
	UFUNCTION( BlueprintPure, Category="Visualization Mode" )
	FORCEINLINE TArray<TSubclassOf<UFGVisualizationModeDescriptor>> GetVisualizationModesToUnlock() const { return mVisualizationModes; }
protected:
	/** The visualization modes retrieved from this unlock */
	UPROPERTY( EditDefaultsOnly, Category = "Visualization Mode" )
	TArray<TSubclassOf<UFGVisualizationModeDescriptor>> mVisualizationModes;
};
