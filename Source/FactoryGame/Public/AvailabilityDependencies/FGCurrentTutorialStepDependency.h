// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGTutorialIntroManager.h"
#include "FGCurrentTutorialStepDependency.generated.h"

/**
* Dependency that's met if we have reached the given intro tutorial step
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGCurrentTutorialStepDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
    virtual bool AreDependenciesMet( UObject* worldContext ) const;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
    EIntroTutorialSteps GetIntroTutorialStep() const{ return mIntroTutorialStep; }
	
protected:
	/** The intro tutorial step that should have been reached for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	EIntroTutorialSteps mIntroTutorialStep;
	
};
