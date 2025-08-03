#include "Audio/FGLocalAudioContextSubsystem.h"

AFGLocalAudioContextSubsystem::AFGLocalAudioContextSubsystem() : Super() {
	this->mLocalAcousticContextHeight = nullptr;
	this->mLocalAcousticContextWidth = nullptr;
	this->mSlapbackLeft = nullptr;
	this->mSlapbackRight = nullptr;
	this->mIsInside = nullptr;
	this->mDefaultMaterialTypeState = nullptr;
	this->MostHitMaterialState = nullptr;
	this->PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryActorTick.bTickEvenWhenPaused = false;
	this->PrimaryActorTick.bCanEverTick = true;
	this->PrimaryActorTick.bStartWithTickEnabled = true;
	this->PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryActorTick.TickInterval = 0.0;
}
AFGLocalAudioContextSubsystem* AFGLocalAudioContextSubsystem::Get(class UWorld* world){ return nullptr; }
void AFGLocalAudioContextSubsystem::BeginPlay(){ Super::BeginPlay(); }
void AFGLocalAudioContextSubsystem::Tick(float DeltaTime){ Super::Tick(DeltaTime); }
void AFGLocalAudioContextSubsystem::DisplayDebug(class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos){ Super::DisplayDebug(canvas, debugDisplay, YL, YPos); }
void AFGLocalAudioContextSubsystem::TickHorizontalRTPC(){ }
void AFGLocalAudioContextSubsystem::TickVerticalRTPC(){ }
void AFGLocalAudioContextSubsystem::TickAngularRTPC(){ }
void AFGLocalAudioContextSubsystem::TickSlapbackRTPC(){ }
void AFGLocalAudioContextSubsystem::TickMaterialTypeRTPC(){ }
float AFGLocalAudioContextSubsystem::CalculateAzimuthPlane(){ return 0; }
float AFGLocalAudioContextSubsystem::CalculateZenithPlane(){ return 0; }
void AFGLocalAudioContextSubsystem::CalculateAngularPlane(float VerticalPlaneHeight){ }
void AFGLocalAudioContextSubsystem::CalculateWallPlanes(float& AveragedLeftPlane, float& AveragedRightPlane){ }
float AFGLocalAudioContextSubsystem::PerformHorizontalPhase(int offsetDegree, TArray<AudioHitInfo>& HitPoints){ return 0; }
float AFGLocalAudioContextSubsystem::PerformVerticalPhase(){ return 0; }
void AFGLocalAudioContextSubsystem::PerformAngularPhase(float OffsetZ){ }
void AFGLocalAudioContextSubsystem::OnHorizontalTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data){ }
void AFGLocalAudioContextSubsystem::OnVerticalTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data){ }
void AFGLocalAudioContextSubsystem::OnAngularTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data){ }
void AFGLocalAudioContextSubsystem::DisplayDebugGraphs(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos, float indent){ }
void AFGLocalAudioContextSubsystem::DisplayDebugWalls(){ }
void AFGLocalAudioContextSubsystem::DisplayDebugHits(){ }
void AFGLocalAudioContextSubsystem::MakeAsyncAudioRaycast(UWorld* World, const FVector& Start, const FVector& End, const FTraceDelegate& Delegate){ }
UAkAudioEvent* AFGLocalAudioContextSubsystem::ResolveSoftAudioReference(TSoftObjectPtr<UAkAudioEvent> InputSoftObject){ return nullptr; }