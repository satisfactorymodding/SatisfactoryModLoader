#include "SessionSettings/SessionSettingsManager.h"

#include "FGGameMode.h"
#include "FGOptionsLibrary.h"
#include "SatisfactoryModLoader.h"
#include "Misc/Base64.h"
#include "ModLoading/PluginModuleLoader.h"
#include "Registry/SessionSettingsRegistry.h"
#include "Settings/FGUserSettingApplyType.h"

const TCHAR* USessionSettingsManager::SessionSettingsOption = TEXT("SessionSettings");

void USessionSettingsManager::InitializeForMap(const TSoftObjectPtr<UWorld>& World, bool bAttemptPreserveValues) {
	if(!bAttemptPreserveValues)
	{
		SessionSettings.Empty();
	}

	// In the first dummy game world, we will have no game instance subsystems initialized, so do not attempt initialization here
	if ( !GetWorld()->GetGameInstance() )
	{
		return;
	}
	USMLSessionSettingsRegistry* SessionSettingsRegistry = GetWorld()->GetGameInstance()->GetSubsystem<USMLSessionSettingsRegistry>();
	if ( !SessionSettingsRegistry )
	{
		return;
	}
	
	const TArray<FSMLSessionSettingInfo> SessionSettingsForMap = SessionSettingsRegistry->GetSettingsForMap(World);

	TArray<FString> OptionNamesToRemove;
	SessionSettings.GetKeys(OptionNamesToRemove);
	
	//Populate settings with new values
	for (const FSMLSessionSettingInfo& SettingInfo : SessionSettingsForMap) {
		const FString SettingId = SettingInfo.SessionSetting->StrId;
		if(!SessionSettings.Contains(SettingId)) {
			SessionSettings.Add(SettingId, UFGUserSettingApplyType::GetUserSettingApplyType(this, SettingInfo.SessionSetting));
		}
		if(!bAttemptPreserveValues) {
			if (const auto setting = SessionSettings[SettingId]) {
				setting->ResetToDefaultValue();
			}
			else {
				UE_LOG(LogSatisfactoryModLoader, Fatal, TEXT("Failed to add SessionSetting with StrId %s, it probably has an invalid Apply Type. Continuing would lead to a crash in base-game code."), *SettingId);
			}
		}
		OptionNamesToRemove.Remove(SettingId);
	}

	for (const FString& OptionNameToRemove : OptionNamesToRemove) {
		SessionSettings.Remove(OptionNameToRemove);
	}
}

void USessionSettingsManager::Initialize(FSubsystemCollectionBase& Collection)
{
	InitializeForMap(GetWorld(), false);
	FGameModeEvents::GameModeInitializedEvent.AddUObject(this, &USessionSettingsManager::OnGameModeInitialized);
}

bool USessionSettingsManager::ShouldCreateSubsystem( UObject* Outer ) const
{
	UWorld* WorldOuter = CastChecked<UWorld>(Outer);
	return FPluginModuleLoader::ShouldLoadModulesForWorld(WorldOuter);
}

void USessionSettingsManager::OnGameModeInitialized(AGameModeBase* GameModeBase) {
	if(!IsInMainMenu()) {
		// This will only run on the server. Syncing the settings to the clients on join is handled in ASessionSettingsSubsystem
		// If we're in a session, we can load the setting values
		const FString SessionSettingsString = UGameplayStatics::ParseOption(GameModeBase->OptionsString, SessionSettingsOption);
		if (!SessionSettingsString.IsEmpty()) {
			DeserializeSettingsFromString(SessionSettingsString);
		}
		// Watch for option updates in order to update them in the options string of the game mode
		SubscribeToAllOptionUpdates(FOnOptionUpdated::CreateUObject(this, &USessionSettingsManager::OnOptionUpdated));
	}
}

bool USessionSettingsManager::IsInMainMenu() const {
	return FPluginModuleLoader::IsMainMenuWorld(GetWorld());
}

void USessionSettingsManager::OnOptionUpdated(FString String, FVariant Value) const {
	if(const AFGGameMode* GameMode = GetWorld()->GetAuthGameMode<AFGGameMode>()) {
		FString& Options = const_cast<FString&>(GameMode->GetCurrentOptions());
		if(UGameplayStatics::HasOption(Options, SessionSettingsOption)) {
			const FString CurrentValue = UGameplayStatics::ParseOption(Options, SessionSettingsOption);
			Options.ReplaceInline(*FString::Printf(TEXT("?%s=%s"), SessionSettingsOption, *CurrentValue), TEXT(""));
		}
		Options.Append(*FString::Printf(TEXT("?%s=%s"), SessionSettingsOption, *SerializeSettingsToString()));
	}
}

FString USessionSettingsManager::SerializeSettingsToString() const {
	TArray<FString> OptionStrings;
	
	for (const TPair<FString, UFGUserSettingApplyType*>& Pair : SessionSettings) {
		FString Name = Pair.Key;
		FVariant Value = Pair.Value->GetPendingValue();
		if (Value.IsEmpty())
			Value = Pair.Value->GetAppliedValue();

		OptionStrings.Add(Pair.Key + TEXT("=") + VariantToString(Value));
	}
	return FString::Join(OptionStrings, TEXT(","));
}

void USessionSettingsManager::DeserializeSettingsFromString(const FString& SerializedString) {
	TArray<FString> OptionStrings;
	SerializedString.ParseIntoArray(OptionStrings, TEXT(","));
	for (const FString& OptionString : OptionStrings) {
		int32 EqualIdx;
		if(!OptionString.FindChar(TEXT('='), EqualIdx)) {
			UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Invalid option string: %s"), *OptionString);
			continue;
		}

		FString Name = OptionString.Left(EqualIdx);
		FVariant Value = StringToVariant(OptionString.RightChop(EqualIdx + 1));
		if(!Value.IsEmpty())
			ForceSetOptionValue(Name, Value, this);
	}
}

FString USessionSettingsManager::VariantToString(FVariant& Variant) {
	TArray<uint8> Bytes;
	FMemoryWriter MemoryWriter(Bytes);
	MemoryWriter << Variant;
	return FBase64::Encode(Bytes);
}

FVariant USessionSettingsManager::StringToVariant(const FString& String) {
	FVariant Variant;

	TArray<uint8> Bytes;
	FBase64::Decode(String, Bytes);
	FMemoryReader MemoryReader(Bytes);
	MemoryReader << Variant;

	return Variant;
}

UFGUserSettingApplyType* USessionSettingsManager::FindSessionSetting(const FString& strId) const {
	UFGUserSettingApplyType* const* SessionSetting = SessionSettings.Find(strId);
	if (!SessionSetting) {
		return nullptr;
	}
	return *SessionSetting;
}

FVariant USessionSettingsManager::GetOptionValue(const FString& strId) const {
	return GetOptionValue(strId, FVariant());
}

FVariant USessionSettingsManager::GetOptionValue(const FString& strId, const FVariant& defaultValue) const {
	const UFGUserSettingApplyType* SessionSetting = FindSessionSetting(strId);
	if (!SessionSetting) {
		return defaultValue;
	}
	FVariant AppliedValue = SessionSetting->GetAppliedValue();
	if (AppliedValue.IsEmpty()) {
		return defaultValue;
	}
	return AppliedValue;
}

FVariant USessionSettingsManager::GetOptionDisplayValue(const FString& strId) const {
	return GetOptionDisplayValue(strId, FVariant());
}

FVariant USessionSettingsManager::GetOptionDisplayValue(const FString& strId, const FVariant& defaultValue) const {
	const UFGUserSettingApplyType* SessionSetting = FindSessionSetting(strId);
	if (!SessionSetting) {
		return defaultValue;
	}
	return SessionSetting->GetDisplayValue();
}

void USessionSettingsManager::SetOptionValue(const FString& strId, const FVariant& value) {
	if (UFGUserSettingApplyType* SessionSetting = FindSessionSetting(strId)) {
		SessionSetting->SetValue(value);
	}
}


void USessionSettingsManager::ForceSetOptionValue(const FString& strId, const FVariant& variant, const UObject* instigator) {
	if (UFGUserSettingApplyType* SessionSetting = FindSessionSetting(strId)) {
		SessionSetting->ForceSetValue(variant);
	}
}

void USessionSettingsManager::SubscribeToOptionUpdate(const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate) {
	if (UFGUserSettingApplyType* SessionSetting = FindSessionSetting(strId)) {
		SessionSetting->AddSubscriber(onOptionUpdatedDelegate);
	}
}

void USessionSettingsManager::UnsubscribeToOptionUpdate(const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate) {
	if (UFGUserSettingApplyType* SessionSetting = FindSessionSetting(strId)) {
		SessionSetting->RemoveSubscriber(onOptionUpdatedDelegate);
	}
}

bool USessionSettingsManager::IsDefaultValueApplied(const FString& strId) const {
	if (const UFGUserSettingApplyType* SessionSetting = FindSessionSetting(strId)) {
		return SessionSetting->IsDefaultValueApplied();
	}
	return false;
}

void USessionSettingsManager::ApplyChanges() {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Option : SessionSettings) {
		Option.Value->OnApply();
	}
}

void USessionSettingsManager::ResetAllSettingsToDefault() {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Option : SessionSettings) {
		Option.Value->ResetToDefaultValue();
	}
}

void USessionSettingsManager::ResetAllSettingsInCategory(TSubclassOf<UFGUserSettingCategory> category, TSubclassOf<UFGUserSettingCategory> subCategory) {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Option : SessionSettings) {
		if(Option.Value->GetUserSetting()->CategoryClass == category && Option.Value->GetUserSetting()->SubCategoryClass == subCategory) {
			Option.Value->ResetToDefaultValue();
		}
	}
}

bool USessionSettingsManager::GetBoolOptionValue(const FString& cvar) const {
	return GetOptionValue(cvar, FVariant(false)).GetValue<bool>();
}

bool USessionSettingsManager::GetBoolUIDisplayValue(const FString& cvar) const {
	return GetOptionDisplayValue(cvar, FVariant(false)).GetValue<bool>();
}

void USessionSettingsManager::SetBoolOptionValue(const FString& cvar, bool value) {
	SetOptionValue(cvar, FVariant(value));
}

int32 USessionSettingsManager::GetIntOptionValue(const FString& cvar) const {
	return GetOptionValue(cvar, FVariant(0)).GetValue<int32>();
}

int32 USessionSettingsManager::GetIntUIDisplayValue(const FString& cvar) const {
	return GetOptionDisplayValue(cvar, FVariant(0)).GetValue<int32>();
}

void USessionSettingsManager::SetIntOptionValue(const FString& cvar, int32 newValue) {
	SetOptionValue(cvar, FVariant(newValue));
}

float USessionSettingsManager::GetFloatOptionValue(const FString& cvar) const {
	return GetOptionValue(cvar, FVariant(0)).GetValue<float>();
}

float USessionSettingsManager::GetFloatUIDisplayValue(const FString& cvar) const {
	return GetOptionDisplayValue(cvar, FVariant(0)).GetValue<float>();
}

void USessionSettingsManager::SetFloatOptionValue(const FString& cvar, float newValue) {
	SetOptionValue(cvar, FVariant(newValue));
}

bool USessionSettingsManager::HasAnyUnsavedOptionValueChanges() const {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Options : SessionSettings) {
		if (Options.Value->HasPendingChanges())
			return true;
	}
	return false;
}

bool USessionSettingsManager::HasPendingApplyOptionValue(const FString& cvar) const {
	const UFGUserSettingApplyType* SessionSetting = FindSessionSetting(cvar);
	if (!SessionSetting) {
		return false;
	}
	return SessionSetting->HasPendingChanges();
}

bool USessionSettingsManager::HasAnyPendingRestartOptionValue(const FString& cvar) const {
	const UFGUserSettingApplyType* SessionSetting = FindSessionSetting(cvar);
	if (!SessionSetting) {
		return false;
	}
	return SessionSetting->HasGameRestartRequiredChanges() || SessionSetting->HasSessionRestartRequiredChanges();
}

bool USessionSettingsManager::GetRequireSessionRestart() const {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Options : SessionSettings) {
		if (Options.Value->HasSessionRestartRequiredChanges())
			return true;
	}
	return false;
}

bool USessionSettingsManager::GetRequireGameRestart() const {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Options : SessionSettings) {
		if (Options.Value->HasGameRestartRequiredChanges())
			return true;
	}
	return false;
}

void USessionSettingsManager::SubscribeToDynamicOptionUpdate(const FString& cvar, const FOptionUpdated& optionUpdatedDelegate) {
	if (UFGUserSettingApplyType* SessionSetting = FindSessionSetting(cvar)) {
		SessionSetting->AddSubscriber(optionUpdatedDelegate);
	}
}

void USessionSettingsManager::UnsubscribeToDynamicOptionUpdate(const FString& cvar, const FOptionUpdated& optionUpdatedDelegate) {
	if (UFGUserSettingApplyType* SessionSetting = FindSessionSetting(cvar)) {
		SessionSetting->RemoveSubscriber(optionUpdatedDelegate);
	}
}

void USessionSettingsManager::UnsubscribeToAllDynamicOptionUpdate(UObject* boundObject) {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Options : SessionSettings) {
		Options.Value->RemoveObjectAsSubscriber(boundObject);
	}
}

TArray<FUserSettingCategoryMapping> USessionSettingsManager::GetCategorizedSettingWidgets( UObject* worldContext, UUserWidget* owningWidget )
{
	return UFGOptionsLibrary::GetCategorizedUserSettingsWidgets( worldContext, owningWidget, this, SessionSettings );
}

IFGOptionInterface* USessionSettingsManager::GetActiveOptionInterface() const
{
	// Only resort to the world context iteration if we are the CDO, otherwise we are the active manager for ourselves
	if ( HasAnyFlags( RF_ClassDefaultObject ) )
	{
		for ( const FWorldContext& worldContext : GEngine->GetWorldContexts() )
		{
			if( worldContext.World() && ( worldContext.WorldType == EWorldType::Game || worldContext.WorldType == EWorldType::PIE ) )
			{
				return worldContext.World()->GetSubsystem<USessionSettingsManager>();
			}
		}
		return nullptr;
	}
	return const_cast<USessionSettingsManager*>( this );
}

void USessionSettingsManager::SubscribeToAllOptionUpdates(const FOnOptionUpdated& onOptionUpdatedDelegate) {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Options : SessionSettings) {
		Options.Value->AddSubscriber(onOptionUpdatedDelegate);
	}
}

void USessionSettingsManager::UnsubscribeToAllOptionUpdates(const FOnOptionUpdated& onOptionUpdatedDelegate) {
	for (const TTuple<FString, UFGUserSettingApplyType*>& Options : SessionSettings) {
		Options.Value->RemoveSubscriber(onOptionUpdatedDelegate);
	}
}

