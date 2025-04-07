#include "Hologram/FGSplineBuildableSnapHologram.h"
#include "Net/UnrealNetwork.h"

AFGSplineBuildableSnapHologram::AFGSplineBuildableSnapHologram() : Super() {
	this->mMaxValidTurnOffset = 140.0;
	this->mMaxValidTurnAngle = 2.0;
	this->mSnappedSplineBuildable = nullptr;
	this->mSplineInterface = nullptr;
	this->mSnappedOffset = 0.0;
}
void AFGSplineBuildableSnapHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGSplineBuildableSnapHologram::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGSplineBuildableSnapHologram, mSnappedSplineBuildable);
	DOREPLIFETIME(AFGSplineBuildableSnapHologram, mSnappedOffset);
}
void AFGSplineBuildableSnapHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
void AFGSplineBuildableSnapHologram::ConfigureActor(AFGBuildable* inBuildable) const{ Super::ConfigureActor(inBuildable); }
bool AFGSplineBuildableSnapHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
bool AFGSplineBuildableSnapHologram::IsValidHitResult(const FHitResult& hitResult) const{ return Super::IsValidHitResult(hitResult); }
float AFGSplineBuildableSnapHologram::GetHologramHoverHeight() const{ return Super::GetHologramHoverHeight(); }
void AFGSplineBuildableSnapHologram::GetIgnoredClearanceActors(TSet<AActor*>& ignoredActors) const{ Super::GetIgnoredClearanceActors(ignoredActors); }
bool AFGSplineBuildableSnapHologram::CanNudgeHologram() const{ return Super::CanNudgeHologram(); }
bool AFGSplineBuildableSnapHologram::ShouldActorBeConsideredForGuidelines(class AActor* actor) const{ return Super::ShouldActorBeConsideredForGuidelines(actor); }
int32 AFGSplineBuildableSnapHologram::GetRotationStep() const{ return Super::GetRotationStep(); }
void AFGSplineBuildableSnapHologram::ConfigureComponents(class AFGBuildable* inBuildable) const{ Super::ConfigureComponents(inBuildable); }
void AFGSplineBuildableSnapHologram::CheckValidPlacement(){ Super::CheckValidPlacement(); }