#include "AvailabilityDependencies/FGPersonalElevatorDependency.h"

UFGPersonalElevatorDependency::UFGPersonalElevatorDependency() : Super() {
	this->mEvents = 0;
}
bool UFGPersonalElevatorDependency::ShouldTriggerOnEvents(EElevatorDependencyEvent eventTypeFlags) const{ return false; }
#if WITH_EDITOR
FString UFGPersonalElevatorDependency::ToString() const{ return Super::ToString(); }
void UFGPersonalElevatorDependency::FromString(const FString& inString){ Super::FromString(inString); }
#endif