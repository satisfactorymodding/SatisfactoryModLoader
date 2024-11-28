#include "AvailabilityDependencies/FGCalendarSlotUnlockedDependency.h"

UFGCalendarSlotUnlockedDependency::UFGCalendarSlotUnlockedDependency(){ }
bool UFGCalendarSlotUnlockedDependency::AreDependenciesMet( UObject* worldContext ) const{ return bool(); }
#if WITH_EDITOR
FString UFGCalendarSlotUnlockedDependency::ToString() const{ return FString(); }
void UFGCalendarSlotUnlockedDependency::FromString( const FString& inString ){ }
#endif
