#include "AvailabilityDependencies/FGItemSinkDependency.h"

UFGItemSinkDependency::UFGItemSinkDependency(){ }
#if WITH_EDITOR
FString UFGItemSinkDependency::ToString() const{ return FString(); }
void UFGItemSinkDependency::FromString( const FString& inString ){ }
#endif
