#include "AvailabilityDependencies/FGCalendarOpenedDependency.h"

bool UFGCalendarOpenedDependency::AreDependenciesMet( UObject* worldContext ) const{ return bool(); }
#if WITH_EDITOR
FString UFGCalendarOpenedDependency::ToString() const{ return FString(); }
void UFGCalendarOpenedDependency::FromString( const FString& inString ){ }
#endif
