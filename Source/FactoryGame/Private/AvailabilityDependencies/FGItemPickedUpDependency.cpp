// This file has been automatically generated by the Unreal Header Implementation tool

#include "AvailabilityDependencies/FGItemPickedUpDependency.h"

#if WITH_EDITOR
void UFGItemPickedUpDependency::Init(TArray< TSubclassOf<  UFGItemDescriptor > > items, bool requireAllItemsToBePickedUp){ }
FString UFGItemPickedUpDependency::ToString() const{ return FString(); }
void UFGItemPickedUpDependency::FromString(const FString& inString){ }
#endif 
bool UFGItemPickedUpDependency::AreDependenciesMet(UObject* worldContext) const{ return bool(); }
bool UFGItemPickedUpDependency::DoesItemAmountMatchDependency(const FItemAmount& totalAmountPickuped) const{ return bool(); }
void UFGItemPickedUpDependency::GetItems(TArray< TSubclassOf<  UFGItemDescriptor > >& out_items) const{ }
void UFGItemPickedUpDependency::GetItemAmounts(TMap< TSubclassOf<  UFGItemDescriptor >, int32 >& out_items) const{ }
