#include "Hologram/FGWallPassthroughHologram.h"

AFGWallPassthroughHologram::AFGWallPassthroughHologram() : Super() {
	this->mConnectionMeshes[0] = nullptr;
	this->mConnectionMeshes[1] = nullptr;
}
void AFGWallPassthroughHologram::BeginPlay(){ Super::BeginPlay(); }
bool AFGWallPassthroughHologram::IsValidHitResult(const FHitResult& hitResult) const{ return Super::IsValidHitResult(hitResult); }
bool AFGWallPassthroughHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGWallPassthroughHologram::PostHologramPlacement(const FHitResult& hitResult, bool callForChildren){ Super::PostHologramPlacement(hitResult, callForChildren); }
void AFGWallPassthroughHologram::InitializeClearanceData(){ Super::InitializeClearanceData(); }
void AFGWallPassthroughHologram::GetClearanceData(TArray<const FFGClearanceData*>& out_ClearanceData) const{ Super::GetClearanceData(out_ClearanceData); }
void AFGWallPassthroughHologram::ConfigureActor(AFGBuildable* inBuildable) const{ Super::ConfigureActor(inBuildable); }