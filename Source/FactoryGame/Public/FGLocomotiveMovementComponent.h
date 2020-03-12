// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "Curves/CurveFloat.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "FGRailroadVehicleMovementComponent.h"
#include "FGLocomotiveMovementComponent.generated.h"

/**
 * Enum to indicate which MU state a locomotive is in.
 * Disabled: MU is disabled, train has no driver (nor AI).
 * Master: This unit controls all slave units in the train, this is where the driver sits (or AI).
 * Slave: Cannot be controlled, even if occupied by a player, gets input from the master.
 */
UENUM()
enum class EMultipleUnitControl : uint8
{
	MUC_Disabled	UMETA( DisplayName = "Disabled" ),
	MUC_Master		UMETA( DisplayName = "Master" ),
	MUC_Slave		UMETA( DisplayName = "Slave" )
};

/**
 * Some replicated state for this movement component.
 */
USTRUCT()
struct FACTORYGAME_API FReplicatedRailroadVehicleState
{
	GENERATED_USTRUCT_BODY()

	// input replication: steering
	UPROPERTY()
	int32 ReverserInput;

	// input replication: steering
	UPROPERTY()
	float SteeringInput;

	// input replication: throttle
	UPROPERTY()
	float ThrottleInput;

	// input replication: dynamic brakes
	UPROPERTY()
	float DynamicBrakeInput;

	// input replication: air brakes
	UPROPERTY()
	float AirBrakeInput;

	//@todotrains Tooot input

public:
	FORCEINLINE ~FReplicatedRailroadVehicleState() = default;
};

USTRUCT()
struct FACTORYGAME_API FRailroadVehicleInputRate
{
	GENERATED_USTRUCT_BODY()

	// Rate at which the input value rises
	UPROPERTY( EditAnywhere, Category = "VehicleInputRate" )
	float RiseRate;

	// Rate at which the input value falls
	UPROPERTY( EditAnywhere, Category = "VehicleInputRate" )
	float FallRate;

	FRailroadVehicleInputRate() :
		RiseRate( 5.0f ),
		FallRate( 5.0f )
	{
	}

	/** Change an output value using max rise and fall rates */
	float InterpInputValue( float deltaTime, float currentValue, float newValue ) const
	{
		const float deltaValue = newValue - currentValue;
		const bool isRising = ( deltaValue > 0.0f ) == ( currentValue > 0.0f );
		const float maxDeltaValue = deltaTime * ( isRising ? RiseRate : FallRate );
		const float clampedDeltaValue = FMath::Clamp( deltaValue, -maxDeltaValue, maxDeltaValue );
		return currentValue + clampedDeltaValue;
	}

public:
	FORCEINLINE ~FRailroadVehicleInputRate() = default;
};

/**
 * Movement component for locomotives.
 * This is where input and controlling of the train is happening.
 */
UCLASS()
class FACTORYGAME_API UFGLocomotiveMovementComponent : public UFGRailroadVehicleMovementComponent
{
	// MODDING EDIT
	GENERATED_BODY()
	UFGLocomotiveMovementComponent(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}	
public:
	// Begin UActorComponent Interface
	virtual void TickComponent( float dt, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction ) override;
	// End UActorComponent Interface
	
	virtual void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty, class FDefaultAllocator> & OutReplicatedProps) const override; // MODDING EDIT

	//~ Begin UFGRailroadVehicleMovementComponent interface
	virtual void ComputeConstants() override;
	virtual void TickSlaveInput( float dt, const UFGLocomotiveMovementComponent* master ) override;
	virtual void TickTractionAndFriction( float dt ) override;
	//~ End UFGRailroadVehicleMovementComponent interface

	void TickMasterInput( float dt );

	/**
	 * Set the value of the reverser control.
	 *  1: Forward, locomotive goes forwards.
     * -1: Reverse, locomotive goes backwards.
	 *  0: Neutral, locomotive goes nowhere!
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetReverserInput( int32 reverser );

	/**
	 * Set the user input for the vehicle throttle. Range [-1, 1].
	 * If negative and the vehicle is moving forward this applies dynamic braking (not same as handbrake).
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetThrottleInput( float throttle );

	/**
	 * Set the user input for the vehicle steering
	 * Negative: Flip turnout ahead to the right.
	 * Positive: Flip turnout ahead to the left.
	 * Zero: Do nothing and go with the flow.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetSteeringInput( float steering );

	/** Set the user input for air brakes (handbrake). */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetAirBrakeInput( float brake );

	/** Sets all brakes to max and the throttle to zero. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetEmergencyBrake();

	/** Returns the value of the reverser control. @see SetReverserInput */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE int32 GetReverser() const { return mReverserInput; }

	/** Get the throttle value in range [0,1]. This is not the same as the raw data passed to SetThrottleInput */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE float GetThrottle() const { return mThrottleInput; }
	
	/** Get the amount of pressure applied to the air brakes in range [0,1]. This is the trains version of hand brake. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE float GetAirBrake() const { return mAirBrakeInput; }

	/**
	 * Get the amount of dynamic braking in range [0,1]. This is the trains version of a cars engine brake.
	 * It is applied when moving forward and applying reverse throttle.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE float GetDynamicBrake() const { return mDynamicBrakeInput; }

protected:
	/** Get dynamic braking force at the given speed. [N] [kg cm/s^2] */
	FORCEINLINE float CalcDynamicBrakingEffort( float atSpeed ) const
	{
		return kNToN( MToCm( mDynamicBrakingEffortCurve.GetRichCurveConst()->Eval( CmSToKmH( atSpeed ) ) ) );
	}

	/** Get the tractive force at the given speed. [N] [kg cm/s^2] */
	FORCEINLINE float CalcTractiveEffort( float atSpeed ) const
	{
		return kNToN( MToCm( mTractiveEffortCurve.GetRichCurveConst()->Eval( CmSToKmH( atSpeed ) ) ) );
	}

	/** Compute steering input */
	float CalcSteeringInput();

	/** Compute dynamic brake input */
	float CalcDynamicBrakeInput();

	/** Compute air brake input */
	float CalcAirBrakeInput();

	/** Compute throttle input */
	float CalcThrottleInput();

	/** Clear all interpolated inputs to default values */
	void ClearInput();

	/** Read current state for simulation */
	void UpdateState( float dt, const UFGLocomotiveMovementComponent* master );

	/** Pass current state to server */
	UFUNCTION( Reliable, Server, WithValidation )
	void ServerUpdateState( int32 inReverserInput, float inSteeringInput, float inThrottleInput, float inDynamicBrakeInput, float inAirBrakeInput );

	/** Update the clients state from the replicated state */
	UFUNCTION()
	void UseReplicatedState();

private:
	/**
	 * Used to get the MU master state as our input.
	 * @note Only call this on the server.
	 */
	void UseMultipleUnitMasterState( const UFGLocomotiveMovementComponent* master );

protected:
	// replicated state of vehicle
	UPROPERTY( Transient, Replicated )
	FReplicatedRailroadVehicleState mReplicatedState;

	// What the player has the reverser set to. Values -1, 0, 1
	UPROPERTY( Transient )
	int32 mRawReverserInput;

	// What the player has the steering set to. Range -1...1
	UPROPERTY( Transient )
	float mRawSteeringInput;

	// What the player has the accelerator set to. Range -1...1
	UPROPERTY( Transient )
	float mRawThrottleInput;

	// What the dynamic brake input is set to.
	UPROPERTY( Transient )
	float mRawDynamicBrakeInput;

	// What the air brake input is set to.
	UPROPERTY( Transient )
	float mRawAirBrakeInput;

	// Rate at which input throttle can rise and fall.
	UPROPERTY( EditAnywhere, Category = "VehicleInput", AdvancedDisplay )
	FRailroadVehicleInputRate mThrottleInputRate;

	// Rate at which input dynamic brake can rise and fall.
	UPROPERTY( EditAnywhere, Category = "VehicleInput", AdvancedDisplay )
	FRailroadVehicleInputRate mDynamicBrakeInputRate;

	// Velocity at which the dynamic brake can be engaged.
	UPROPERTY( EditAnywhere, Category = "VehicleInput", AdvancedDisplay )
	float mDynamicBrakeVelocityThreshold;

	// Rate at which input air brake can rise and fall.
	UPROPERTY( EditAnywhere, Category = "VehicleInput", AdvancedDisplay )
	FRailroadVehicleInputRate mAirBrakeInputRate;

	// Reversing control output to physics system. -1, 0, 1
	UPROPERTY( Transient )
	int32 mReverserInput;

	// Steering output to physics system. Range -1...1
	UPROPERTY( Transient )
	float mSteeringInput;

	// Accelerator output to physics system. Range 0...1
	UPROPERTY( Transient )
	float mThrottleInput;

	// Air brake output to physics system. Range 0...1
	UPROPERTY( Transient )
	float mAirBrakeInput;

	// Dynamic brake output to physics system. Range 0...1
	UPROPERTY( Transient )
	float mDynamicBrakeInput;

	/** The maximum tractive force [kN] [kg m/s^2 * 1000] that can be delivered at a given speed [km/h]. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	FRuntimeFloatCurve mTractiveEffortCurve;

	/** The traction we want, may not get it due to power restrictions. */
	float mTargetTractiveEffort;

	/** The maximum dynamic braking force [kN] [kg m/s^2 * 1000] that can be delivered at a given speed [km/h]. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	FRuntimeFloatCurve mDynamicBrakingEffortCurve;

	/** How much power do we get [0,1] */
	float mPowerFactor;

public:
	FORCEINLINE ~UFGLocomotiveMovementComponent() = default;
};

// Some helper functions for converting units
// Useful for debug functions
inline FString MucToFString( EMultipleUnitControl muc )
{
	switch( muc )
	{
	case EMultipleUnitControl::MUC_Disabled:
		return FString( TEXT( "Disabled" ) );
	case EMultipleUnitControl::MUC_Master:
		return FString( TEXT( "Master" ) );
	case EMultipleUnitControl::MUC_Slave:
		return FString( TEXT( "Slave" ) );
	}

	return FString( TEXT( "Invalid" ) );
}

inline FString ReverserToFString( int reverser )
{
	switch( reverser )
	{
	case -1:
		return FString( TEXT( "R" ) );
	case 0:
		return FString( TEXT( "N" ) );
	case 1:
		return FString( TEXT( "F" ) );
	}

	return FString( TEXT( "Invalid" ) );
}
