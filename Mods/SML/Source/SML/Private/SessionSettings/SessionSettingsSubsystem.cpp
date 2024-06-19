﻿#include "SessionSettings/SessionSettingsSubsystem.h"
#include "FGGameMode.h"
#include "FGPlayerController.h"
#include "Subsystem/SubsystemActorManager.h"
#include "Settings/FGUserSettingApplyType.h"
#include "Net/UnrealNetwork.h"

ASessionSettingsSubsystem::ASessionSettingsSubsystem() {
	ReplicationPolicy = ESubsystemReplicationPolicy::SpawnOnServer_Replicate;
}

void ASessionSettingsSubsystem::Init() {
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	check(SessionSettingsManager);

	if (!HasAuthority())
	{
		// We're a client, so we only have our own player controller
		AFGPlayerController* PlayerController = Cast<AFGPlayerController>(GetWorld()->GetFirstPlayerController());
		USMLSessionSettingsRemoteCallObject* RCO = PlayerController->GetRemoteCallObjectOfClass<USMLSessionSettingsRemoteCallObject>();
		RCO->Server_RequestAllSessionSettings();
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

void ASessionSettingsSubsystem::Multicast_SessionSettingUpdated_Implementation(const FString& StrID, const FString& value) {
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

void USMLSessionSettingsRemoteCallObject::Server_RequestAllSessionSettings_Implementation()
{
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	TMap<FString, UFGUserSettingApplyType*> Settings = SessionSettingsManager->GetAllSessionSettings();
	for (TPair<FString, UFGUserSettingApplyType*> Setting : Settings)
	{
		FVariant AppliedValue = Setting.Value->GetAppliedValue();
		FString ValueString = USessionSettingsManager::VariantToString(AppliedValue);
		Client_SendSessionSetting(Setting.Key, ValueString);
	}
}

bool USMLSessionSettingsRemoteCallObject::Server_RequestAllSessionSettings_Validate()
{
	USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	return SessionSettingsManager != NULL;
}

void USMLSessionSettingsRemoteCallObject::Client_SendSessionSetting_Implementation(const FString& SessionSettingName, const FString& ValueString)
{
	ASessionSettingsSubsystem* SessionSettingsSubsystem = ASessionSettingsSubsystem::Get(GetWorld());
	check(SessionSettingsSubsystem);

	SessionSettingsSubsystem->PushSettingToSessionSettings(SessionSettingName, USessionSettingsManager::StringToVariant(ValueString));
}

bool USMLSessionSettingsRemoteCallObject::Client_SendSessionSetting_Validate(const FString& SessionSettingName, const FString& ValueString)
{
	const USessionSettingsManager* SessionSettingsManager = GetWorld()->GetSubsystem<USessionSettingsManager>();
	return SessionSettingsManager != NULL && !SessionSettingName.IsEmpty() && !ValueString.IsEmpty();
}