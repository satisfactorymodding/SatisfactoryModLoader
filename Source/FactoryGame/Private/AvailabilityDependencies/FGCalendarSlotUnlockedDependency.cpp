#include "AvailabilityDependencies/FGCalendarSlotUnlockedDependency.h"

UFGCalendarSlotUnlockedDependency::UFGCalendarSlotUnlockedDependency() : Super() {
	this->mSlot = -1;
	this->mUnlockType = EUnlockDependencyType::Any;
	this->mUnlockedItemClassesRequirement = EItemUnlockRequirement::Any;
}
bool UFGCalendarSlotUnlockedDependency::AreDependenciesMet( UObject* worldContext ) const{ return bool(); }
#if WITH_EDITOR
FString UFGCalendarSlotUnlockedDependency::ToString() const{ return FString(); }
void UFGCalendarSlotUnlockedDependency::FromString( const FString& inString ){ }
#endif
