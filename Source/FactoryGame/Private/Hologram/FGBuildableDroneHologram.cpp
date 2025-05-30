// This file has been automatically generated by the Unreal Header Implementation tool

#include "Hologram/FGBuildableDroneHologram.h"
#include "Net/UnrealNetwork.h"

AFGBuildableDroneHologram::AFGBuildableDroneHologram() : Super() {
	this->mSnappedStation = nullptr;
}
void AFGBuildableDroneHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableDroneHologram::Destroyed(){ Super::Destroyed(); }
void AFGBuildableDroneHologram::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableDroneHologram, mSnappedStation);
}
bool AFGBuildableDroneHologram::TrySnapToActor(const FHitResult& hitResult){ return bool(); }
void AFGBuildableDroneHologram::GetIgnoredClearanceActors(TSet< AActor* >& ignoredActors) const{ }
void AFGBuildableDroneHologram::CheckValidPlacement(){ }
AFGVehicle* AFGBuildableDroneHologram::ConstructVehicle(FNetConstructionID netConstructionID) const{ return nullptr; }
