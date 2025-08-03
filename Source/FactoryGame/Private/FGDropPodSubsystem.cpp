#include "FGDropPodSubsystem.h"

void UFGDropPodSubsystem::Initialize(FSubsystemCollectionBase& Collection){ Super::Initialize(Collection); }
bool UFGDropPodSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const{ return Super::DoesSupportWorldType(WorldType); }
UFGDropPodRefundsLootPool* UFGDropPodSubsystem::GetDropPodLootPoolForActorClass(TSubclassOf<AFGCrashSiteBaseActor> ActorClass) const{ return nullptr; }
UFGDropPodRefundsLootPool* UFGDropPodSubsystem::CreateDropPodLootPool(TSubclassOf<AFGCrashSiteBaseActor> ActorClass, TSubclassOf<UFGDropPodRefundsLootPool> LootPoolClass){ return nullptr; }