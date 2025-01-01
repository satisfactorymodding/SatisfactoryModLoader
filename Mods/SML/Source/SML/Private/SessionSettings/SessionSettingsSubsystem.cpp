#include "SessionSettings/SessionSettingsSubsystem.h"
#include "FGGameState.h"
#include "FGPlayerController.h"
#include "SatisfactoryModLoader.h"
#include "GameFramework/GameState.h"
#include "Subsystem/SubsystemActorManager.h"
#include "Settings/FGUserSettingApplyType.h"
#include "Net/UnrealNetwork.h"

ASessionSettingsSubsystem::ASessionSettingsSubsystem() {
	ReplicationPolicy = ESubsystemReplicationPolicy::SpawnOnServer_Replicate;
}

void ASessionSettingsSubsystem::Init() {
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	check(SessionSettingsManager);

	if (HasAuthority()) {
		// We have to chunk the replication of a map, and the server must decide how much data to send,
		// so we cannot send the list of missing setting names, as that could, itself, overflow the buffer (though arguably unlikely)
		// For this, we only populate the settings names list on server to ensure it gets replicated,
		// and then we can use this order to decide which settings to send in each chunk, and the client can know which settings the values belong to		
		SessionSettingsManager->GetAllSessionSettings().GetKeys(SessionSettingsNames);
	}

	OnOptionUpdatedDelegate = FOnOptionUpdated::CreateUObject(this, &ASessionSettingsSubsystem::OnSessionSettingUpdated);
	SessionSettingsManager->SubscribeToAllOptionUpdates(OnOptionUpdatedDelegate);
}

ASessionSettingsSubsystem* ASessionSettingsSubsystem::Get(UWorld* World) {
	USubsystemActorManager* SubsystemActorManager = World->GetSubsystem<USubsystemActorManager>();
	check(SubsystemActorManager);

	return SubsystemActorManager->GetSubsystemActor<ASessionSettingsSubsystem>();
}

void ASessionSettingsSubsystem::OnSessionSettingUpdated(const FString StrID, FVariant value) {
	if(HasAuthority()) {
		Multicast_SessionSettingUpdated(StrID, USessionSettingsManager::VariantToString(value));
	} else {
		// We're a client, so we only have our own player controller
		AFGPlayerController* PlayerController = Cast<AFGPlayerController>(GetWorld()->GetFirstPlayerController());
		USMLSessionSettingsRemoteCallObject* RCO = PlayerController->GetRemoteCallObjectOfClass<USMLSessionSettingsRemoteCallObject>();
		RCO->Server_RequestSessionSettingUpdate(StrID, USessionSettingsManager::VariantToString(value));
	}
}

void ASessionSettingsSubsystem::PushSettingToSessionSettings(const FString& StrID, FVariant value) {
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	check(SessionSettingsManager);

	SessionSettingsManager->ForceSetOptionValue(StrID, value, this);
}

void ASessionSettingsSubsystem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASessionSettingsSubsystem, SessionSettingsNames);
}

void ASessionSettingsSubsystem::Multicast_SessionSettingUpdated_Implementation(const FString& StrID, const FString& value) {
	if (HasAuthority()) {
		return;
	}
	PushSettingToSessionSettings(StrID, USessionSettingsManager::StringToVariant(value));
}

void ASessionSettingsSubsystem::OnRep_SessionSettingsNames() {
	if (!HasPendingSessionSettingsRequest && !HasAuthority()) {
		// We're on a client, so there should be only one player controller
		// and we only care to request the settings, so even if there are more, it doesn't matter
		AFGPlayerController* FirstPlayerController = GetWorld()->GetFirstPlayerController<AFGPlayerController>();
		if (FirstPlayerController) {
			USMLSessionSettingsRemoteCallObject* RCO = FirstPlayerController->GetRemoteCallObjectOfClass<USMLSessionSettingsRemoteCallObject>();
			if (RCO) {
				ReceivedSessionSettings = 0;
				RCO->Server_RequestInitialSessionSettings(0);
				HasPendingSessionSettingsRequest = true;
			}
		}
	}
	if (!HasPendingSessionSettingsRequest) {
		// Retry until the RCO is available
		GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ASessionSettingsSubsystem::OnRep_SessionSettingsNames));
	}
}

USMLSessionSettingsRemoteCallObject::USMLSessionSettingsRemoteCallObject() {
	this->mForceNetField_USMLSessionSettingsRemoteCallObject = false;
}

void USMLSessionSettingsRemoteCallObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, mForceNetField_USMLSessionSettingsRemoteCallObject);
}

void USMLSessionSettingsRemoteCallObject::Server_RequestSessionSettingUpdate_Implementation(const FString& SessionSettingName, const FString& InNewSettingValueString) {
	ASessionSettingsSubsystem* SessionSettingsSubsystem = ASessionSettingsSubsystem::Get(GetWorld());
	check(SessionSettingsSubsystem);
	
	SessionSettingsSubsystem->PushSettingToSessionSettings(SessionSettingName, USessionSettingsManager::StringToVariant(InNewSettingValueString));
}

bool USMLSessionSettingsRemoteCallObject::Server_RequestSessionSettingUpdate_Validate(const FString& SessionSettingName, const FString& InNewSettingValueString) {
	const USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();

	return SessionSettingsManager != NULL && SessionSettingsManager->FindSessionSetting(SessionSettingName) != NULL;
}

void USMLSessionSettingsRemoteCallObject::Server_RequestInitialSessionSettings_Implementation(const int& CurrentIndex) {
	ASessionSettingsSubsystem* SessionSettingsSubsystem = ASessionSettingsSubsystem::Get(GetWorld());
	fgcheck(SessionSettingsSubsystem);

	// Current values for session settings are primitives, so they don't take up much space
	// But if we support more complex types, we may need to limit the size of the data sent, not the number of settings
	int NumSettingsToSend = FMath::Min(SessionSettingsSubsystem->SessionSettingsNames.Num() - CurrentIndex, 512);
	TArray<FString> SessionSettingsNamesToSend;
	SessionSettingsNamesToSend.Reserve(NumSettingsToSend);
	for (int i = 0; i < NumSettingsToSend; i++) {
		SessionSettingsNamesToSend.Add(SessionSettingsSubsystem->SessionSettingsNames[CurrentIndex + i]);
	}

	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	fgcheck(SessionSettingsManager);

	TArray<FString> SettingValues;
	SettingValues.Reserve(NumSettingsToSend);
	for (const FString& SettingName : SessionSettingsNamesToSend) {
		FVariant Value = SessionSettingsManager->FindSessionSetting(SettingName)->GetAppliedValue();
		FString ValueString = USessionSettingsManager::VariantToString(Value);
		SettingValues.Add(ValueString);
	}

	Client_RespondInitialSessionSettings(SettingValues);	
}

void USMLSessionSettingsRemoteCallObject::Client_RespondInitialSessionSettings_Implementation(const TArray<FString>& SessionSettings)
{
	ASessionSettingsSubsystem* SessionSettingsSubsystem = ASessionSettingsSubsystem::Get(GetWorld());
	fgcheck(SessionSettingsSubsystem);
	
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	fgcheck(SessionSettingsManager);

	for (int i = 0; i < SessionSettings.Num(); i++) {
		SessionSettingsSubsystem->PushSettingToSessionSettings(SessionSettingsSubsystem->SessionSettingsNames[SessionSettingsSubsystem->ReceivedSessionSettings + i], USessionSettingsManager::StringToVariant(SessionSettings[i]));
	}
	SessionSettingsSubsystem->ReceivedSessionSettings += SessionSettings.Num();
	SessionSettingsSubsystem->HasPendingSessionSettingsRequest = false;
	if (SessionSettingsSubsystem->ReceivedSessionSettings < SessionSettingsSubsystem->SessionSettingsNames.Num()) {
		Server_RequestInitialSessionSettings(SessionSettingsSubsystem->ReceivedSessionSettings);
	}
}
