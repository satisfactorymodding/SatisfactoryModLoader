#pragma once
#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
#include "FGBuildablePipeHyperAttachment.h"
#include "FGCharacterPlayer.h"
#include "FGPipeHyperInterface.h"
#include "FGBuildablePipeHyperBooster.generated.h"

class USplineComponent;

UCLASS( )
class FACTORYGAME_API AFGBuildablePipeHyperBooster : public AFGBuildablePipeHyperAttachment, public IFGPipeHyperInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipeHyperBooster();
	
	//Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_TickProducing(float dt) override;
	virtual float GetProducingPowerConsumptionBase() const override;
	//End AFGBuildableFactory interface

	//Begin IFGPipeHyperInterface interface
	virtual TArray<TPair<UFGPipeConnectionComponentBase*, float>> GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough) const override;
	virtual EPipeHyperEnterResult OnPipeEnterReal( AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough, TStructOnScope<FFGPipeHyperBasePipeData>& outPipeData, const TStructOnScope<FFGPipeHyperBasePipeData>& predictionPipeData ) override;
	virtual bool FindDistanceClosestToWorldLocation( AFGCharacterPlayer* charPlayer, const FVector& worldLocation, const FVector& velocity, TStructOnScope<FFGPipeHyperBasePipeData>& out_pipeData, float& out_distance ) const override;
	virtual float GetLengthAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData ) override;
	virtual void GetLocationAndRotationAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, FVector& outLocation, FVector& outDirection ) override;
	virtual UFGPipeConnectionComponentBase* GetConnectionToTransitThrough( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, float& outExitOffset ) override;
	virtual void OnPipeExitReal( AFGCharacterPlayer* charPlayer, TStructOnScope<FFGPipeHyperBasePipeData>& pipeData ) override;
	virtual void OnPipeMoveStep(AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float stepLength, const FPlayerPipeHyperData& pipeTravelData, float& pipeVelocityReal, float& pipeTempMinSpeed) override;
	//End IFGPipeHyperInterface interface
protected:
	void UpdateTargetConsumption();
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Pipe Hyper" )
	USplineComponent* mSplineComponent;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	float ActivePowerConsumption;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	float PipeVelocityBoostImpulse;

	/** Players currently traveling inside of the pipe */
	UPROPERTY( VisibleAnywhere, Transient, Category = "Pipe Hyper" )
	TArray<TWeakObjectPtr<AFGCharacterPlayer>> mTravelingPlayers;
public:
	/** Called right after player has received the boost effect, used to play sounds and other effects */
	UFUNCTION( BlueprintImplementableEvent )
	void OnPlayerBoosted_Cosmetic( AFGCharacterPlayer* charPlayer );
};
