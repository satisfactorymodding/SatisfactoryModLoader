#include "SessionSettings/SessionSettingsSubsystem.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGGameMode.h"
#include "FGPlayerController.h"

USessionSettingsSubsystem::USessionSettingsSubsystem() {
	SessionSettingsManager = CreateDefaultSubobject<USMLSessionSettingsManager>(TEXT("SessionSettingsManager"));
}

FVariant USessionSettingsSubsystem::GetSessionSettingValue(const USMLSessionSetting* SessionSetting) const {
	if (SessionSetting == NULL) {
		return FVariant();
	}
	return SessionSettingsManager->GetActiveOptionValue(SessionSetting->UserSetting->StrId);
}

bool USessionSettingsSubsystem::GetSessionSettingBoolValue(const USMLSessionSetting* SessionSetting) const {
	const FVariant SettingValue = GetSessionSettingValue(SessionSetting);
	if (SettingValue.GetType() == EVariantTypes::Bool) {
		return SettingValue.GetValue<bool>();
	}
	return false;
}

float USessionSettingsSubsystem::GetSessionSettingFloatValue(const USMLSessionSetting* SessionSetting) const {
	const FVariant SettingValue = GetSessionSettingValue(SessionSetting);
	if (SettingValue.GetType() == EVariantTypes::Float) {
		return SettingValue.GetValue<float>();
	}
	return false;
}

int32 USessionSettingsSubsystem::GetSessionSettingIntValue(const USMLSessionSetting* SessionSetting) const {
	const FVariant SettingValue = GetSessionSettingValue(SessionSetting);
	if (SettingValue.GetType() == EVariantTypes::Int32) {
		return SettingValue.GetValue<int32>();
	}
	return false;
}

FString USessionSettingsSubsystem::GetSessionSettingStringValue(const USMLSessionSetting* SessionSetting) const {
	const FVariant SettingValue = GetSessionSettingValue(SessionSetting);
	if (SettingValue.GetType() == EVariantTypes::String) {
		return SettingValue.GetValue<FString>();
	}
	return TEXT("");
}

USMLSessionSettingsManager* USessionSettingsSubsystem::GetSessionSettingsManager() const {
	return SessionSettingsManager;
}

void USessionSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	UWorld* World = GetWorld();

	//Initialize session manager with the default values first for the map
	SessionSettingsManager->InitializeForMap(TSoftObjectPtr<UWorld>(World), false);

	//We are only capable of applying non-restart active settings and on server side only
	const bool bIsServerWorld = World->IsServer();
	SessionSettingsManager->SetSettingsApplyPolicy(bIsServerWorld ? ESessionSettingsApplyPolicy::ApplyWhenPossible : ESessionSettingsApplyPolicy::Never);

	//Subscribe to console variable updates for options that have them
	for (USMLSessionSetting* SessionSetting : SessionSettingsManager->GetAllSessionSettings()) {
		if (SessionSetting->UserSetting->CreateCVarFromStrid) {
			if (IConsoleVariable* ConsoleVariable = IConsoleManager::Get().FindConsoleVariable(*SessionSetting->UserSetting->StrId)) {
				ConsoleVariableAssociations.Add(ConsoleVariable, SessionSetting);
				ConsoleVariable->OnChangedDelegate().AddUObject(this, &USessionSettingsSubsystem::OnConsoleVariableChanged);
			}
		}
	}
	
	//We will be able to grab the actual option values the second world is initialized
	World->OnActorsInitialized.AddUObject(this, &USessionSettingsSubsystem::OnWorldActorsInitialized);

	//Subscribe to option changes from the manager so we can update values in real time
	SessionSettingsManager->OnActiveOptionUpdated.AddDynamic(this, &USessionSettingsSubsystem::OnActiveSessionSettingChanged);
	SessionSettingsManager->OnCurrentOptionUpdated.AddDynamic(this, &USessionSettingsSubsystem::OnCurrentSessionSettingChanged);
}

bool USessionSettingsSubsystem::ShouldCreateSubsystem(UObject* Outer) const {
	return FPlatformProperties::RequiresCookedData() && Super::ShouldCreateSubsystem(Outer);
}

void USessionSettingsSubsystem::OnWorldActorsInitialized(const UWorld::FActorsInitializedParams& ActorsInitializedParams) {
	//Populate option values from the world
	//At this point we will already have UWorld::URL set, and potentially the AuthorityGameMode
	UWorld* World = GetWorld();
	check(World == ActorsInitializedParams.World);

	bool bNeedsCurrentOptionsInit = true;

	//Attempt to initialize current option values from the game mode
	if (const AFGGameMode* FGGameMode = Cast<AFGGameMode>(World->GetAuthGameMode())) {
		const FURL FGOptionsURL(&World->URL, *FGGameMode->GetCurrentOptions(), TRAVEL_Relative);
		SessionSettingsManager->LoadOptionValuesFromURLOptions(FGOptionsURL, true, false);
		bNeedsCurrentOptionsInit = false;
	}
	
	//We always take UWorld::URL that we have been loaded with as an active data source
	//We might have been loaded with settings different from the saved ones
	SessionSettingsManager->LoadOptionValuesFromURLOptions(World->URL, bNeedsCurrentOptionsInit, true);

	//Update console variable values for settings that have them
	for (const TPair<IConsoleVariable*, USMLSessionSetting*>& Pair : ConsoleVariableAssociations) {
		const FVariant NewVariableValue = SessionSettingsManager->GetActiveOptionValue(Pair.Value->UserSetting->StrId);
		const FString NewVariableValueString = USMLSessionSettingsManager::ConvertOptionValueToString(NewVariableValue);

		this->bIsUpdatingCVarValue = true;
		Pair.Key->Set(*NewVariableValueString, ECVF_SetByGameSetting);
		this->bIsUpdatingCVarValue = false;
	}

	//Notify our listeners that session settings have been loaded
	OnSessionSettingsLoaded.Broadcast(this);
}

void USessionSettingsSubsystem::OnConsoleVariableChanged(IConsoleVariable* ConsoleVariable) {
	if (!bIsUpdatingCVarValue) {
		const USMLSessionSetting* SessionSetting = ConsoleVariableAssociations.FindChecked(ConsoleVariable);
		const FVariant NewSettingValue = USMLSessionSettingsManager::CreateOptionValueFromString(SessionSetting->UserSetting->GetDefaultValue(), ConsoleVariable->GetString());

		SessionSettingsManager->SetCurrentOptionValue(SessionSetting->UserSetting->StrId, NewSettingValue);
	}
}

void USessionSettingsSubsystem::OnActiveSessionSettingChanged(USMLSessionSettingsManager* InSessionSettingsManager, USMLSessionSetting* SessionSetting) {
	const FString SessionSettingId = SessionSetting->UserSetting->StrId;
	const FVariant ValueVariant = InSessionSettingsManager->GetActiveOptionValue(SessionSettingId);
	const FString NewSettingValue = USMLSessionSettingsManager::ConvertOptionValueToString(ValueVariant);
	
	//Update the associated CVar if we actually have one associated with the current option
	IConsoleVariable* const* ConsoleVariable = ConsoleVariableAssociations.FindKey(SessionSetting);
	if (ConsoleVariable != NULL) {
		this->bIsUpdatingCVarValue = true;
		(*ConsoleVariable)->Set(*NewSettingValue, ECVF_SetByGameSetting);
		this->bIsUpdatingCVarValue = false;
	}

	//Notify all of the connected players that we have changed an active session setting if we are the server
	if (GetWorld()->IsServer()) {
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
			AFGPlayerController* PlayerController = Cast<AFGPlayerController>(*It);

			//Do not send updates to the locally controller players as that is unnecessary
			if (PlayerController != NULL && !PlayerController->IsLocalController()) {
				auto* RemoteCallObject = PlayerController->GetRemoteCallObjectOfClass<USMLSessionSettingsRemoteCallObject>();
				if (RemoteCallObject != NULL) {
					RemoteCallObject->NotifyActiveSessionSettingChanged(SessionSettingId, NewSettingValue);
				}
			}
		}
	}
	//Notify the listeners that the setting has been updated
	OnSessionSettingChanged.Broadcast(this, SessionSetting);

	//Log the active setting change
	UE_LOG(LogTemp, Display, TEXT("Session Setting %s value has been updated to %s (Instigator: %s)"), *SessionSettingId, *NewSettingValue, *CurrentInstigatorPlayer);
}

void USessionSettingsSubsystem::OnCurrentSessionSettingChanged(USMLSessionSettingsManager* InSessionSettingsManager, USMLSessionSetting* SessionSetting) {
	const FString SessionSettingId = SessionSetting->UserSetting->StrId;
	const UWorld* World = GetWorld();
	const FVariant SettingVariant = InSessionSettingsManager->GetCurrentOptionValue(SessionSettingId);
	const FString NewSettingValue = USMLSessionSettingsManager::ConvertOptionValueToString(SettingVariant);

	//Handle server sided changes like options update and sync
	if (World->IsServer()) {
		//Modify AFGGameMode map options string
		if (const AFGGameMode* FGGameMode = Cast<AFGGameMode>(World->GetAuthGameMode())) {
			FString& MapOptionsString = const_cast<FString&>(FGGameMode->GetCurrentOptions());

			FURL MapOptionsURL(NULL, *MapOptionsString, TRAVEL_Absolute);
			MapOptionsURL.Map = TEXT("");
			SessionSettingsManager->PopulateURLOption(SessionSettingId, false, MapOptionsURL);
			MapOptionsString = MapOptionsURL.ToString();
		}

		//Notify players of changes or request the server to change the setting
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
			AFGPlayerController* PlayerController = Cast<AFGPlayerController>(*It);
			if (PlayerController != NULL) {
				auto* RemoteCallObject = PlayerController->GetRemoteCallObjectOfClass<USMLSessionSettingsRemoteCallObject>();
			
				if (RemoteCallObject != NULL && !PlayerController->IsLocalController()) {
					RemoteCallObject->NotifyCurrentSessionSettingChanged(SessionSettingId, NewSettingValue);
				}
			}
		}
	}
	//Politely ask the server to update the setting if we are the admin
	else if (!bIsUpdatingSettingsFromServer) {
		AFGPlayerController* PlayerController = UFGBlueprintFunctionLibrary::GetLocalPlayerController(GetWorld());
		
		const AFGPlayerState* PlayerState = PlayerController->GetPlayerState<AFGPlayerState>();
		auto* RemoteCallObject = PlayerController->GetRemoteCallObjectOfClass<USMLSessionSettingsRemoteCallObject>();

		if (PlayerState != NULL && PlayerState->IsServerAdmin() && RemoteCallObject != NULL) {
			RemoteCallObject->RequestSessionSettingUpdate(SessionSettingId, NewSettingValue);
		}
	}
}

USMLSessionSettingsRemoteCallObject::USMLSessionSettingsRemoteCallObject() {
	this->mForceNetField_USMLSessionSettingsRemoteCallObject = false;
}

void USMLSessionSettingsRemoteCallObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, mForceNetField_USMLSessionSettingsRemoteCallObject);
}

void USMLSessionSettingsRemoteCallObject::RequestSessionSettingUpdate_Implementation(const FString& SessionSettingName, const FString& InNewSettingValue) {
	const AFGPlayerState* PlayerState = GetOuterFGPlayerController()->GetPlayerState<AFGPlayerState>();
	USessionSettingsSubsystem* Subsystem = GetWorld()->GetSubsystem<USessionSettingsSubsystem>();
	if (Subsystem != NULL) {
		USMLSessionSettingsManager* SettingsManager = Subsystem->GetSessionSettingsManager();
		const USMLSessionSetting* SessionSetting = SettingsManager->FindSessionSetting(SessionSettingName);
		
		if (SessionSetting != NULL) {
			const FVariant CurrentValue = SettingsManager->GetCurrentOptionValue(SessionSettingName);
			const FVariant NewSettingValue = USMLSessionSettingsManager::CreateOptionValueFromString(CurrentValue, InNewSettingValue);

			if (CurrentValue != NewSettingValue) {
				Subsystem->SetCurrentInstigator(PlayerState->GetPlayerName());
				SettingsManager->SetCurrentOptionValue(SessionSettingName, NewSettingValue);
				Subsystem->SetCurrentInstigator(TEXT(""));
			}
		}
	}
}

bool USMLSessionSettingsRemoteCallObject::RequestSessionSettingUpdate_Validate(const FString& SessionSettingName, const FString& NewSettingValue) {
	const AFGPlayerController* PlayerController = GetOuterFGPlayerController();

	const AFGPlayerState* PlayerState = PlayerController->GetPlayerState<AFGPlayerState>();
	const USessionSettingsSubsystem* Subsystem = GetWorld()->GetSubsystem<USessionSettingsSubsystem>();

	return PlayerState != NULL && PlayerState->IsServerAdmin() &&
		Subsystem != NULL && Subsystem->GetSessionSettingsManager()->FindSessionSetting(SessionSettingName) != NULL;
}

void USMLSessionSettingsRemoteCallObject::NotifyCurrentSessionSettingChanged_Implementation(const FString& SessionSettingName, const FString& NewSettingValue) {
	USessionSettingsSubsystem* Subsystem = GetWorld()->GetSubsystem<USessionSettingsSubsystem>();
	if (Subsystem != NULL) {
		USMLSessionSettingsManager* SettingsManager = Subsystem->GetSessionSettingsManager();
		const USMLSessionSetting* SessionSetting = SettingsManager->FindSessionSetting(SessionSettingName);
		check(SessionSetting);
		
		const FVariant CurrentValue = SettingsManager->GetCurrentOptionValue(SessionSettingName);
		const FVariant NewValue = USMLSessionSettingsManager::CreateOptionValueFromString(CurrentValue, NewSettingValue);

		if (NewValue != CurrentValue) {
			Subsystem->SetIsUpdatingSettingsFromServer(true);
			SettingsManager->SetCurrentOptionValue(SessionSettingName, NewValue);
			Subsystem->SetIsUpdatingSettingsFromServer(false);
		}
	}
}

void USMLSessionSettingsRemoteCallObject::NotifyActiveSessionSettingChanged_Implementation( const FString& SessionSettingName, const FString& NewSettingValue) {
	USessionSettingsSubsystem* Subsystem = GetWorld()->GetSubsystem<USessionSettingsSubsystem>();
	if (Subsystem != NULL) {
		USMLSessionSettingsManager* SettingsManager = Subsystem->GetSessionSettingsManager();
		const USMLSessionSetting* SessionSetting = SettingsManager->FindSessionSetting(SessionSettingName);
		check(SessionSetting);
		
		const FVariant CurrentValue = SettingsManager->GetCurrentOptionValue(SessionSettingName);
		const FVariant NewValue = USMLSessionSettingsManager::CreateOptionValueFromString(CurrentValue, NewSettingValue);

		if (NewValue != CurrentValue) {
			Subsystem->SetIsUpdatingSettingsFromServer(true);
			SettingsManager->SetActiveOptionValue(SessionSettingName, NewValue);
			Subsystem->SetIsUpdatingSettingsFromServer(false);
		}
	}
}
