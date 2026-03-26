#include "WheeledVehicles/FGWheeledVehicleVFXHandler.h"

UFGWheeledVehicleVFXHandler::UFGWheeledVehicleVFXHandler() : Super() {
	this->mDistanceBetweenDecals = 15.0;
	this->mDefaultTireTrackDecal = nullptr;
	this->mDecalSize = FVector::ZeroVector;
	this->mDecalsLifespan = 5.0;
	this->mTireSoundMaxAtSpeed = 100.0;
	this->mTireSkidSoundMaxAtSpeed = 50.0;
	this->mTires3PAttenuationScalingFactor = 1.0;
	this->mEngineAudioPlayEvent = nullptr;
	this->mEngineAudioStopEvent = nullptr;
	this->mEngineShutdownSoundEvent = nullptr;
	this->mTransmissionAudioEventGearChangeBegin = nullptr;
	this->mTransmissionAudioEventGearChangeEnd = nullptr;
	this->mTransmissionAudioEventGearChangedImmediate = nullptr;
	this->mCrashSoundEvent = nullptr;
	this->mImpactAcceleration = 300.0;
	this->mMaxImpactAcceleration = 1100.0;
	this->mExhaustSmokeTemplate = nullptr;
	this->mEngineRunningMontage = nullptr;
	this->mEngineAudioSocket = TEXT("exhaustSocket");
	this->mExhaustVFXSocket = TEXT("exhaustSocket");
	this->mSpeedRTPCName = TEXT("RTPC_Vehicle_Tires_Speed");
	this->mSkidRTPCName = TEXT("RTPC_Vehicle_Tire_Skid");
	this->mEngineRPMRTPCName = TEXT("RTPC_Vehicles_Explorer_RPM");
	this->mEngineLoadRTPCName = TEXT("RTPC_Vehicle_Load");
	this->mCrashRTPCName = TEXT("RTPC_Vehicle_Impact_Speed");
	this->mVehicleWheelsAudioComponent = nullptr;
	this->mVehicleEngineAudioComponent = nullptr;
	this->mCurrentVehicleAudioStopEvent = nullptr;
	this->mVehicleEngineExhaustSmokeEmitter = nullptr;
}
void UFGWheeledVehicleVFXHandler::PrecacheVehicleAudioEvents(){ }
void UFGWheeledVehicleVFXHandler::TickVehicleVisuals(USkeletalMeshComponent* vehicleRootComponent, const FFGVehicleVFXData& vehicleData, float deltaTime){ }
void UFGWheeledVehicleVFXHandler::NotifyVehicleGearChangeImmediate(int32 newGear) const{ }
void UFGWheeledVehicleVFXHandler::NotifyVehicleGearChangeBegin(int32 newGear) const{ }
void UFGWheeledVehicleVFXHandler::NotifyVehicleGearChangeEnd(int32 newGear) const{ }
void UFGWheeledVehicleVFXHandler::DestroyVehicleVisuals(){ }
