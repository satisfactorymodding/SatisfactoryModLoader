// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCharacterPlayer.h"
#include "FGTutorialIntroManager.h"
#include "Engine/DataAsset.h"
#include "FGOnboardingStep.generated.h"

/**
 * 
 */
UCLASS( BlueprintType )
class FACTORYGAME_API UFGOnboardingStep : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	static TArray<UFGOnboardingStep*> GetAllOnboardingStepAssets();

	bool operator<(const UFGOnboardingStep& otherOnboardingPhase) const;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial" )
	FText Title;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial" )
	TArray< FText > Objectives;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial" )
	TArray< FText > Hints;

	/** Indicates which index does this step have in the list of all onboarding steps. Set by AFGTutorialIntroManager on init.
	 * Onboarding steps with mExcludeFromOnboarding set to true is not considered for this and have a value of -1 */
	UPROPERTY( Transient, BlueprintReadOnly, Category = "Tutorial" )
	float mIndex = INDEX_NONE;

	/** Is this onboarding step relevant for onboarding? If true it's not part of the onboarding process and it's skipped
	 *  This is here instead of removing the step for fast iteration when testing order and content.
	 *  And if we in the future need to migrate from it we want to keep it as well.
	 */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Include" )
	bool mExcludeFromOnboarding;

	/** Lower priority means a step comes earlier */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Priority" )
	float mPriority;

	/** The input gates for this onboarding step, NOTE: True if input is disabled. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	FDisabledInputGate mDisabledInputGate;

	/** This is used so we can migrate from enum to asset based system. Locked so we don't accidentally change it.
	 * Not blueprint readable since we should use the asset itself as the ID */
	UPROPERTY( VisibleDefaultsOnly, Category = "Legacy" )
	EIntroTutorialSteps LegacyID = EIntroTutorialSteps::ITS_DEPRECATED;
};
