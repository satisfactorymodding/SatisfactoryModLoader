#include "AvailabilityDependencies/FGWeatherReactionSeenDependency.h"

bool UFGWeatherReactionSeenDependency::DoesWeatherReactionMatch(const TSubclassOf<class AFGWeatherReaction>& weatherReactionClass) const{ return false; }
#if WITH_EDITOR
FString UFGWeatherReactionSeenDependency::ToString() const{ return Super::ToString(); }
void UFGWeatherReactionSeenDependency::FromString(const FString& inString){ Super::FromString(inString); }
#endif
