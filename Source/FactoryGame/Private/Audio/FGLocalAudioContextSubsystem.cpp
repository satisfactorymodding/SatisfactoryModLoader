#include "Audio/FGLocalAudioContextSubsystem.h"

AFGLocalAudioContextSubsystem::AFGLocalAudioContextSubsystem() : Super() {
	this->mLocalAcousticContextHeight = nullptr;
	this->mLocalAcousticContextWidth = nullptr;
	this->mSlapbackLeft = nullptr;
	this->mSlapbackRight = nullptr;
	this->mIsInside = nullptr;
	this->mCurrentChannelNumber = nullptr;
	this->mDefaultMaterialTypeState = nullptr;
	this->mDefaultHeightMaterialTypeState = nullptr;
	this->mNoHitHeightMaterialTypeState = nullptr;
	this->mDefaultMaterialTypeSwitch = nullptr;
	this->MostHitMaterialState = nullptr;
	this->MostHitVerticalMaterialState = nullptr;
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
void AFGLocalAudioContextSubsystem::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGLocalAudioContextSubsystem::Tick(float DeltaTime){ Super::Tick(DeltaTime); }
void AFGLocalAudioContextSubsystem::TickHorizontalRTPC(){ }
void AFGLocalAudioContextSubsystem::TickVerticalRTPC(){ }
void AFGLocalAudioContextSubsystem::TickAngularRTPC(){ }
void AFGLocalAudioContextSubsystem::TickSlapbackRTPC(){ }
void AFGLocalAudioContextSubsystem::TickMaterialTypeRTPC(){ }
void AFGLocalAudioContextSubsystem::SetActiveChannelsNumberRTPC(){ }
float AFGLocalAudioContextSubsystem::CalculateAzimuthPlane(){ return 0; }
float AFGLocalAudioContextSubsystem::CalculateZenithPlane(){ return 0; }
void AFGLocalAudioContextSubsystem::CalculateAngularPlane(float VerticalPlaneHeight){ }
void AFGLocalAudioContextSubsystem::CalculateWallPlanes(float& AveragedLeftPlane, float& AveragedRightPlane){ }
float AFGLocalAudioContextSubsystem::PerformHorizontalPhase(int offsetDegree, TArray<AudioHitInfo>& HitPoints){ return 0; }
void AFGLocalAudioContextSubsystem::PerformVerticalPhase(float& out_resultedAverageHeight, TWeakObjectPtr<UPhysicalMaterial>& out_mostHitMaterial){ }
void AFGLocalAudioContextSubsystem::PerformAngularPhase(float OffsetZ){ }
void AFGLocalAudioContextSubsystem::OnHorizontalTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data){ }
void AFGLocalAudioContextSubsystem::OnVerticalTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data){ }
void AFGLocalAudioContextSubsystem::OnAngularTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data){ }
TWeakObjectPtr<UPhysicalMaterial> AFGLocalAudioContextSubsystem::FindMostHitMaterial(const TArray<TWeakObjectPtr<UPhysicalMaterial>>& MaterialsHistory){ return TWeakObjectPtr<UPhysicalMaterial>(); }
void AFGLocalAudioContextSubsystem::MakeAsyncAudioRaycast(UWorld* World, const FVector& Start, const FVector& End, const FTraceDelegate& Delegate){ }
UAkAudioEvent* AFGLocalAudioContextSubsystem::ResolveSoftAudioReference(TSoftObjectPtr<UAkAudioEvent> InputSoftObject){ return nullptr; }