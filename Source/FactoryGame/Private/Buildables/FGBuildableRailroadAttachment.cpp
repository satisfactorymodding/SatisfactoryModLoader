#include "Buildables/FGBuildableRailroadAttachment.h"
#include "Components/SceneComponent.h"
#include "FGRailroadTrackConnectionComponent.h"

AFGBuildableRailroadAttachment::AFGBuildableRailroadAttachment() : Super() {
	this->mIsEndStop = false;
	this->mConnection = CreateDefaultSubobject<UFGRailroadTrackConnectionComponent>(TEXT("TrackConnection0"));
	this->mConnection->SetMobility(EComponentMobility::Static);
	this->mConnection->SetupAttachment(RootComponent);
}
void AFGBuildableRailroadAttachment::OnTrainVehicleHitEndStop_Implementation(class AFGRailroadVehicle* vehicle, float velocity){ }
