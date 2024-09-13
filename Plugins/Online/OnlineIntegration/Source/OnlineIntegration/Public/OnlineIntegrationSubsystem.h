// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OnlineIntegrationTypes.h"
#include "Online/OnlineServices.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineIntegrationState.h"
#include "Engine/Engine.h"
#include "OnlineIntegrationSubsystem.generated.h"

class UOnlineIntegrationState;
class UOnlineIntegrationBackend;
class USessionInformation;

namespace UE::Online
{
class IOnlineServices;
}

/**
 * 
 */
UCLASS(Config=Engine, DefaultConfig)
class ONLINEINTEGRATION_API UOnlineIntegrationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Checks to see if we should display a press start/input confirmation screen at startup. Games can call this or check the trait tags directly */
	UFUNCTION(BlueprintPure, BlueprintPure, Category=CommonUser)
	virtual bool ShouldWaitForStartInput() const;

	/** Checks if a specific platform/feature tag is enabled */
	UFUNCTION(BlueprintPure, Category=CommonUser)
	bool HasTraitTag(const FGameplayTag TraitTag) const
	{
		return TraitTags.HasTag(TraitTag);
	}

	/** Get the services provider type, or None if there isn't one. */
	UOnlineIntegrationBackend* GetServiceProviderBackend(UE::Online::EOnlineServices ServiceProvider) const;

	UFUNCTION(BlueprintCallable)
	class UCommonUserSubsystem* GetUserManager() const;

	UFUNCTION(BlueprintCallable)
	class UCommonSessionSubsystem* GetSessionManager() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UOnlineIntegrationState* GetOnlineIntegrationState() const;

	const TArray<FNetDriverDefinition>& GetDefaultNetDriverDefinitions() const;

	const FGameplayTagContainer& GetTraitTags() const;

protected:
	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Deinitialize() override;
	// End
	
	UPROPERTY()
	TObjectPtr<UOnlineIntegrationState> OnlineIntegrationState;

	UPROPERTY(Config)
	TArray<FName> BackendIds;

	UPROPERTY(Config)
	TArray<TSoftObjectPtr<USessionDefinition>> SessionDefinitions;

	UPROPERTY(Config, EditDefaultsOnly, meta=(ConfigHierarchyEditable))
	TArray<FNetDriverDefinition> DefaultNetDriverDefinitions;

	UPROPERTY(Config, meta=(ConfigHierarchyEditable))
	TArray<FGameplayTag> PlatformTraits;

	/** Cached platform/mode trait tags */
	FGameplayTagContainer TraitTags;
};
