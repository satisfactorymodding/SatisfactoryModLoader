// This file has been automatically generated by the Unreal Header Implementation tool

#include "Hologram/FGVehicleHologram.h"
#include "Net/UnrealNetwork.h"

AFGVehicleHologram::AFGVehicleHologram() : Super() {
	this->mCreateClearanceSnapMeshVisualization = false;
}
void AFGVehicleHologram::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGVehicleHologram, mCustomizationData);
}
void AFGVehicleHologram::BeginPlay(){ Super::BeginPlay(); }
AActor* AFGVehicleHologram::Construct(TArray< AActor* >& out_children, FNetConstructionID netConstructionID){ return nullptr; }
void AFGVehicleHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ }
void AFGVehicleHologram::SetCustomizationData(const struct FFactoryCustomizationData& customizationData){  }
void AFGVehicleHologram::CheckValidPlacement(){ }
FTransform AFGVehicleHologram::GetVehicleSpawnTransform() const{ return FTransform(); }
AFGVehicle* AFGVehicleHologram::ConstructVehicle(FNetConstructionID netConstructionID) const{ return nullptr; }
void AFGVehicleHologram::ApplyCustomizationData(){  }
void AFGVehicleHologram::OnGamestateReceived(){ Super::OnGamestateReceived(); }
void AFGVehicleHologram::OnRep_CustomizationData(){  }