#include "Audio/FGRainAudioSubsystem.h"

void AFGRainAudioSubsystem::FillNewRainSpots(TArray<FVector>& RainSpotsCandidates, TArray<RainPropInfo>& RainProps, float AttenuationDistance){ }
void AFGRainAudioSubsystem::DisplayDebugSpots(){ }
void AFGRainAudioSubsystem::OnBuildingAddedRemoved(AFGBuildable* buildable){ }
void AFGRainAudioSubsystem::OnFoliageInstanceRemoved(){ }
void AFGRainAudioSubsystem::Tick(float DeltaTime){ Super::Tick(DeltaTime); }
void AFGRainAudioSubsystem::DisplayDebug(class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos){ Super::DisplayDebug(canvas, debugDisplay, YL, YPos); }
void AFGRainAudioSubsystem::EnableRainAudio(){ }
void AFGRainAudioSubsystem::DisableRainAudio(){ }
void AFGRainAudioSubsystem::CreateEmitters(){ }
void AFGRainAudioSubsystem::DestroyEmitters(){ }
void AFGRainAudioSubsystem::UpdatePlayerUnderRainState(){ }
AFGRainAudioSubsystem::AFGRainAudioSubsystem(): Super() {
	this->mBuildingsRainEvent = nullptr;
	this->mBuildingsSpotsCount = 3;
	this->mBuildingsMaxDistance = 2000;
	this->mBuildingEmitterHeightRatio = 0.2;
	this->mFoliageRainEvent = nullptr;
	this->mFoliageSpotsCount = 3;
	this->mFoliageMaxDistance = 1000;
	this->mGroundRainEvent = nullptr;
	this->mGroundSpotsCount = 2;
	this->mIsInsideRain = nullptr;
	this->mSpotFilteringDistance = 300;
	this->mTimeBetweenRainSpots = 2.0;
	this->mDefaultMaterialTypeState = nullptr;
	this->MostHitMaterialState = nullptr;
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.bStartWithTickEnabled = false;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
}
AFGRainAudioSubsystem* AFGRainAudioSubsystem::Get(class UWorld* world){ return nullptr; }
AFGRainAudioSubsystem* AFGRainAudioSubsystem::Get(UObject* worldContext){ return nullptr; }
void AFGRainAudioSubsystem::BeginPlay(){ Super::BeginPlay(); }
void AFGRainAudioSubsystem::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGRainAudioSubsystem::TickRainBuildingSpots(){ }
void AFGRainAudioSubsystem::TickRainFoliageSpots(){ }
void AFGRainAudioSubsystem::TickRainGroundSpots(){ }
void AFGRainAudioSubsystem::TickMaterialTypeRTPC(){ }
void AFGRainAudioSubsystem::TickIsInsideRainRTPC(){ }
