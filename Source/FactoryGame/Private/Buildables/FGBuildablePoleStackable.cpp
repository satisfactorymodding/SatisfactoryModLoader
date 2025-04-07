#include "Buildables/FGBuildablePoleStackable.h"

AFGBuildablePoleStackable::AFGBuildablePoleStackable() : Super() {
	this->mStackHeight = 200.0;
}
void AFGBuildablePoleStackable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}
