#include "Registry/GameMapRegistry.h"

DEFINE_LOG_CATEGORY(LogGameMapRegistry);

void USMLGameMapRegistry::RegisterGameMap(const FString& PluginName, USMLGameMapData* MapData) {
	if (MapData == NULL) {
		UE_LOG(LogGameMapRegistry, Error, TEXT("Plugin %s attempted to register NULL game map data"), *PluginName);
		return;
	}
	const FSMLGameMapRegistryEntry* ExistingEntry = RegisteredMaps.FindByPredicate([&](const FSMLGameMapRegistryEntry& Entry) {
		return Entry.MapData->MapAsset == MapData->MapAsset;
	});
	if (ExistingEntry != NULL) {
		UE_LOG(LogGameMapRegistry, Error, TEXT("Plugin %s attempted to register Map %s, but it was already registered by Plugin %s"),
			*PluginName, *MapData->MapAsset.ToString(), *ExistingEntry->OwningPluginName);
		return;
	}
	
	FSMLGameMapRegistryEntry NewEntry;
	NewEntry.MapData = MapData;
	NewEntry.OwningPluginName = PluginName;
	RegisteredMaps.Add(NewEntry);
}

void USMLGameMapRegistry::UnregisterGameMap(USMLGameMapData* MapData) {
	const int32 ExistingEntryIndex = RegisteredMaps.IndexOfByPredicate([&](const FSMLGameMapRegistryEntry& Entry) {
		return Entry.MapData->MapAsset == MapData->MapAsset;
	});
	if (ExistingEntryIndex == INDEX_NONE) {
		UE_LOG(LogGameMapRegistry, Warning, TEXT("Attempt to unregister not registered MapData %s"), *MapData->GetPathName());
		return;
	}
	if (RegisteredMaps[ExistingEntryIndex].MapData != MapData) {
		UE_LOG(LogGameMapRegistry, Error, TEXT("Attempt to unregister Map %s using MapData %s, but it was registered by MapData %s"),
			*MapData->MapAsset.ToString(), *MapData->GetPathName(), *RegisteredMaps[ExistingEntryIndex].MapData->GetPathName());
		return;
	}
	RegisteredMaps.RemoveAt(ExistingEntryIndex);
}

TArray<FSMLGameMapRegistryEntry> USMLGameMapRegistry::GetGameMaps() const {
	return RegisteredMaps;
}
