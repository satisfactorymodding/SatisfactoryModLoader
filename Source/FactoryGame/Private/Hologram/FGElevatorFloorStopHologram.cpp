#include "Hologram/FGElevatorFloorStopHologram.h"

AFGElevatorFloorStopHologram::AFGElevatorFloorStopHologram() : Super() {
	this->mParentElevatorHologram = nullptr;
	this->mOwningElevator = nullptr;
	this->mUpgradedFloorStop = nullptr;
	this->mCanLockHologram = false;
	this->mCanNudgeHologram = false;
}
bool AFGElevatorFloorStopHologram::IsValidHitResult(const FHitResult& hitResult) const{ return Super::IsValidHitResult(hitResult); }
void AFGElevatorFloorStopHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
void AFGElevatorFloorStopHologram::CheckValidPlacement(){ Super::CheckValidPlacement(); }
bool AFGElevatorFloorStopHologram::CanNudgeHologram() const{ return Super::CanNudgeHologram(); }
AActor* AFGElevatorFloorStopHologram::GetUpgradedActor() const{ return Super::GetUpgradedActor(); }
void AFGElevatorFloorStopHologram::ConfigureActor(AFGBuildable* inBuildable) const{ Super::ConfigureActor(inBuildable); }
void AFGElevatorFloorStopHologram::ConfigureComponents(AFGBuildable* inBuildable) const{ Super::ConfigureComponents(inBuildable); }
bool AFGElevatorFloorStopHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
bool AFGElevatorFloorStopHologram::TryUpgrade(const FHitResult& hitResult){ return Super::TryUpgrade(hitResult); }
int32 AFGElevatorFloorStopHologram::GetRotationStep() const{ return Super::GetRotationStep(); }
