#include "Hologram/FGDockingStationHologram.h"

AFGDockingStationHologram::AFGDockingStationHologram() : Super() {
	this->mMaxPathPointElevation = 100.0;
	this->mSegmentEndPointSnapDistance = 800.0;
	this->mPathPointElevationOffset = 0.0;
}
void AFGDockingStationHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGDockingStationHologram::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
bool AFGDockingStationHologram::ShouldBuildGunHitVehiclePaths() const{ return Super::ShouldBuildGunHitVehiclePaths(); }
bool AFGDockingStationHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGDockingStationHologram::PostHologramPlacement(const FHitResult& hitResult, bool callForChildren){ Super::PostHologramPlacement(hitResult, callForChildren); }
void AFGDockingStationHologram::PreConfigureActor(class AFGBuildable* inBuildable){ Super::PreConfigureActor(inBuildable); }
void AFGDockingStationHologram::CheckValidPlacement(){ Super::CheckValidPlacement(); }
void AFGDockingStationHologram::ScrollRotate(int32 delta, int32 step){ Super::ScrollRotate(delta, step); }
AFGVehiclePathNode* AFGDockingStationHologram::GetPathNodeFromHitResult(const FHitResult& hitResult) const{ return nullptr; }
