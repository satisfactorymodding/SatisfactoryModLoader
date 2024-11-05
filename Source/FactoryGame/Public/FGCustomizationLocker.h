// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGPlayerState.h"
#include "Buildables/FGBuildable.h"
#include "FGCustomizationLocker.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCustomizationLocker : public AFGBuildable
{
	GENERATED_BODY()
public:
	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override { return false; }
	// End IFGSaveInterface

	virtual void StartIsLookedAt_Implementation( AFGCharacterPlayer* byCharacter, const FUseState& state ) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnCustomizationDataChanged(FPlayerCustomizationData NewData);
};
