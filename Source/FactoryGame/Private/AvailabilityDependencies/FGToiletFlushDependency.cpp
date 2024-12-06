#include "AvailabilityDependencies/FGToiletFlushDependency.h"

UFGToiletFlushDependency::UFGToiletFlushDependency(){ }
#if WITH_EDITOR
FString UFGToiletFlushDependency::ToString() const{ return FString(); }
void UFGToiletFlushDependency::FromString( const FString& inString ){ }
#endif
