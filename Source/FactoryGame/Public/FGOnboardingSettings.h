// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "FGOnboardingSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Onboarding / Tutorial" ) )
class FACTORYGAME_API UFGOnboardingSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFGOnboardingSettings(); // // <FL> [WuttkeP] UFGOnboardingSettings uses gameplay tags, so initialize them before loading the config.

	static const UFGOnboardingSettings* Get() { return GetDefault<UFGOnboardingSettings>(); };

	UPROPERTY( EditAnywhere, config, Category = "Onboarding",
		meta = ( ToolTip = "Maps a gameplay tag to an onboarding step, ensuring a type-safe and bindable reference for native code handling of onboarding steps" ) )
	TMap<FGameplayTag, TSoftObjectPtr<class UFGOnboardingStep>> mOnboardingStepMapping;

	
};
