#include "FGVehicleDetectionComponent.h"

UFGVehicleDetectionComponent::UFGVehicleDetectionComponent() : Super() {
	this->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
}
void UFGVehicleDetectionComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGVehicleDetectionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void UFGVehicleDetectionComponent::Private_SetIsOverlappingAnyVehicles(bool newIsOverlappingAnyVehicles){ }
