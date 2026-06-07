// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Audio/AudioEventsCache.h"
#include "Components/ActorComponent.h"
#include "Chaos/ChaosEngineInterface.h"
#include "FGWheeledVehicleVFXHandler.generated.h"

class UAnimMontage;
class UAkComponent;
class UParticleSystemComponent;
class UAkAudioEvent;
class UMaterial;
class UPhysicalMaterial;
class UMaterialInterface;
class UParticleSystem;
class USkeletalMeshComponent;

USTRUCT( BlueprintType )
struct FACTORYGAME_API FTireTrackDecalDetails
{
	GENERATED_BODY()

	/** Surface material to override for */
	UPROPERTY( EditAnywhere, Category = "Vehicle" )
	TObjectPtr<UPhysicalMaterial> SurfacePhysicsMaterial;

	/** Material to use as an override */
	UPROPERTY( EditAnywhere, Category = "Vehicle" )
	TObjectPtr<UMaterialInterface> DecalMaterialOverride;
};

USTRUCT( BlueprintType )
struct FSurfaceParticlePair
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, Category = "Surface Particle Profile" )
	TObjectPtr<UParticleSystem> EmitterTemplate;

	UPROPERTY( EditAnywhere, Category = "Surface Particle Profile" )
	TEnumAsByte<EPhysicalSurface> Surface = SurfaceType_Default;
};

USTRUCT( BlueprintType )
struct FWheelSoundSurfacePair
{
	GENERATED_BODY()

	FORCEINLINE FWheelSoundSurfacePair()
	{
		Surfaces = TArray<TEnumAsByte<EPhysicalSurface>>{SurfaceType_Default};
	}

	UPROPERTY( EditAnywhere, Category = "Surface Sound Profile" )
	TSoftObjectPtr<UAkAudioEvent> PlayEvent;

	UPROPERTY( EditAnywhere, Category = "Surface Sound Profile" )
	TObjectPtr<UAkAudioEvent> StopEvent; //This is HARD ref intentionally to avoid any potential issues with stopping async events

	UPROPERTY( EditAnywhere, Category = "Surface Sound Profile" )
	TArray<TEnumAsByte<EPhysicalSurface>> Surfaces;
};

USTRUCT()
struct FParticleTemplatePair
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UParticleSystem> Template;

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> Particle;
};

struct FFGVehicleWheelVFXData
{
	bool bHasContact{false};
	FVector ContactPoint{ForceInit};
	TWeakObjectPtr<UPhysicalMaterial> ContactMaterial;
	float WheelSkidMagnitude{0.0f};
};

struct FFGVehicleVFXData
{
	bool bIsVehicleAirborne{false};
	float VehicleForwardSpeed{0.0f};
	bool bIsSubmergedInWater{false};
	bool bVehicleHasFuel{false};
	bool bVehicleHasDriver{false};
	TArray<FChaosWheelSetup> WheelsSetup;
	TArray<FFGVehicleWheelVFXData> Wheels;
	float VehicleThrottleInput{0.0f};
	float VehicleEngineRPM{0.0f};
	bool bIsHandbrakeActive{false};
};

UCLASS()
class FACTORYGAME_API UFGWheeledVehicleVFXHandler : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGWheeledVehicleVFXHandler();

	void PrecacheVehicleAudioEvents();
	void TickVehicleVisuals( USkeletalMeshComponent* vehicleRootComponent, const FFGVehicleVFXData& vehicleData, float deltaTime );
	void NotifyVehicleGearChangeImmediate( int32 newGear ) const;
	void NotifyVehicleGearChangeBegin( int32 newGear ) const;
	void NotifyVehicleGearChangeEnd( int32 newGear ) const;
	void DestroyVehicleVisuals();

	/** Map that lists which templates corresponds to what surface type */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TArray<FSurfaceParticlePair> mVehicleParticleMap;

	/** Distance between tire track decals */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	float mDistanceBetweenDecals{15.0f};

	/** default tire track decal. Can be empty for no default. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TObjectPtr<UMaterialInterface> mDefaultTireTrackDecal;
	
	/** tire track decal  settings */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TArray<FTireTrackDecalDetails> mTireTrackDecals;

	/** Array of the different sound switches to use with which surface. The first element without a surface is considered the default switch */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TArray<FWheelSoundSurfacePair> mVehicleSoundMap;

	/** The scale for the decal. This will probably need to be uniquely set for every vehicle. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	FVector mDecalSize{ForceInit};

	/** Time, in seconds, for the tire track decal to live */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	float mDecalsLifespan{5.0f};

	/** Speed at which tire sounds will have their RTPC set to max (100). In Kmh */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	float mTireSoundMaxAtSpeed{100.0f};

	/** Skidding speed at which tire skidding sounds will have their RTPC set to max (100). In Kmh */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	float mTireSkidSoundMaxAtSpeed{50.0f};

	/** Attenuation scaling factor for Wise for wheel sounds in 3rd person (so not the vehicle the player drives, but one he sees driven by another player/AI */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	float mTires3PAttenuationScalingFactor{1.0f};

	/** Audio event used for the engine sounds of the vehicle */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TSoftObjectPtr<UAkAudioEvent> mEngineAudioPlayEvent;

	/** Audio event used to stop the engine sounds of the vehicle */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TSoftObjectPtr<UAkAudioEvent> mEngineAudioStopEvent;

	/** Audio event used to stop the engine sounds of the vehicle (when submerged in water or ran out of fuel) */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TSoftObjectPtr<UAkAudioEvent> mEngineShutdownSoundEvent;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
    TSoftObjectPtr<UAkAudioEvent> mTransmissionAudioEventGearChangeBegin;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
    TSoftObjectPtr<UAkAudioEvent> mTransmissionAudioEventGearChangeEnd;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
    TSoftObjectPtr<UAkAudioEvent> mTransmissionAudioEventGearChangedImmediate;

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TSoftObjectPtr<UAkAudioEvent> mCrashSoundEvent;

	/** Minimum acceleration to trigger the impact effects */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	float mImpactAcceleration{300.0f};

	/** Max impact acceleration at which point the effects will be at their strongest (e.g. the sound will be the loudest) */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	float mMaxImpactAcceleration{1100.0f};

	/** Particle emitter template for the exhaust smoke of the vehicle */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TObjectPtr<UParticleSystem> mExhaustSmokeTemplate;

	/** Montage to play on the vehicle mesh when driving it with engine on */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	TObjectPtr<UAnimMontage> mEngineRunningMontage;

	/** Socket for where the engine sounds come from (or exhaust in our case mostly) */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	FName mEngineAudioSocket{TEXT("exhaustSocket")};

	/** Socket for attaching the exhaust smoke particle system to */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	FName mExhaustVFXSocket{TEXT("exhaustSocket")};

	/** Name of the RTPC used to drive the vehicle's speed audio */
    UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
    FName mSpeedRTPCName{TEXT("RTPC_Vehicle_Tires_Speed")};

    /** Name of the RTPC to drive the vehicle's skidding magnitude audio */
    UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
    FName mSkidRTPCName{TEXT("RTPC_Vehicle_Tire_Skid")};

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	FName mEngineRPMRTPCName{TEXT("RTPC_Vehicles_Explorer_RPM")};

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	FName mEngineLoadRTPCName{TEXT("RTPC_Vehicle_Load")};

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle VFX/SFX" )
	FName mCrashRTPCName{TEXT("RTPC_Vehicle_Impact_Speed")};
protected:
	/** Contains references to all current active particle systems on the tires */
	UPROPERTY()
	TArray<FParticleTemplatePair> mActiveParticleAndTemplate;

	/** Location of the last placed decals for each wheel */
	TArray<FVector> mLastDecalLocations;

	/** Audio component for the vehicle wheels */
	UPROPERTY()
	TObjectPtr<UAkComponent> mVehicleWheelsAudioComponent;

	/** Audio component for the vehicle engine */
	UPROPERTY()
	TObjectPtr<UAkComponent> mVehicleEngineAudioComponent;

	/** True if vehicle engine running sound is playing */
	bool mIsVehicleEngineSoundActive{false};

	UPROPERTY()
	TObjectPtr<UAkAudioEvent> mCurrentVehicleAudioStopEvent;

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> mVehicleEngineExhaustSmokeEmitter;

	UPROPERTY()
	FAudioEventsCache mAudioEventsCache;

	bool mVehicleAudioEventsPrecached{false};
	float mVehicleImpactSoundGracePeriod{0.0f};
	float mLastFrameVehicleSpeed{-1.0f};
};
