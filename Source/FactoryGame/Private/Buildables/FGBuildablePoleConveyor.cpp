#include "Buildables/FGBuildablePoleConveyor.h"
#include "Components/SceneComponent.h"
#include "FGFactoryConnectionComponent.h"

AFGBuildablePoleConveyor::AFGBuildablePoleConveyor() : Super() {
	this->mSnapOnly0 = CreateDefaultSubobject<UFGFactoryConnectionComponent>(TEXT("SnapOnly0"));
	this->mSnapOnly0->SetMobility(EComponentMobility::Static);
	this->mSnapOnly0->SetupAttachment(RootComponent);
}
