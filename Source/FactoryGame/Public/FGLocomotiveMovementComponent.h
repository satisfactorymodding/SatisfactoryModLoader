// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
struct FReplicatedRailroadVehicleState
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	int32 ReverserInput;
	UPROPERTY()
	float ThrottleInput;
	UPROPERTY()
	float DynamicBrakeInput;
	UPROPERTY()
	float AirBrakeInput;
	UPROPERTY()
	bool HornInput;
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
};

/**
 * Movement component for locomotives.
 * This is where input and controlling of the train is happening.
 */
UCLASS()
class FACTORYGAME_API UFGLocomotiveMovementComponent : public UFGRailroadVehicleMovementComponent
{
	GENERATED_BODY()
public:
	UFGLocomotiveMovementComponent();
	
	// Begin UActorComponent Interface
	virtual void TickComponent( float dt, enum ELevelTick tickType, FActorComponentTickFunction *thisTickFunction ) override;
	// End UActorComponent Interface

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
	 * Set the user input for the vehicle steering.
	 *
	 * Negative: Flip turnout ahead one step to the left.
	 * Positive: Flip turnout ahead one step to the right.
	 * Zero: Do nothing and go with the flow.
	 *
	 * This input is consumed so if a non-zero value is set it is back to zero next frame.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetSteeringInput( int32 steering );

	/** Set the user input for air brakes (handbrake). */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetAirBrakeInput( float brake );

	/** Sets all brakes to max and the throttle to zero. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetEmergencyBrake();

	/** Choo choo */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Movement" )
	void SetHornInput( bool horn );

	/** Returns the value of the reverser control. @see SetReverserInput */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE int32 GetReverser() const { return mReverserInput; }

	/** Get the throttle value in range [0,1]. This is not the same as the raw data passed to SetThrottleInput */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE float GetThrottle() const { return mThrottleInput; }

	/**
	 * Get the requested direction from the player to put the switch in, @see SetSteeringInput.
	 *
	 * @param clear Clear the input when reading it.
	 * 
	 * @return the steering input.
	 */
	int32 GetSteering( bool clear );
	
	/** Get the amount of pressure applied to the air brakes in range [0,1]. This is the trains version of hand brake. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE float GetAirBrake() const { return mAirBrakeInput; }

	/**
	 * Get the amount of dynamic braking in range [0,1]. This is the trains version of a cars engine brake.
	 * It is applied when moving forward and applying reverse throttle.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE float GetDynamicBrake() const { return mDynamicBrakeInput; }

	/** Get the horn input, is the horn sounding or not? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Movement" )
	FORCEINLINE bool GetHornInput() const { return mHornInput; }

	/** Get the power factor this locomotive needs to run. */
	float GetTractiveEffortPct() const { return FMath::Abs( mTargetTractiveEffort ) / mMaxTractiveEffort; }
	/** Get the power factor this locomotive can return to the grid. */
	float GetRegenerativePowerFactor() const;
	/** Set the actual power factor that we got. */
	void SetTractivePowerFactor( float factor ) { mPowerFactor = factor; }
	
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

	/** Get dynamic braking force at the given speed. [N] [kg cm/s^2] */
	FORCEINLINE float CalcRegenerativePowerFactor( float atSpeed ) const
	{
		return mRegenerativePowerCurve.GetRichCurveConst()->Eval( CmSToKmH( atSpeed ) );
	}

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
	UFUNCTION( Unreliable,Server, WithValidation )
	void ServerUpdateState( int32 inReverserInput, int32 inSteeringInput, float inThrottleInput, float inDynamicBrakeInput, float inAirBrakeInput, bool inHornInput );

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
	int32 mRawSteeringInput;

	// What the player has the accelerator set to. Range -1...1
	UPROPERTY( Transient )
	float mRawThrottleInput;

	// What the dynamic brake input is set to.
	UPROPERTY( Transient )
	float mRawDynamicBrakeInput;

	// What the air brake input is set to.
	UPROPERTY( Transient )
	float mRawAirBrakeInput;

	// What the honk input is set to.
	UPROPERTY( Transient )
	bool mRawHornInput;

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

	// Are going choo choo?
	UPROPERTY( Transient )
	bool mHornInput;

	/** The maximum tractive force [kN] [kg m/s^2 * 1000] that can be delivered at a given speed [km/h]. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	FRuntimeFloatCurve mTractiveEffortCurve;

	/** The traction we want, may not get it due to power restrictions. */
	float mTargetTractiveEffort;

	/** The maximum dynamic braking force [kN] [kg m/s^2 * 1000] that can be delivered at a given speed [km/h]. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	FRuntimeFloatCurve mDynamicBrakingEffortCurve;

	/** How much of the power is given back [0,1] to the grid at a given speed [km/h] when using the dynamic brakes. */
	UPROPERTY( EditAnywhere, Category = "VehicleSetup" )
	FRuntimeFloatCurve mRegenerativePowerCurve;

	/** How much power do we get [0,1] */
	float mPowerFactor;
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
