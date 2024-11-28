#include "FGGiftRainSpawner.h"

AFGGiftRainSpawner::AFGGiftRainSpawner(){ }
void AFGGiftRainSpawner::BeginPlay(){ Super::BeginPlay(); }
bool AFGGiftRainSpawner::ShouldAutomaticallySpawnGifts() const{ return bool(); }
void AFGGiftRainSpawner::SetAutomaticGiftSpawningEnabled(bool enabled){ }
void AFGGiftRainSpawner::SetGiftSpawnIntervalMinMax(float intervalSecondsMin, float intervalSecondsMax){ }
void AFGGiftRainSpawner::SetGiftSpawnInterval(const FFloatInterval& intervalSeconds){ }
void AFGGiftRainSpawner::SetAutomaticGiftSpawnLimit(int32 newLimit){ }
void AFGGiftRainSpawner::SetGiftBundleClassBlockedFromSpawning(TSubclassOf<class AFGFallingGiftBundle> giftBundleClass, bool blocked){ }
void AFGGiftRainSpawner::OnGiftBundleSpawned_Native(class AFGFallingGiftBundle* giftBundle){ }
void AFGGiftRainSpawner::GetRelevantPlayerCharacters(TArray<class AFGCharacterPlayer*>& out_playerCharacters) const{ }
void AFGGiftRainSpawner::OnGiftBundleActorDestroyed(AActor* giftBundleActor){ }
void AFGGiftRainSpawner::OnGiftSpawnerTimerFinished(){ }
void AFGGiftRainSpawner::UpdateGiftSpawnerTimer(){ }
int32 AFGGiftRainSpawner::TryDestroyOldestGiftBundles(int32 numToDestroy) const{ return int32(); }
TSubclassOf<class AFGFallingGiftBundle> AFGGiftRainSpawner::GetGiftBundleClassToSpawn_Implementation(){ return TSubclassOf<class AFGFallingGiftBundle>(); }
class AFGFallingGiftBundle* AFGGiftRainSpawner::SpawnRandomGiftAroundAnyPlayer(float spawnDistance){ return nullptr; }
class AFGFallingGiftBundle* AFGGiftRainSpawner::SpawnRandomGiftAroundPlayer(class AFGCharacterPlayer* player, float spawnDistance){ return nullptr; }
class AFGFallingGiftBundle* AFGGiftRainSpawner::SpawnRandomGiftAtLocation(const FVector& location){ return nullptr; }
