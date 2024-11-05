// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGTutorialIntroManager.h"
#include "FGCurrentOnboardingStepDependency.generated.h"

/**
* Dependency that's met if we have reached or surpassed the given onboarding step.
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGCurrentOnboardingStepDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
    virtual bool AreDependenciesMet( UObject* worldContext ) const;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
    class UFGOnboardingStep* GetOnboardingStep() const{ return mOnboardingStep; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif
	
protected:
	/** The onboarding step that should have been reached or surpassed for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	UFGOnboardingStep* mOnboardingStep;
	
};
