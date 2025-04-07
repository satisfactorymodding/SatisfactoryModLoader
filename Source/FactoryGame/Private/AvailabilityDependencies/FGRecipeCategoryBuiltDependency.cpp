#include "AvailabilityDependencies/FGRecipeCategoryBuiltDependency.h"

#if WITH_EDITOR
FString UFGRecipeCategoryBuiltDependency::ToString() const{ return Super::ToString(); }
void UFGRecipeCategoryBuiltDependency::FromString(const FString& inString){ Super::FromString(inString); }
#endif
