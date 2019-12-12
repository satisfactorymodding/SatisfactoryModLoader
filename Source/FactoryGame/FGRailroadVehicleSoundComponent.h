// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGRailroadVehicleSoundComponent.generated.h"


UCLASS( ClassGroup=( Custom ), BlueprintType, Blueprintable, meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGRailroadVehicleSoundComponent : public USceneComponent
{
	GENERATED_BODY()
public:	
	UFGRailroadVehicleSoundComponent();

	// Begin UActorComponent interface
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void TickComponent( float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction ) override;
	// End UActorComponent interface

protected:
	/** Let blueprint update the RTPC values. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|RTPC" )
	void UpdateRTPCs();

	/** Train started moving. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnStartedMoving();

	/** Train stopped moving. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnStoppedMoving();

	/** Air brakes are applied. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnAirBrakesApplied();

	/** Air brakes are released. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnAirBrakesReleased();

	/** Dynamic brakes are applied. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnDynamicBrakesApplied();

	/** Dynamic brakes are released. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnDynamicBrakesReleased();

	/** Throttle was applied. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnThrottleApplied();
	
	/** Throttle was released. */
	UFUNCTION( BlueprintImplementableEvent, Category = "RailroadVehicleSoundComponent|Train" )
	void OnThrottleReleased();

protected:
	/** Movement component of the first vehicle in the train. */
	UPROPERTY( BlueprintReadOnly, Category = "Movement Components" )
	class UFGRailroadVehicleMovementComponent* mVehicleMovementComponent;

	/** Movement component of the first locomotive in the train, may be none. */
	UPROPERTY( BlueprintReadOnly, Category = "Movement Components" )
	class UFGLocomotiveMovementComponent* mLocomotiveMovementComponent;

	/** Component to play events on the wheelsets. Location is the bogie bone. */
	UPROPERTY( BlueprintReadOnly, Category = "Ak" )
	class UAkComponent* mWheelsetsAkComponent;

	/** Component to play events on the locomotives. Location is the center of the actor bounds (colliding). */
	UPROPERTY( BlueprintReadOnly, Category = "Ak" )
	class UAkComponent* mEnginesAkComponent;

	/** Component to play events on all the locomotives and wagons. Location is the center of the actor bounds (colliding). */
	UPROPERTY( BlueprintReadOnly, Category = "Ak" )
	class UAkComponent* mAllVehicleCentersAkComponent;

	/** Some flags to keep track of which blueprint events to trigger. */
	uint8 mIsMoving : 1;
	uint8 mIsAirBrakesApplied : 1;
	uint8 mIsDynamicBrakesApplied : 1;
	uint8 mIsThrottleApplied : 1;
};
