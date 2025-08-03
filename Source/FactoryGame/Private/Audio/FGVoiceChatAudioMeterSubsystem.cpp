#include "Audio/FGVoiceChatAudioMeterSubsystem.h"

AFGVoiceChatAudioMeterSubsystem::AFGVoiceChatAudioMeterSubsystem() : Super() {
	this->mAudioMeterPeakRtpc = nullptr;
	this->mAttenuationStrengthLowRtpc = nullptr;
	this->mAttenuationStrengthMediumRtpc = nullptr;
	this->mAttenuationStrengthStrongRtpc = nullptr;
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.bStartWithTickEnabled = true;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
}
void AFGVoiceChatAudioMeterSubsystem::BeginPlay(){ Super::BeginPlay(); }
void AFGVoiceChatAudioMeterSubsystem::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGVoiceChatAudioMeterSubsystem::Tick(float DeltaTime){ Super::Tick(DeltaTime); }
void AFGVoiceChatAudioMeterSubsystem::ConvertPeakToRTPC(float peak, float DeltaTime){ }
void AFGVoiceChatAudioMeterSubsystem::SetRTPC(float AudioMeterValue){ }
