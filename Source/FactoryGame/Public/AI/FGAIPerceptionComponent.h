// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "FGAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	// Begin UActorComponent Interface
	virtual void OnRegister() override;
	// End UActorComponent Interface
	
	// Begin UAIPerceptionComponent Interface
	virtual void HandleExpiredStimulus( FAIStimulus& StimulusStore ) override;
	// End UAIPerceptionComponent Interface

protected:
	UPROPERTY()
	class AFGCreatureController* mCreatureController;
};
