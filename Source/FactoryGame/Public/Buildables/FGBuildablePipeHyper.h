#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildablePipeBase.h"
#include "../FGPipeHyperInterface.h"
#include "FGBuildablePipeHyper.generated.h"


/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipeHyper : public AFGBuildablePipeBase, public IFGPipeHyperInterface
{
	GENERATED_BODY()
public:

	// Begin FGHyperTube Interface
	virtual float GetPipeProgressOfConnection_Implementation( const UFGPipeConnectionComponentBase* connectionEnteredThrough ) override;

	virtual void OnPipeMove_Implementation( UFGCharacterMovementComponent* charMove, float deltaTime ) override;

	UFGPipeConnectionComponentBase* GetEndOfPipeInDirectionAndMaxDist( const UFGPipeConnectionComponentBase* enterFromConnection, float maxDist, float& distSoFar ) const;
	virtual bool OnPipeEnter_Implementation( UFGCharacterMovementComponent* charMove, const UFGPipeConnectionComponentBase* connectionEnteredThrough = nullptr, const AActor* fromPipe = nullptr ) override;
	// End FGHyperTube Interface
private:



public:
	FORCEINLINE ~AFGBuildablePipeHyper() = default;
};

