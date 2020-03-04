#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#pragma once

// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "../FGBuildablePipePart.h"
#include "FGPipeHyperStart.generated.h"


/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGPipeHyperStart : public AFGBuildablePipeHyperPart
{
	GENERATED_BODY()
	public:

	// Begin FGHyperTube Interface
	virtual void OnPipeMove_Implementation( UFGCharacterMovementComponent* charMove, float deltaTime ) override;

	virtual bool OnPipeEnter_Implementation( UFGCharacterMovementComponent* charMove, const UFGPipeConnectionComponentBase* connectionEnteredThrough = nullptr, const AActor* fromPipe = nullptr ) override;
	// End FGHyperTube Interface
protected:

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Hyper Tube" )
	float mOpeningOffset = 350.0f;
private:
	float mTimer = 0;
	

	bool mIsEntering;

	/**Set value to above 1 to give the player a small boost when entering pipes in slow speed. 
	   Could be exploited if made too big, but it felt better and clearer feedback about slowdowns if it was a little above the usual min speed when doing initial tests.*/
	UPROPERTY( EditDefaultsOnly )
	float mInitialMinSpeedFactor = 1.4f;

public:
	FORCEINLINE ~AFGPipeHyperStart() = default;
};



