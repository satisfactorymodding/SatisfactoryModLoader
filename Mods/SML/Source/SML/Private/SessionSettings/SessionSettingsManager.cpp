#include "SessionSettings/SessionSettingsManager.h"

#include "FGGameMode.h"
#include "FGOptionsLibrary.h"
#include "SatisfactoryModLoader.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
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

void USessionSettingsManager::GetAllUserSettings(TArray<UFGUserSettingApplyType*>& OutUserSettings) const {
	return SessionSettings.GenerateValueArray(OutUserSettings);
}

UFGUserSettingApplyType* USessionSettingsManager::FindUserSetting(const FString& SettingId) const {
	return SessionSettings.FindRef(SettingId);
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
		UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Could not find session setting '%s'"), *strId);
		return nullptr;
	}
	return *SessionSetting;
}

IFGOptionInterface* USessionSettingsManager::GetPrimaryOptionInterface(UWorld* world) const {
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

bool USessionSettingsManager::IsGlobalManager() const {
	return !IsInMainMenu();
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
