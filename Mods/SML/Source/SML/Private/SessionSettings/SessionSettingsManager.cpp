#include "SessionSettings/SessionSettingsManager.h"

#include "FGGameMode.h"
#include "FGOptionsLibrary.h"
#include "FGSaveSession.h"
#include "Registry/SessionSettingsRegistry.h"

void USMLSessionSettingsManager::InitializeForMap(const TSoftObjectPtr<UWorld>& InMapName, bool bAttemptPreserveValues) {
	TMap<FString, FVariant> PreviousOptionValues;
	if (bAttemptPreserveValues) {
		PreviousOptionValues = CurrentOptionValues;
	}

	//=====================================
	//Completely reset the state
	OptionsByName.Empty();
	PendingOptionValues.Empty();
	CurrentOptionValues.Empty();
	ActiveOptionValues.Empty();
	OptionValueCallbacks.Empty();
	DynamicOptionValueCallbacks.Empty();
	//=====================================
	
	this->MapName = InMapName;

	USMLSessionSettingsRegistry* SessionSettingsRegistry = GEngine->GetEngineSubsystem<USMLSessionSettingsRegistry>();
	const TArray<FSMLSessionSettingInfo> SessionSettings = SessionSettingsRegistry->GetSettingsForMap(InMapName);

	//Populate settings with new values
	for (const FSMLSessionSettingInfo& SettingInfo : SessionSettings) {
		const FString SettingId = SettingInfo.SessionSetting->UserSetting->StrId;
		this->OptionsByName.Add(SettingId, SettingInfo.SessionSetting);

		FVariant CurrentOptionValue = SettingInfo.SessionSetting->UserSetting->GetDefaultValue();
		if (const FVariant* PreviousValue = PreviousOptionValues.Find(SettingId)) {
			CurrentOptionValue = *PreviousValue;
		}
		this->CurrentOptionValues.Add(SettingId, CurrentOptionValue);
		this->ActiveOptionValues.Add(SettingId, CurrentOptionValue);
	}
}

void USMLSessionSettingsManager::SetSettingsApplyPolicy(ESessionSettingsApplyPolicy InApplyPolicy) {
	SettingsApplyPolicy = InApplyPolicy;
}

TArray<UFGDynamicOptionsRow*> USMLSessionSettingsManager::GetSessionSettingsOptionWidgets(UUserWidget* OwningWidget) {
	TArray<UFGDynamicOptionsRow*> ResultArray;
	for (const USMLSessionSetting* SessionSetting : GetAllSessionSettings()) {
		if (CanEditOptionValue(SessionSetting)) {
			TScriptInterface<IFGOptionInterface> ScriptInterface;
			ScriptInterface.SetObject(this);
			ScriptInterface.SetInterface(static_cast<IFGOptionInterface*>(this));
			
			ResultArray.Add(UFGOptionsLibrary::SetupUserSetting(OwningWidget, SessionSetting->UserSetting, ScriptInterface));
		}
	}
	return ResultArray;
}

FString USMLSessionSettingsManager::ToMapOptionsActive() const {
	FURL ResultOptions(NULL, TEXT(""), TRAVEL_Absolute);
	ResultOptions.Map = TEXT("");
	PopulateURLOptions(true, ResultOptions);
	return ResultOptions.ToString();
}

void USMLSessionSettingsManager::PopulateURLOption(const FString& strId, bool bActiveOption, FURL& OutURL) const {
	if (const USMLSessionSetting* SessionSetting = FindSessionSetting(strId)) {
		const FString SessionSettingId = SessionSetting->UserSetting->StrId;
		
		//Gather the current value
		FVariant CurrentOptionValue;
		if (bActiveOption) {
			if (const FVariant* ActiveOptionValue = ActiveOptionValues.Find(SessionSettingId)) {
				CurrentOptionValue = *ActiveOptionValue;
			}
		} else {
			if (const FVariant* InCurrentOptionValue = CurrentOptionValues.Find(SessionSettingId)) {
				CurrentOptionValue = *InCurrentOptionValue;
			}
		}

		const FVariant DefaultValue = SessionSetting->UserSetting->GetDefaultValue();
		const bool bIsBoolOptionWithDefaultFalseValue = DefaultValue.GetType() == EVariantTypes::Bool && !DefaultValue.GetValue<bool>();

		//Only add option if it's value is different from the default
		if (CurrentOptionValue != DefaultValue) {
			//If it's default value is false and it is different from false, just add it as a flag
			if (bIsBoolOptionWithDefaultFalseValue) {
				OutURL.AddOption(*SessionSettingId);
			} else {
				//Otherwise add it as a normal option value string
				const FString OptionValueString = ConvertOptionValueToString(CurrentOptionValue);
				const FString ResultString = FString::Printf(TEXT("%s=%s"), *SessionSettingId, *OptionValueString);
				OutURL.AddOption(*ResultString);
			}
		} else {
			//Otherwise remove it from the URL options
			OutURL.RemoveOption(*SessionSettingId);
		}
	}
}

void USMLSessionSettingsManager::LoadURLOption(const FString& strId, const FURL& URL, bool bActiveOption, bool bCurrentOption) {
	if (const USMLSessionSetting* SessionSetting = FindSessionSetting(strId)) {

		const FString SessionSettingId = SessionSetting->UserSetting->StrId;
		const TCHAR* OptionValue = URL.GetOption(*SessionSettingId, NULL);
		const FVariant DefaultValue = SessionSetting->UserSetting->GetDefaultValue();

		const bool bIsBoolOptionWithDefaultFalseValue = DefaultValue.GetType() == EVariantTypes::Bool &&
			!DefaultValue.GetValue<bool>();
		FVariant ResultOptionValue;
		
		//If there is no value, or it's empty, we use the default one
		if (OptionValue == NULL || *OptionValue == '\0') {
			//Boolean options with default value of false have a simplified representation -
			//if the value is NULL, then they are false, and if it is an empty string, it is true
			//If it's something else, treat it normally
			if (bIsBoolOptionWithDefaultFalseValue) {
				ResultOptionValue = FVariant(!!OptionValue);
			} else {
				ResultOptionValue = DefaultValue;
			}
		} else {
			//Attempt to parse the option value
			//Strip first character because it would be =
			//We can do it safely without worrying about accidentally stripping \0 because it is handled in if cases above
			ResultOptionValue = CreateOptionValueFromString(DefaultValue, OptionValue + 1);
		}

		//Update cached option values inside of the maps
		PendingOptionValues.Remove(SessionSettingId);
		if (bActiveOption) {
			ActiveOptionValues.Add(SessionSettingId, ResultOptionValue);
		}
		if (bCurrentOption) {
			CurrentOptionValues.Add(SessionSettingId, ResultOptionValue);
		}
	}
}

void USMLSessionSettingsManager::LoadOptionValuesFromURLOptions(const FURL& URL, bool bPopulateCurrentOptions, bool bPopulateActiveOptions) {
	//Iterate all settings that we have
	for (const TPair<FString, USMLSessionSetting*>& Pair : OptionsByName) {
		LoadURLOption(Pair.Key, URL, bPopulateActiveOptions, bPopulateCurrentOptions);
	}
}

void USMLSessionSettingsManager::PopulateURLOptions(bool bActiveOptions, FURL& OutURL) const {
	//Iterate all settings that we have
	for (const TPair<FString, USMLSessionSetting*>& Pair : OptionsByName) {
		PopulateURLOption(Pair.Key, bActiveOptions, OutURL);
	}
}

FVariant USMLSessionSettingsManager::CreateOptionValueFromString(const FVariant& DefaultValue, const FString& InValue) {
	switch (DefaultValue.GetType()) {
	case EVariantTypes::Bool:
		if (InValue == TEXT("true") || InValue == TEXT("false")) {
			return InValue == TEXT("true");
		}
		return DefaultValue;
	case EVariantTypes::Float:
		if (FCString::IsNumeric(*InValue)) {
			return FCString::Atof(*InValue);
		}
		return DefaultValue;
	case EVariantTypes::Int32:
		if (FCString::IsNumeric(*InValue)) {
			return FCString::Atoi(*InValue);
		}
		return DefaultValue;
	case EVariantTypes::String:
		return InValue;
	default:
		return DefaultValue;
	}
}

FString USMLSessionSettingsManager::ConvertOptionValueToString(const FVariant& Variant) {
	switch (Variant.GetType()) {
	case EVariantTypes::Bool:
		return Variant.GetValue<bool>() ? TEXT("true") : TEXT("false");
	case EVariantTypes::Float:
		return FString::Printf(TEXT("%.2f"), Variant.GetValue<float>());
	case EVariantTypes::Int32:
		return FString::Printf(TEXT("%d"), Variant.GetValue<int32>());
	case EVariantTypes::String:
		return Variant.GetValue<FString>();
	default:
		return TEXT("");
	}
}

TArray<USMLSessionSetting*> USMLSessionSettingsManager::GetAllSessionSettings() const {
	TArray<USMLSessionSetting*> OutResult;
	OptionsByName.GenerateValueArray(OutResult);
	return OutResult;
}

USMLSessionSetting* USMLSessionSettingsManager::FindSessionSetting(const FString& strId) const {
	USMLSessionSetting* const* SessionSetting = OptionsByName.Find(strId);
	return SessionSetting ? *SessionSetting : NULL;
}

FVariant USMLSessionSettingsManager::GetCurrentOptionValue(const FString& strId) const {
	const USMLSessionSetting* SessionSetting = FindSessionSetting(strId);
	if (const FVariant* CurrentValue = CurrentOptionValues.Find(strId)) {
		return *CurrentValue;
	}
	if (SessionSetting) {
		return SessionSetting->UserSetting->GetDefaultValue();
	}
	return FVariant();
}

FVariant USMLSessionSettingsManager::GetActiveOptionValue(const FString& strId) const {
	const USMLSessionSetting* SessionSetting = FindSessionSetting(strId);
	if (const FVariant* CurrentValue = ActiveOptionValues.Find(strId)) {
		return *CurrentValue;
	}
	if (SessionSetting) {
		return SessionSetting->UserSetting->GetDefaultValue();
	}
	return FVariant();
}

FVariant USMLSessionSettingsManager::GetUIOptionValue(const FString& strId) const {
	//Attempt to retrieve pending value first
	const FVariant* PendingVariant = PendingOptionValues.Find(strId);
	if (PendingVariant != NULL) {
		return *PendingVariant;
	}
	//Fallback to active option value
	return GetCurrentOptionValue(strId);
}

FVariant USMLSessionSettingsManager::GetOptionValue(const FString& strId) const {
	return GetCurrentOptionValue(strId);
}

void USMLSessionSettingsManager::SetUIOptionValue(const FString& strId, const FVariant& variant) {
	if (const USMLSessionSetting* UserSetting = FindSessionSetting(strId)) {
		const EOptionApplyType OptionApplyType = UserSetting->UserSetting->ApplyType;

		//If this option updates instantly, just set it's value directly
		if (OptionApplyType == EOptionApplyType::OAT_UpdateInstantly || SettingsApplyPolicy == ESessionSettingsApplyPolicy::Always) {
			SetCurrentOptionValue(strId, variant);
		} else {
			//Otherwise set a pending option value now
			SetPendingOptionValue(strId, variant);
		}
	}
}

bool USMLSessionSettingsManager::CanApplyActiveOptionValue(const USMLSessionSetting* SessionSetting) const {
	//We can apply active options immediately if they do not require a game or a session restart
	if (SettingsApplyPolicy == ESessionSettingsApplyPolicy::ApplyWhenPossible) {
		const EOptionApplyType OptionApplyType = SessionSetting->UserSetting->ApplyType;

		return OptionApplyType != EOptionApplyType::OAT_RequireSessionRestart &&
				OptionApplyType != EOptionApplyType::OAT_RequireGameRestart;
	}
	//Otherwise it's either Always or Never
	return SettingsApplyPolicy == ESessionSettingsApplyPolicy::Always;
}

bool USMLSessionSettingsManager::CanEditOptionValue(const USMLSessionSetting* SessionSetting) const {
	//If we cannot edit the setting after session creation, we can only edit it if we are on always change policy
	if (!SessionSetting->bCanEditAfterSessionCreation) {
		return SettingsApplyPolicy == ESessionSettingsApplyPolicy::Always;
	}
	//Otherwise we can change the setting normally
	return true;
}

void USMLSessionSettingsManager::SetCurrentOptionValue(const FString& strId, const FVariant& variant) {
	if (USMLSessionSetting* UserSetting = FindSessionSetting(strId)) {
		const FVariant* CurrentOptionValue = CurrentOptionValues.Find(strId);

		if (CurrentOptionValue == NULL || *CurrentOptionValue != variant) {
			PendingOptionValues.Remove(strId);
			
			CurrentOptionValues.Add(strId, variant);
			OnCurrentOptionUpdated.Broadcast(this, UserSetting);
			
			//If this option does not require a game or session restart, update it immediately
			if (CanApplyActiveOptionValue(UserSetting)) {
				SetActiveOptionValue(strId, variant);
			}
			BroadcastOptionValueChanged(strId);
		}
	}
}

void USMLSessionSettingsManager::SetActiveOptionValue(const FString& strId, const FVariant& variant) {
	if (USMLSessionSetting* UserSetting = FindSessionSetting(strId)) {
		const FVariant* ActiveOptionValue = ActiveOptionValues.Find(strId);

		if (ActiveOptionValue == NULL || *ActiveOptionValue != variant) {
			ActiveOptionValues.Add(strId, variant);
			OnActiveOptionUpdated.Broadcast(this, UserSetting);
		}
	}
}

void USMLSessionSettingsManager::SetPendingOptionValue(const FString& strId, const FVariant& variant) {
	if (USMLSessionSetting* UserSetting = FindSessionSetting(strId)) {
		const FVariant* CurrentOptionValue = PendingOptionValues.Find(strId);

		if (CurrentOptionValue == NULL || *CurrentOptionValue != variant) {
			PendingOptionValues.Add(strId, variant);
			OnPendingOptionUpdated.Broadcast(this, UserSetting);
		}
	}
}

void USMLSessionSettingsManager::ForceSetOptionValue(const FString& strId, const FVariant& variant, const UObject* instigator) {
	SetCurrentOptionValue(strId, variant);
}

void USMLSessionSettingsManager::ResetAllSettingsToDefault() {
	//Iterate all current options and set their default values
	for (const TPair<FString, USMLSessionSetting*>& Pair : OptionsByName) {
		SetCurrentOptionValue(Pair.Key, Pair.Value->UserSetting->GetDefaultValue());
	}
}

bool USMLSessionSettingsManager::GetBoolOptionValue(const FString& cvar) const {
	return GetOptionValueOrDefault<bool>(cvar);
}

bool USMLSessionSettingsManager::GetBoolUIDisplayValue(const FString& cvar) const {
	return GetUIOptionValueOrDefault<bool>(cvar);
}

void USMLSessionSettingsManager::SetBoolOptionValue(const FString& cvar, bool value) {
	SetUIOptionValue(cvar, FVariant(value));
}

int32 USMLSessionSettingsManager::GetIntOptionValue(const FString& cvar) const {
	return GetOptionValueOrDefault<int32>(cvar);
}

int32 USMLSessionSettingsManager::GetIntUIDisplayValue(const FString& cvar) const {
	return GetUIOptionValueOrDefault<int32>(cvar);
}

void USMLSessionSettingsManager::SetIntOptionValue(const FString& cvar, int32 newValue) {
	SetUIOptionValue(cvar, FVariant(newValue));
}

float USMLSessionSettingsManager::GetFloatOptionValue(const FString& cvar) const {
	return GetOptionValueOrDefault<float>(cvar);
}

float USMLSessionSettingsManager::GetFloatUIDisplayValue(const FString& cvar) const {
	return GetUIOptionValueOrDefault<float>(cvar);
}

void USMLSessionSettingsManager::SetFloatOptionValue(const FString& cvar, float newValue) {
	SetUIOptionValue(cvar, FVariant(newValue));
}

void USMLSessionSettingsManager::ApplyChanges() {
	//Apply any pending option values that we might have
	for (const TPair<FString, FVariant>& PendingOptionValue : PendingOptionValues) {
		SetCurrentOptionValue(PendingOptionValue.Key, PendingOptionValue.Value);
	}
}

bool USMLSessionSettingsManager::HasAnyUnsavedOptionValueChanges() const {
	return PendingOptionValues.Num() > 0;
}

bool USMLSessionSettingsManager::HasPendingApplyOptionValue(const FString& cvar) const {
	return PendingOptionValues.Contains(cvar);
}

bool USMLSessionSettingsManager::HasPendingSessionRestartOptionValue(const FString& strId) const {
	//We need to restart session if an active session value does not match the current one
	const FVariant* ActiveOptionValue = ActiveOptionValues.Find(strId);
	const FVariant* CurrentOptionValue = CurrentOptionValues.Find(strId);

	if (ActiveOptionValue && CurrentOptionValue) {
		return *ActiveOptionValue != *CurrentOptionValue;
	}
	return false;
}

bool USMLSessionSettingsManager::HasPendingAnyRestartOptionValue(const FString& cvar) const {
	return HasPendingSessionRestartOptionValue(cvar);
}

bool USMLSessionSettingsManager::GetRequireSessionRestart() const {
	for (const TPair<FString, FVariant>& Pair : ActiveOptionValues) {
		if (HasPendingSessionRestartOptionValue(Pair.Key)) {
			return true;
		}
	}
	return false;
}

//Session level settings never require a game restart
bool USMLSessionSettingsManager::GetRequireGameRestart() const {
	return false;
}

void USMLSessionSettingsManager::BroadcastOptionValueChanged(const FString& strId) {
	const FVariant CurrentOptionValue = GetOptionValue(strId);
	
	if (const TArray<FOnOptionUpdated>* Callbacks = OptionValueCallbacks.Find(strId)) {
		for (const FOnOptionUpdated& Callback : *Callbacks) {
			Callback.ExecuteIfBound(strId, CurrentOptionValue);
		}
	}
	if (const TArray<FOptionUpdated>* Callbacks = DynamicOptionValueCallbacks.Find(strId)) {
		for (const FOptionUpdated& Callback : *Callbacks) {
			Callback.ExecuteIfBound(strId);
		}
	}
}

void USMLSessionSettingsManager::SubscribeToOptionUpdate(const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate) {
	TArray<FOnOptionUpdated>& Callbacks = OptionValueCallbacks.FindOrAdd(strId);
	Callbacks.Add(onOptionUpdatedDelegate);
}

void USMLSessionSettingsManager::UnsubscribeToOptionUpdate(const FString& strId, const FOnOptionUpdated& onOptionUpdatedDelegate) {
	TArray<FOnOptionUpdated>* Callbacks = OptionValueCallbacks.Find(strId);
	if (Callbacks != NULL) {
		Callbacks->RemoveAll([&](const FOnOptionUpdated& Delegate) {
			return Delegate.GetHandle() == onOptionUpdatedDelegate.GetHandle();
		});
	}
}

void USMLSessionSettingsManager::SubscribeToDynamicOptionUpdate(const FString& cvar, const FOptionUpdated& optionUpdatedDelegate) {
	TArray<FOptionUpdated>& Callbacks = DynamicOptionValueCallbacks.FindOrAdd(cvar);
	Callbacks.Add(optionUpdatedDelegate);
}

void USMLSessionSettingsManager::UnsubscribeToDynamicOptionUpdate(const FString& cvar, const FOptionUpdated& optionUpdatedDelegate) {
	TArray<FOptionUpdated>* Callbacks = DynamicOptionValueCallbacks.Find(cvar);
	if (Callbacks != NULL) {
		Callbacks->Remove(optionUpdatedDelegate);
	}
}

void USMLSessionSettingsManager::UnsubscribeToAllDynamicOptionUpdate(UObject* boundObject) {
	for (TPair<FString, TArray<FOptionUpdated>>& Pair : DynamicOptionValueCallbacks) {
		Pair.Value.RemoveAll([&](const FOptionUpdated& Delegate) {
			return Delegate.GetUObject() == boundObject;
		});
	}
}

TArray<UFGDynamicOptionsRow*> USMLSessionSettingsManager::GetOptionWidgetsInCategory(UUserWidget* owningWidget, EOptionCategory category) {
	//Not supported - we are not using default option categories
	return TArray<UFGDynamicOptionsRow*>();
}
