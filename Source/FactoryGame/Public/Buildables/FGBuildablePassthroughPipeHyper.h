// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildablePassthrough.h"
#include "FGBuildablePipeHyper.h"
#include "FGBuildablePassthroughPipeHyper.generated.h"

UCLASS()
class FACTORYGAME_API AFGBuildablePassthroughPipeHyper : public AFGBuildablePassthroughBase, public IFGPipeHyperInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePassthroughPipeHyper();

	// Begin Actor Interface
	virtual void BeginPlay() override;
	// End Actor Interface

	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection0() const { return mConnection0; }
	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection1() const { return mConnection1; }

	// Begin IFGPipeHyperInterface
	virtual TArray<TPair<UFGPipeConnectionComponentBase*, float>> GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough) const override;
	virtual EPipeHyperEnterResult OnPipeEnterReal( AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough, TStructOnScope<FFGPipeHyperBasePipeData>& outPipeData, const TStructOnScope<FFGPipeHyperBasePipeData>& predictionPipeData ) override;
	virtual bool FindDistanceClosestToWorldLocation( AFGCharacterPlayer* charPlayer, const FVector& worldLocation, const FVector& velocity, TStructOnScope<FFGPipeHyperBasePipeData>& out_pipeData, float& out_distance ) const override;
	virtual float GetLengthAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData ) override;
	virtual void GetLocationAndRotationAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, FVector& outLocation, FVector& outDirection ) override;
	virtual UFGPipeConnectionComponentBase* GetConnectionToTransitThrough( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, float& outExitOffset ) override;
	// End IFGPipeHyperInterface
protected:
	UPROPERTY( EditDefaultsOnly, SaveGame, Category = "Passthrough" )
	UFGPipeConnectionComponentBase* mConnection0;

	UPROPERTY( EditDefaultsOnly, SaveGame, Category = "Passthrough" )
	UFGPipeConnectionComponentBase* mConnection1;
};
