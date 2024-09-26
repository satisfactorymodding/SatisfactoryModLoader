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
		FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &ASessionSettingsSubsystem::GameModePostLogin);
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

void ASessionSettingsSubsystem::GameModePostLogin(AGameModeBase* GameMode, APlayerController* PlayerController) const {
	if (!PlayerController || PlayerController->GetWorld() != GetWorld())
		return;

	AFGPlayerController* FGPlayerController = Cast<AFGPlayerController>(PlayerController);
	if (!FGPlayerController) {
		UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("Skipping client Mod Session Settings initialization, PlayerController is not an AFGPlayerController"));
		return;
	}
	// AFGGameMode::PostLogin sets the remote call objects on the player controller
	// before calling Super, so the RCOs are valid here
	SendAllSessionSettings(FGPlayerController);
}

void ASessionSettingsSubsystem::SendAllSessionSettings(AFGPlayerController* PlayerController) const {
	USMLSessionSettingsRemoteCallObject* RCO = PlayerController->GetRemoteCallObjectOfClass<USMLSessionSettingsRemoteCallObject>();
	
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	TMap<FString, UFGUserSettingApplyType*> Settings = SessionSettingsManager->GetAllSessionSettings();
	for (TPair<FString, UFGUserSettingApplyType*> Setting : Settings)
	{
		FVariant AppliedValue = Setting.Value->GetAppliedValue();
		FString ValueString = USessionSettingsManager::VariantToString(AppliedValue);
		RCO->Client_SendSessionSetting(Setting.Key, ValueString);
	}
}

void ASessionSettingsSubsystem::Multicast_SessionSettingUpdated_Implementation(const FString& StrID, const FString& value) {
	if (HasAuthority()) {
		return;
	}
	PushSettingToSessionSettings(StrID, USessionSettingsManager::StringToVariant(value));
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

void USMLSessionSettingsRemoteCallObject::Client_SendSessionSetting_Implementation(const FString& SessionSettingName, const FString& ValueString)
{
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	check(SessionSettingsManager);

	SessionSettingsManager->ForceSetOptionValue(SessionSettingName, USessionSettingsManager::StringToVariant(ValueString), this);
}

bool USMLSessionSettingsRemoteCallObject::Client_SendSessionSetting_Validate(const FString& SessionSettingName, const FString& ValueString)
{
	const USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	return SessionSettingsManager != NULL && !SessionSettingName.IsEmpty() && !ValueString.IsEmpty();
}
