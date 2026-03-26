// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "ChaosVehicleWheel.h"
#include "EngineSystem.h"
#include "FGWheeledVehicleVFXHandler.h"
#include "TransmissionSystem.h"
#include "FGWheeledVehicleMovementComponent.generated.h"

class UAkAudioEvent;
struct FWheelSoundSurfacePair;

USTRUCT(BlueprintType)
struct FSurfaceForceMultiplierOverride
{
	GENERATED_BODY()

	FSurfaceForceMultiplierOverride() : OverrideForceMultiplier( 1 )
	{
		Surfaces = TArray<TEnumAsByte<EPhysicalSurface>>{EPhysicalSurface::SurfaceType_Default};
	}

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float OverrideForceMultiplier = 1.0f;
	
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TArray<TEnumAsByte<EPhysicalSurface>> Surfaces;
};

class FACTORYGAME_API FFGSimpleEngineSim : public Chaos::FSimpleEngineSim
{
public:
	explicit FFGSimpleEngineSim(const Chaos::FSimpleEngineConfig* StaticDataIn);

	virtual ~FFGSimpleEngineSim();
	
	float GetThrottlePosition() const
	{
		return ThrottlePosition;
	}

	virtual void Simulate( float DeltaTime ) override;

	TRange<int> mIdleBounceRange;

	TRange<int> mRevLimiterBounceRange;

	float mIdleRevRateBounceFactor = 0.f;

	float mRevLimiterRevRateBounceFactor = 0.f;
};

DECLARE_MULTICAST_DELEGATE_OneParam( FTransmissionEventDelegate, int32 );

class FACTORYGAME_API FFGSimpleTransmissionSim : public Chaos::FSimpleTransmissionSim
{
public:
	explicit FFGSimpleTransmissionSim(const Chaos::FSimpleTransmissionConfig* SetupIn);

	virtual ~FFGSimpleTransmissionSim();

	virtual void SetGear(int32 InGear, bool Immediate) override;

	virtual void Simulate(float DeltaTime) override;

	/** Get the expected engine RPM from the wheel RPM in the target gear taking into account the current gear ratio (assuming no clutch slip) */
	float GetEngineRPMFromWheelRPMInTargetGear(float InWheelRPM)
	{
		return InWheelRPM * GetGearRatio(GetTargetGear());
	}
	
	/** Broadcasts when we request for an immediate gear change. Param is current gear */
	FTransmissionEventDelegate GearChangeImmediate;
	/** Broadcasts when we request a gear change with delay. Param is target gear */
	FTransmissionEventDelegate GearChangeBegin;
	/** Broadcasts when a gear change with delay completes. Param is current gear */
	FTransmissionEventDelegate GearChangeEnd;
};

class FACTORYGAME_API UFGWheeledVehicleSimulation : public UChaosWheeledVehicleSimulation
{
public:
	UFGWheeledVehicleSimulation()
	{
		QueryBox.Init();
	}

	virtual ~UFGWheeledVehicleSimulation() override
	{
		
	}

	virtual void PerformSuspensionTraces(const TArray<Chaos::FSuspensionTrace>& SuspensionTrace, FCollisionQueryParams& TraceParams, FCollisionResponseContainer& CollisionResponse, TArray<FWheelTraceParams>& WheelTraceParams) override;
	virtual void ProcessMechanicalSimulation(float DeltaTime) override;
};

/**
 * This class is currently just a container for the simulation components used by a wheeled vehicle
 * Keeping all the physics systems together and accessible through the one vehicle class
 */
class FFGSimpleWheeledVehicle : public Chaos::FSimpleWheeledVehicle
{
public:
	FFGSimpleWheeledVehicle()
	: FSimpleWheeledVehicle()
	{

	}

	virtual ~FFGSimpleWheeledVehicle() override
	{

	}

	FFGSimpleEngineSim* GetEngine()
	{
		check(Engine.Num() == 1);
		return static_cast< FFGSimpleEngineSim* >(Engine[ 0 ]);
	}

	FFGSimpleTransmissionSim* GetTransmission()
	{
		check(Transmission.Num() == 1);
		return static_cast<FFGSimpleTransmissionSim*>(Transmission[0]);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FVehicleLandedDelegate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FVehicleTransmissionEventDelegate, int32, NewGear );

UCLASS( BlueprintType, meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGWheeledVehicleMovementComponent : public UChaosWheeledVehicleMovementComponent
{
	GENERATED_BODY()

public:
	virtual void PreTickGT( float DeltaTime ) override;
	virtual void SetupVehicle(TUniquePtr<Chaos::FSimpleWheeledVehicle>& PVehicle) override;
	virtual void CreateWheels() override;

	/** Returns the actual steering input internal to the system (so not the raw input but how far the wheel is turned */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetModifiedSteeringInput() const { return SteeringInput; }

	/** returns the actual throttle input internal to the system (so not the raw input but how far the throttle is pushed */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetModifiedThrottleInput() const { return ThrottleInput; }

	/** returns the actual brake input internal to the system (so not the raw input but how far the brake is pushed */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetModifiedBrakeInput() const { return BrakeInput; }

	/** Is the vehicle in the air? */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE bool IsInAir() const { return !VehicleState.bAllWheelsOnGround; }

	/** Sets if the vehicle is driven or not, to handle sleep and whatnot */
	void SetHasDriver( bool hasDriver );
	/** Resets all player inputs on this vehicle. Called when entering a manual docking state or running out of fuel */
	void ClearLocalVehicleInput();
	/** Completely resets all player inputs on the vehicle. Called when entering a simulated mode or player exiting the vehicle */
	void HardResetVehiclePlayerInputOnServer();
	/** Populates visual state of the vehicle when using the vehicle movement component */
	void PopulateVehicleVisualState( FFGVehicleVFXData& vehicleVisualState ) const;

	/** Gets the mass of the vehicle as set in the vehicle properties */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetVehicleMass() const { return Mass; }

	virtual TUniquePtr<Chaos::FSimpleWheeledVehicle> CreatePhysicsVehicle() override
	{
		VehicleSimulationPT = MakeUnique<UFGWheeledVehicleSimulation>(); // Custom vehicle simulation
		PVehicleOutput = MakeUnique<FPhysicsVehicleOutput>();	// create physics output container
		return MakeUnique<FFGSimpleWheeledVehicle>();
	}

	UPROPERTY(BlueprintAssignable, Category = Vehicle)
	FVehicleTransmissionEventDelegate mOnGearChangedImmediate;

	UPROPERTY(BlueprintAssignable, Category = Vehicle)
	FVehicleTransmissionEventDelegate mOnGearChangeBegin;

	UPROPERTY(BlueprintAssignable, Category = Vehicle)
	FVehicleTransmissionEventDelegate mOnGearChangeEnd;
protected:
	virtual void UpdateState(float DeltaTime) override;
	virtual void ProcessSleeping(const FControlInputs& ControlInputs) override;

	virtual void OnGearChangedImmediate_NonGameThread( int32 NewGear );
	virtual void OnGearChangeBegin_NonGameThread( int32 NewGear );
	virtual void OnGearChangeEnd_NonGameThread( int32 NewGear );

	/** Sideslip multiplier applied to wheel affected by handbrake while using the handbrake */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelSetup)
	float mHandbrakeSideSlipMultiplier = 0.1f;

	/** Allows overriding the force multiplier of wheels based on the surface they are driving on. (i.e: Make the golf cart a soapbox in general but make it stick like fly on a flytrap on foundations) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelSetup)
	TArray<FSurfaceForceMultiplierOverride> mSurfaceWheelForceMultiplierOverrides;

	/** When we bounce off the idle rpm, how much rpm to add to the engine. Random number between min and max */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	FInt32Range mIdleBounceRange = TRange<int32>(0, 150);

	/** When we bounce of the idle rpm, we can affect the rev rate of the engine a bit: just noticed it does nothing under the hood actually... */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	float mIdleRevRateBounceFactor = 0.0f;

	/** When we bounce off the rev limiter, how much rpm do we subtract to the engine max rpm. Random number between min and max */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	FInt32Range mRevLimiterBounceRange = TRange<int32>(100, 250);

	/** When we bounce of the rev limiter, we can affect the rev rate of the engine a bit: just noticed it does nothing under the hood actually... */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	float mRevLimiterRevRateBounceFactor = 0.0f;
private:
	/** The setup of the wheel when starting the simulation.
	 * Allows us to revert to stock settings when runtime modifications aren't needed anymore */
	TArray<Chaos::FSimpleWheelConfig> mInitialWheelSetup;

	/** Do we have a driver? */
	bool mHasDriver{false};
	/** Cached value of the sleep threshold that was set up with the vehicle */
	float mInitialSleepThreshold{0.0f};

	float mCachedEngineThrottle{0.0f};
	float mCachedEngineRPM{0.0f};
};
