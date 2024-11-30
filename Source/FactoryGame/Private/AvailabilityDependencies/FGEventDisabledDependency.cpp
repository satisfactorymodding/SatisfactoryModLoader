#include "AvailabilityDependencies/FGEventDisabledDependency.h"

bool UFGEventDisabledDependency::AreDependenciesMet( UObject* worldContext ) const{ return bool(); }
#if WITH_EDITOR
FString UFGEventDisabledDependency::ToString() const{ return FString(); }
void UFGEventDisabledDependency::FromString( const FString& inString ){ }
#endif
