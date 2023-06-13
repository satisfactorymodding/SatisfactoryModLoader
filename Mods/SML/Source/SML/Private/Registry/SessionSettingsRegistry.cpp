#include "Registry/SessionSettingsRegistry.h"

#include "SessionSettings/SessionSettingsManager.h"

DEFINE_LOG_CATEGORY(LogSessionSettingsRegistry);

void USMLSessionSettingsRegistry::RegisterSessionSetting(const FString& PluginName, USMLSessionSetting* SessionSetting) {
	if (SessionSetting == NULL || SessionSetting->UserSetting == NULL) {
		UE_LOG(LogSessionSettingsRegistry, Error, TEXT("Plugin %s attempted to register NULL game map data"), *PluginName);
		return;
	}
	if (SessionSetting->UserSetting->StrId.IsEmpty()) {
		UE_LOG(LogSessionSettingsRegistry, Error, TEXT("Plugin %s attempted to register Settings %s with an empty ID"), *PluginName, *SessionSetting->GetPathName());
		return;
	} 
	const FSMLSessionSettingInfo* ExistingEntry = AllSessionSettings.FindByPredicate([&](const FSMLSessionSettingInfo& Entry) {
		return Entry.SessionSetting == SessionSetting ||
			Entry.SessionSetting->UserSetting->StrId == SessionSetting->UserSetting->StrId;
	});
	if (ExistingEntry != NULL) {
		UE_LOG(LogSessionSettingsRegistry, Error, TEXT("Plugin %s attempted to register SessionSetting %s, but it was already registered by Plugin %s"),
			*PluginName, *SessionSetting->GetPathName(), *ExistingEntry->OwningPluginName);
		return;
	}

	//Add the registry entry for the setting
	FSMLSessionSettingInfo NewEntry;
	NewEntry.SessionSetting = SessionSetting;
	NewEntry.OwningPluginName = PluginName;

	//If we want a CVar created, automatically create it
	//It's not a problem that we create it late at the game lifecycle, because unresolved CVars will still be read from the config and the command line,
	//and stashed using a dummy CVar registration
	if (SessionSetting->UserSetting->CreateCVarFromStrid) {
		const FString SettingId = SessionSetting->UserSetting->StrId;
		const FVariant DefaultValue = SessionSetting->UserSetting->GetDefaultValue();
		
		if (IConsoleManager::Get().FindConsoleVariable(*SettingId) == NULL) {
			IConsoleVariable* NewConsoleVariable;

			if (DefaultValue.GetType() == EVariantTypes::Bool) {
				NewConsoleVariable = IConsoleManager::Get().RegisterConsoleVariable(*SettingId, DefaultValue.GetValue<bool>(),
					*SessionSetting->UserSetting->ToolTip.ToString());
				
			} else if (DefaultValue.GetType() == EVariantTypes::Int32) {
				NewConsoleVariable = IConsoleManager::Get().RegisterConsoleVariable(*SettingId, DefaultValue.GetValue<int32>(),
					*SessionSetting->UserSetting->ToolTip.ToString());

			} else if (DefaultValue.GetType() == EVariantTypes::Float) {
				NewConsoleVariable = IConsoleManager::Get().RegisterConsoleVariable(*SettingId, DefaultValue.GetValue<float>(),
					*SessionSetting->UserSetting->ToolTip.ToString());
			} else {
				const FString StringValue = USMLSessionSettingsManager::ConvertOptionValueToString(DefaultValue);
				NewConsoleVariable = IConsoleManager::Get().RegisterConsoleVariable(*SettingId, StringValue,
					*SessionSetting->UserSetting->ToolTip.ToString());
			}
			NewEntry.ConsoleVariable = NewConsoleVariable;
			UE_LOG(LogSessionSettingsRegistry, Log, TEXT("Registered Session Settings backed Console Variable %s"), *SettingId);
		}
	}
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
	//Unregister console variable if we have one
	if (IConsoleVariable* ConsoleVariable = AllSessionSettings[ExistingEntryIndex].ConsoleVariable) {
		IConsoleManager::Get().UnregisterConsoleObject(ConsoleVariable);
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
