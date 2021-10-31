// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGTrainSoundComponent.generated.h"


UCLASS( ClassGroup=( Custom ), BlueprintType, Blueprintable, meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGTrainSoundComponent : public USceneComponent
{
	GENERATED_BODY()
public:	
	UFGTrainSoundComponent();

	// Begin UActorComponent interface
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void TickComponent( float dt, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction ) override;
	// End UActorComponent interface
	
public:
	/** Stops all sounds playing on this component */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void StopAllSounds();

	/** Restart sounds after gaining significance */
	UFUNCTION( BlueprintNativeEvent, Category =  "FactoryGame|Trains|Audio" )
	void RestartSounds();
	
protected:
	/** Starts playing idle sounds */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void StartIdleSounds();

	/** Train started moving. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnStartedMoving();

	/** Train stopped moving. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnStoppedMoving();

	/** Air brakes are applied. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnAirBrakesApplied();

	/** Air brakes are released. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnAirBrakesReleased();

	/** Dynamic brakes are applied. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnDynamicBrakesApplied();

	/** Dynamic brakes are released. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnDynamicBrakesReleased();

	/** Throttle was applied. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnThrottleApplied();
	
	/** Throttle was released. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Trains|Audio" )
	void OnThrottleReleased();

private:
	void UpdateAudioPositions();
	void UpdateSmoothedTrainStats( float dt );
	void UpdateRTPCs();
	void UpdateTriggers();
	
protected:
	/** train that owns this component */
	UPROPERTY()
	class AFGTrain* mTrainOwner;

	/** Component to play events on the wheelsets. Location is the bogie bone. */
	UPROPERTY( BlueprintReadOnly, Category = "Ak" )
	class UAkComponent* mWheelsetsAkComponent;

	/** Component to play events on the locomotives. Location is the center of the actor bounds (colliding). */
	UPROPERTY( BlueprintReadOnly, Category = "Ak" )
	class UAkComponent* mEnginesAkComponent;

	/** Component to play events on all the locomotives and wagons. Location is the center of the actor bounds (colliding). */
	UPROPERTY( BlueprintReadOnly, Category = "Ak" )
	class UAkComponent* mAllVehicleCentersAkComponent;

	/** Speed of the train [cm/s]. */
	UPROPERTY( BlueprintReadOnly, Category = "Train Data" )
	float mSpeed;

	/** Traction in percent [0,1]. */
	UPROPERTY( BlueprintReadOnly, Category = "Train Data" )
	float mTractionPct;

	/** Air braking in percent [0,1]. */
	UPROPERTY( BlueprintReadOnly, Category = "Train Data" )
	float mAirBrakingPct;

	/** Dynamic braking in percent [0,1]. */
	UPROPERTY( BlueprintReadOnly, Category = "Train Data" )
	float mDynamicBrakePct;

	/** Some flags to keep track of which blueprint events to trigger. */
	uint8 mIsMoving : 1;
	uint8 mIsAirBrakesApplied : 1;
	uint8 mIsDynamicBrakesApplied : 1;
	uint8 mIsThrottleApplied : 1;
};
