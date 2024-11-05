// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AkAudioEvent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "ChaosVehicleWheel.h"
#include "EngineSystem.h"
#include "TransmissionSystem.h"

#include "FGWheeledVehicleMovementComponent.generated.h"

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

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTireTrackDecalDetails
{
	GENERATED_BODY()

	/** Surface material to override for */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TObjectPtr<UPhysicalMaterial> SurfacePhysicsMaterial = nullptr;

	/** Material to use as an override */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TObjectPtr<UMaterial> DecalMaterialOverride = nullptr;
};

USTRUCT( BlueprintType )
struct FSurfaceParticlePair
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, Category = "SurfaceParticlePair" )
	TObjectPtr<UParticleSystem> EmitterTemplate = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "SurfaceParticlePair" )
	TEnumAsByte< EPhysicalSurface > Surface = EPhysicalSurface::SurfaceType_Default;
};

USTRUCT()
struct FParticleTemplatePair
{
	GENERATED_BODY()

	FParticleTemplatePair() : Template( nullptr ), Particle( nullptr ) {}

	UPROPERTY()
	TObjectPtr<UParticleSystem> Template;

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> Particle;
};

USTRUCT( BlueprintType )
struct FWheelSoundSurfacePair
{
	GENERATED_BODY()

	FWheelSoundSurfacePair() : PlayEvent( NoInit ), StopEvent( NoInit )
	{
		Surfaces = TArray<TEnumAsByte<EPhysicalSurface>>{EPhysicalSurface::SurfaceType_Default};
	}
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAkAudioEvent> PlayEvent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAkAudioEvent> StopEvent;

	UPROPERTY( EditDefaultsOnly)
	TArray<TEnumAsByte< EPhysicalSurface >> Surfaces;
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

	/** To update significance from the vehicle */
	void UpdateSignificance(bool isSignificant);

	/** Returns the actual steering input internal to the system (so not the raw input but how far the wheel is turned */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetModifiedSteeringInput() const { return SteeringInput; }

	/** returns the actual throttle input internal to the system (so not the raw input but how far the throttle is pushed */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetModifiedThrottleInput() const { return ThrottleInput; }

	/** returns the actual brake input internal to the system (so not the raw input but how far the brake is pushed */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetModifiedBrakeInput() const { return BrakeInput; }

	/** Sets if the vehicle is driven or not, to handle sleep and whatnot */
	UFUNCTION(BlueprintCallable, Category = Vehicle)
	void SetHasDriver( bool hasDriver, bool isLocalDriver );

	/** Used to drive audio. */
	void HandleEngineSounds( const bool hasFuel );
	
	/** Is the vehicle in the air? */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE bool IsInAir() const { return mNumWheelsOnGround == 0; }

	/** Get the wheel particle system associated with that physical material it is on */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	UParticleSystem* GetSurfaceParticleSystem( UPhysicalMaterial* PhysMat);

	/** Gets the mass of the vehicle as set in the vehicle properties */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE float GetVehicleMass() const { return Mass; }

	/** Get the surface that most wheels are on, if any. Can be null */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	FORCEINLINE UPhysicalMaterial* GetPrimarySurfaceMaterial() const { return mPrimarySurfaceMaterial; }

	/** When a vehicle lands, this triggers */
	UPROPERTY(BlueprintAssignable, Category = Vehicle)
	FVehicleLandedDelegate mOnVehicleLanded;

	virtual TUniquePtr<Chaos::FSimpleWheeledVehicle> CreatePhysicsVehicle() override
	{
		VehicleSimulationPT = MakeUnique<UFGWheeledVehicleSimulation>(); // Custom vehicle simulation
		PVehicleOutput = MakeUnique<FPhysicsVehicleOutput>();	// create physics output container
		
		return MakeUnique<FFGSimpleWheeledVehicle>();
	}

	UFUNCTION(BlueprintPure, Category="Vehicle|Engine")
	UAkComponent* GetEngineAudioComponent() const { return mEngineAudioComponent; }

	UFUNCTION(BlueprintNativeEvent, Category="Vehicle|Transmission")
	void OnGearChangedImmediate( int32 NewGear );

	UFUNCTION(BlueprintNativeEvent, Category="Vehicle|Transmission")
	void OnGearChangeBegin( int32 NewGear );

	UFUNCTION(BlueprintNativeEvent, Category="Vehicle|Transmission")
	void OnGearChangeEnd( int32 NewGear );

	void SetClientInputsOnDriverLeave();
	
	UPROPERTY(BlueprintAssignable, Category = Vehicle)
	FVehicleTransmissionEventDelegate mOnGearChangedImmediate;

	UPROPERTY(BlueprintAssignable, Category = Vehicle)
	FVehicleTransmissionEventDelegate mOnGearChangeBegin;

	UPROPERTY(BlueprintAssignable, Category = Vehicle)
	FVehicleTransmissionEventDelegate mOnGearChangeEnd;

	void PlayStartupEngineAudio();
	void PlayShutDownEngineAudio( const bool isOutOfFuel );

	UFUNCTION( Server, Reliable )
	void Server_PlayShutDownEngineAudio( const bool isOutOfFuel );

	UFUNCTION( Server, Reliable )
	void Server_PlayStartupEngineAudio();
	
protected:
	virtual void UpdateState(float DeltaTime) override;
	virtual void ProcessSleeping(const FControlInputs& ControlInputs) override;
	void UpdateAudioPositions( UAkComponent* audioComp );
	
	/** returns the current largest tire load of the vehicle */
	UFUNCTION(BlueprintPure, Category = Vehicle )
	float GetLargestTireLoadValue();

	/** returns the current largest slip (burnout/longitudinal) magnitude lat slip of the vehicle */
	UFUNCTION(BlueprintPure, Category = Vehicle )
	float GetLargestSlipMagnitude();

	/** returns the current largest skid (drift/lateral) magnitude of the vehicle */
	UFUNCTION(BlueprintPure, Category = Vehicle)
	float GetLargestSkidMagnitude();

	// Side slip multiplier applied to wheel affected by handbrake while using the handbrake
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelSetup)
	float mHandbrakeSideSlipMultiplier = 0.1f;

	/** Allows overriding the force multiplier of wheels based on the surface they are driving on. (i.e: Make the golf cart a soapbox in general but make it stick like fly on a flytrap on foundations) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WheelSetup)
	TArray<FSurfaceForceMultiplierOverride> mSurfaceWheelForceMultiplierOverrides;

	/** Surface on which most wheels are */
	UPROPERTY(BlueprintReadWrite, Category = Surface)
	TObjectPtr<UPhysicalMaterial> mPrimarySurfaceMaterial = nullptr;

	/** Distance between tire track decals */
	UPROPERTY( EditDefaultsOnly, Category = "WheelSetup|Effects" )
	float mDistanceBetweenDecals = 15.f;

	/** Time, in seconds, for the tire track decal to live */
	UPROPERTY( EditDefaultsOnly, Category = "WheelSetup|Effects" )
	float mDecalsLifespan = 5.0f;
	
	/** default tire track decal. Can be empty for no default. */
	UPROPERTY( EditDefaultsOnly, Category = "WheelSetup|Effects" )
	TObjectPtr<UMaterial> mDefaultTireTrackDecal;
	
	/** tire track decal  settings */
	UPROPERTY( EditDefaultsOnly, Category = "WheelSetup|Effects" )
	TArray< FTireTrackDecalDetails > mTireTrackDecals;
	
	/** The scale for the decal. This will probably need to be uniquely set for every vehicle. */
	UPROPERTY( EditDefaultsOnly, Category = "WheelSetup|Effects" )
	FVector mDecalSize;

	/** Map that lists which templates corresponds to what surface type */
	UPROPERTY( EditDefaultsOnly, Category = "WheelSetup|Effects" )
	TArray< FSurfaceParticlePair > mVehicleParticleMap;

	/** Name of the RTPC used to drive the vehicle's speed audio */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "WheelSetup|Effects" )
	FName mSpeedRTPCName = FName("RTPC_Vehicle_Tires_Speed");

	/** Name of the RTPC to drive the vehicle's skidding magnitude audio */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "WheelSetup|Effects" )
	FName mSkidRTPCName = FName("RTPC_Vehicle_Tire_Skid");

	/** Speed at which tire sounds will have their RTPC set to max (100). In Kmh */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "WheelSetup|Effects" )
	float mTireSoundMaxAtSpeed = 100;

	/** Skidding speed at which tire skidding sounds will have their RTPC set to max (100). In Kmh */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "WheelSetup|Effects" )
	float mTireSkidSoundMaxAtSpeed = 50;

	/** Attenuation scaling factor for Wwise for wheel sounds in 3rd person (so not the vehicle the player drives, but one he sees driven by another player/AI */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "WheelSetup|Effects" )
	float mTires3PAttenuationScalingFactor = 1.0f;

	/** Array of the different sound switches to use with which surface. The first element without a surface is considered the default switch */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "WheelSetup|Effects" )
	TArray< FWheelSoundSurfacePair > mVehicleSoundMap;

	/** Map of the wheel index to ak component */
	UPROPERTY(BlueprintReadOnly)
	TMap<int, TObjectPtr<UAkComponent>> mVehicleWheelAudioComponents;

	/** Contains references to all current active particle systems on the tires */
	UPROPERTY()
	TArray< FParticleTemplatePair > mActiveParticleAndTemplate;
	
	/** location of the last placed decals for each wheel */
	UPROPERTY()
	TArray< FVector > mLastDecalLocations;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|General" )
	TObjectPtr<UAkAudioEvent> mCrashSoundEvent;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|General" )
	FName mCrashRTPCName;

	/** Speed at which the RTPC for the crash sound will be set to max */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|General" )
	float mCrashMaxSpeed = 100.f;
	
	/** Audio event that's used for the engine sounds of the vehicle */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineAudio" )
	TObjectPtr<UAkAudioEvent> mEngineAudioPlayEvent;

	/** Audio event that's used to stop the engine sounds of the vehicle */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineAudio" )
	TObjectPtr<UAkAudioEvent> mEngineAudioStopEvent;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineAudio" )
	TObjectPtr<UAkAudioEvent> mEngineShutdownSoundEvent;

	/** Socket for where the engine sounds come from (or exhaust in our case mostly) */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineAudio" )
	FName mEngineAudioSocket = FName("exhaustSocket");

	/** RTPC name that will be used by the sim to drive the engine rpm audio */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineAudio" )
	FName mEngineRpmRTPC = FName("RTPC_Vehicles_Explorer_RPM");

	/** RTPC name that will be used by the sim's throttle position to drive the load audio */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineAudio" )
	FName mEngineLoadRTPC = FName("RTPC_Vehicle_Load");
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAkComponent> mEngineAudioComponent;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|TransmissionAudio" )
	TObjectPtr<UAkAudioEvent> mTransmissionAudioEventGearChangeBegin;

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|TransmissionAudio" )
	TObjectPtr<UAkAudioEvent> mTransmissionAudioEventGearChangeEnd;
	
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|TransmissionAudio" )
	TObjectPtr<UAkAudioEvent> mTransmissionAudioEventGearChangedImmediate;

	/** When we bounce off the idle rpm, how much rpm to add to the engine. Random number between min and max */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	FInt32Range mIdleBounceRange = TRange<int>(0, 150);

	/** When we bounce of the idle rpm, we can affect the rev rate of the engine a bit: just noticed it does nothing under the hood actually... */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	float mIdleRevRateBounceFactor = 0.f;

	/** When we bounce off the rev limiter, how much rpm do we subtract to the engine max rpm. Random number between min and max */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	FInt32Range mRevLimiterBounceRange = TRange<int>(100, 250);

	/** When we bounce of the rev limiter, we can affect the rev rate of the engine a bit: just noticed it does nothing under the hood actually... */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Custom|EngineSetup" )
	float mRevLimiterRevRateBounceFactor = 0.f;
	
private:
	void ReCreateSoundComponents();
	void DeleteSoundComponents();
	
	void UpdateAirStatus();

	void UpdateTireEffects();

	void UpdateTireAudio();
	
	/** The setup of the wheel when starting the simulation.
	 * Allows us to revert to stock settings when runtime modifications aren't needed anymore */
	TArray< Chaos::FSimpleWheelConfig > mInitialWheelSetup;
	
	TMap< int, FWheelSoundSurfacePair* > mVehicleWheelAudioPairs;
	
	/** How many of our wheels are on the ground */
	int mNumWheelsOnGround;
	
	/** Vehicle sets if we're significant or not. */
	bool mIsSignificant = false;

	/** Do we have a driver? */
	bool mHasDriver = false;
	
	/** Is our driver the local player */
	bool mHasLocalDriver = false;

	/** Cached value of the sleep threshold that was setup with the vehicle */
	float mInitialSleepThreshold = 0;
	
};
