#include "Settings/FGGameModeSettings.h"

void UFGGameModeSettings::Initialize(){ }
void UFGGameModeSettings::GetAllUserSettings(TArray<TObjectPtr<UFGUserSettingApplyType>>& out_userSettings) const{ }
void UFGGameModeSettings::GetAllUserSettingsMap(TMap<FString, TObjectPtr<UFGUserSettingApplyType>>& out_userSettings) const{ }
UFGUserSettingApplyType* UFGGameModeSettings::FindUserSetting(const FString& settingId) const{ return nullptr; }
bool UFGGameModeSettings::HasAnyUnsavedOptionValueChanges() const{ return IFGAdvancedGameSettingsInterface::HasAnyUnsavedOptionValueChanges(); }
bool UFGGameModeSettings::HasPendingApplyOptionValue(const FString& cvar) const{ return IFGAdvancedGameSettingsInterface::HasPendingApplyOptionValue(cvar); }
void UFGGameModeSettings::RevertUnsavedChanges(){ IFGAdvancedGameSettingsInterface::RevertUnsavedChanges(); }
void UFGGameModeSettings::ApplyChanges(){ IFGAdvancedGameSettingsInterface::ApplyChanges(); }
IFGOptionInterface* UFGGameModeSettings::GetPrimaryOptionInterface(UWorld* world) const{ return nullptr; }
bool UFGGameModeSettings::IsInMainMenu() const{ return IFGAdvancedGameSettingsInterface::IsInMainMenu(); }
bool UFGGameModeSettings::IsAppliedImmediately() const{ return false; }
