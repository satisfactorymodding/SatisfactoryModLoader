#include "AvailabilityDependencies/FGTakeDamageDependency.h"

#if WITH_EDITOR
FString UFGTakeDamageDependency::ToString() const{ return Super::ToString(); }
void UFGTakeDamageDependency::FromString(const FString& inString){ Super::FromString(inString); }
#endif
