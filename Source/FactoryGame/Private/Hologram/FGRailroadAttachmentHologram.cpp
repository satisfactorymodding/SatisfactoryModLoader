#include "Hologram/FGRailroadAttachmentHologram.h"

AFGRailroadAttachmentHologram::AFGRailroadAttachmentHologram() : Super() {
	this->mConnection = nullptr;
	this->mSnappedConnection = nullptr;
	this->mMustSnap = false;
	this->mNeedsValidFloor = false;
}
void AFGRailroadAttachmentHologram::BeginPlay(){ Super::BeginPlay(); }
bool AFGRailroadAttachmentHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGRailroadAttachmentHologram::PostHologramPlacement(const FHitResult& hitResult, bool callForChildren){ Super::PostHologramPlacement(hitResult, callForChildren); }
void AFGRailroadAttachmentHologram::ConfigureComponents(AFGBuildable* inBuildable) const{ Super::ConfigureComponents(inBuildable); }
void AFGRailroadAttachmentHologram::GetIgnoredClearanceActors(TSet<AActor*>& ignoredActors) const{ Super::GetIgnoredClearanceActors(ignoredActors); }