// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once


#include "FactoryGame.h"
#include "Buildables/FGBuildablePipeBase.h"
#include "FGPipeHyperInterface.h"
#include "FGBuildablePipeHyper.generated.h"


/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipeHyper : public AFGBuildablePipeBase, public IFGPipeHyperInterface
{
	GENERATED_BODY()

	AFGBuildablePipeHyper();
	
public:

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
	
	// Begin FGHyperTube Interface
	virtual float GetPipeProgressOfConnection_Implementation( const UFGPipeConnectionComponentBase* connectionEnteredThrough ) override;

	virtual void OnPipeMove_Implementation( UFGCharacterMovementComponent* charMove, float deltaTime ) override;

	UFGPipeConnectionComponentBase* GetEndOfPipeInDirectionAndMaxDist( const UFGPipeConnectionComponentBase* enterFromConnection, float maxDist, float& distSoFar, bool& endIsConnectionOne ) const;
	virtual bool OnPipeEnter_Implementation( UFGCharacterMovementComponent* charMove, const UFGPipeConnectionComponentBase* connectionEnteredThrough = nullptr, const AActor* fromPipe = nullptr ) override;
	// End FGHyperTube Interface
private:

	static const FName mConnectionName0;
	static const FName mConnectionName1;

	UPROPERTY()
	FVector mExitOffset;

};

