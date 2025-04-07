// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "MVVMViewModelBase.h"
#include "Online/CoreOnline.h"

#include "OnlineIntegrationState.generated.h"

class ULocalUserInfo;
class USessionDefinition;
class USessionMigrationSequence;
class UGameplayTagContainerViewModel;
class UOnlineIntegrationBackend;
class UGameSessionInfo;

/**
 * The entry point model for the entire Online Integration which glues everything together. Entry point for more specific models.  
 */
UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UOnlineIntegrationState: public UMVVMViewModelBase
{
	GENERATED_BODY()
	friend class UOnlineIntegrationSubsystem;
	
public:
	UOnlineIntegrationState();
	
	UOnlineIntegrationBackend* GetPlatformBackend() const;
	UOnlineIntegrationBackend* GetExternalBackend() const;
	
	TArray<UOnlineIntegrationBackend*> GetBackends() const;
	UOnlineIntegrationBackend* GetBackendByIndex(int32 Index) const;
	UOnlineIntegrationBackend* GetBackendByProvider(FName ServiceProvider);
	UOnlineIntegrationBackend* GetBackendByOnlineServiceType(UE::Online::EOnlineServices type); // <FL>[KonradA]
	USessionMigrationSequence* GetPendingSessionMigrationSequence() const;

	ULocalUserInfo* GetFirstUserInfo() const;
	const UGameplayTagContainerViewModel& GetTagContainer() const;

	UFUNCTION(BlueprintCallable)
	USessionDefinition* GetSessionDefinitionByName(FName SessionDefinition) const;

	UFUNCTION(BlueprintCallable)
	USessionDefinition* GetDefaultSessionDefinition();

	const TArray<TObjectPtr<USessionDefinition>>& GetSessionDefinitions() const
	{
		return SessionDefinitions;
	}

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineIntegrationBackend> PlatformBackend;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineIntegrationBackend> ExternalBackend;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TArray<TObjectPtr<UOnlineIntegrationBackend>> Backends;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<ULocalUserInfo> FirstUserInfo;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<USessionMigrationSequence> PendingSessionMigration;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UGameplayTagContainerViewModel> TagContainer;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TArray<TObjectPtr<USessionDefinition>> SessionDefinitions;

	FString ConvertServiceEnumToServiceProviderString(UE::Online::EOnlineServices type); //<FL>[KonradA]
};
