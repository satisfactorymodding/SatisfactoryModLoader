#include "Registry/SessionSettingsRegistry.h"

#include "SessionSettings/SessionSettingsManager.h"

DEFINE_LOG_CATEGORY(LogSessionSettingsRegistry);

USMLSessionSettingsRegistry::USMLSessionSettingsRegistry()
{
}

void USMLSessionSettingsRegistry::RegisterSessionSetting(const FString& PluginName, USMLSessionSetting* SessionSetting) {
	if (SessionSetting == NULL) {
		UE_LOG(LogSessionSettingsRegistry, Error, TEXT("Plugin %s attempted to register NULL session setting"), *PluginName);
		return;
	}
	if (SessionSetting->StrId.IsEmpty()) {
		UE_LOG(LogSessionSettingsRegistry, Error, TEXT("Plugin %s attempted to register Settings %s with an empty ID"), *PluginName, *SessionSetting->GetPathName());
		return;
	}
	const FSMLSessionSettingInfo* ExistingEntry = AllSessionSettings.FindByPredicate([&](const FSMLSessionSettingInfo& Entry) {
		return Entry.SessionSetting == SessionSetting;
	});
	if (ExistingEntry != NULL) {
		UE_LOG(LogSessionSettingsRegistry, Error, TEXT("Plugin %s attempted to register SessionSetting %s, but it was already registered by Plugin %s"),
			*PluginName, *SessionSetting->GetPathName(), *ExistingEntry->OwningPluginName);
		return;
	}
	const FSMLSessionSettingInfo* ExistingEntrySameId = AllSessionSettings.FindByPredicate([&](const FSMLSessionSettingInfo& Entry) {
		return Entry.SessionSetting != SessionSetting && Entry.SessionSetting->StrId == SessionSetting->StrId;
	});
	checkf(ExistingEntrySameId == NULL, TEXT("Plugin %s attempted to register SessionSetting with ID %s, but a different SessionSetting with the same ID is already registered by Plugin %s"), *PluginName, *SessionSetting->StrId, *ExistingEntrySameId->OwningPluginName);

	//Add the registry entry for the setting
	FSMLSessionSettingInfo NewEntry;
	NewEntry.SessionSetting = SessionSetting;
	NewEntry.OwningPluginName = PluginName;

	AllSessionSettings.Add(NewEntry);
}

void USMLSessionSettingsRegistry::UnregisterSessionSetting(USMLSessionSetting* SessionSetting) {
	const int32 ExistingEntryIndex = AllSessionSettings.IndexOfByPredicate([&](const FSMLSessionSettingInfo& Entry) {
		return Entry.SessionSetting == SessionSetting;
	});
	if (ExistingEntryIndex == INDEX_NONE) {
		UE_LOG(LogSessionSettingsRegistry, Warning, TEXT("Attempt to unregister not registered SessionSetting %s"), *SessionSetting->GetPathName());
		return;
	}
	AllSessionSettings.RemoveAt(ExistingEntryIndex);
}

TArray<FSMLSessionSettingInfo> USMLSessionSettingsRegistry::GetSettingsForMap(const TSoftObjectPtr<UWorld>& MapName) {
	TArray<FSMLSessionSettingInfo> ResultArray;

	for (const FSMLSessionSettingInfo& SettingInfo : AllSessionSettings) {
		const TArray<TSoftObjectPtr<UWorld>>& MapWhitelist = SettingInfo.SessionSetting->MapNameWhitelist;
		if (MapWhitelist.Num() == 0 || MapWhitelist.Contains(MapName)) {
			ResultArray.Add(SettingInfo);
		}
	}
	return ResultArray;
}
