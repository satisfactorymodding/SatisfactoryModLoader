// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once


#include "FactoryGame.h"
#include "FGBuildablePipeBase.h"
#include "FGPipeHyperInterface.h"
#include "FGBuildablePipeHyper.generated.h"


/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipeHyper : public AFGBuildablePipeBase, public IFGPipeHyperInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipeHyper();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin Save Interface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// end Save interface
	
	// Begin FGHyperTube Interface
	virtual TArray<TPair<UFGPipeConnectionComponentBase*, float>> GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough) const override;
	virtual EPipeHyperEnterResult OnPipeEnterReal( AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough, FFGDynamicStruct& outPipeData, const FFGDynamicStruct& predictionPipeData ) override;
	virtual bool FindDistanceClosestToWorldLocation( AFGCharacterPlayer* charPlayer, const FVector& worldLocation, const FVector& velocity, FFGDynamicStruct& out_pipeData, float& out_distance ) const override;
	virtual float GetLengthAlongPipe( AFGCharacterPlayer* charPlayer, const FFGDynamicStruct& pipeData ) override;
	virtual void GetLocationAndRotationAlongPipe( AFGCharacterPlayer* charPlayer, const FFGDynamicStruct& pipeData, float distance, FVector& outLocation, FVector& outDirection ) override;
	virtual UFGPipeConnectionComponentBase* GetConnectionToTransitThrough( AFGCharacterPlayer* charPlayer, const FFGDynamicStruct& pipeData, float distance, float& outExitOffset ) override;
	// End FGHyperTube Interface

private:
	static const FName mConnectionName0;
	static const FName mConnectionName1;
};

