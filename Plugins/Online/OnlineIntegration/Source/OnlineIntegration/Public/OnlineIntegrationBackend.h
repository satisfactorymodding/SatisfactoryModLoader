// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "MVVMViewModelBase.h"
#include "OnlineIntegrationTypes.h"

#include "OnlineIntegrationBackend.generated.h"

class UOnlineIntegrationSubsystem;
class UOnlineIntegrationState;

/**
 * Represents one instance of an online integration backend and caches all the data pertaining to said backend.
 */
UCLASS(Config=Engine, PerObjectConfig, Abstract, Within=OnlineIntegrationSubsystem)
class UOnlineIntegrationBackend: public UMVVMViewModelBase, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
public:
	
	const TArray<FNetDriverDefinition> &GetNetDriverDefinitions() const
	{
		return NetDriverDefinitions;
	}

	EOnlineBackendConnectionStatus GetConnectionStatus() const
	{
		return ConnectionStatus;
	}

	UE::Online::IOnlineServicesPtr GetServicesPtr() const
	{
		return ServicesPtr;
	}

	FName GetServiceProviderName() const
	{
		return ServiceProviderName;
	}

	const TSet<FName> &GetMirrorSessionBackends() const
	{
		return MirrorSessionBackends;
	}

	UFUNCTION(BlueprintCallable)
	void AddTraitTag(FGameplayTag TraitTag);

	UFUNCTION(BlueprintCallable)
	void ClearTraitTag(FGameplayTag TraitTag);

	UFUNCTION(BlueprintCallable)
	bool HasTraitTag(FGameplayTag TraitTag) const;
	
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	const TArray<FGameplayTag>& GetLoginTags() const
	{
		return LoginTags;
	}

	UOnlineIntegrationSubsystem* GetOnlineIntegration() const;
	UOnlineIntegrationState* GetOnlineIntegrationState() const;
protected:
	/**
	 * Service provider name for this backend. Needs to be convertible to an UE::Online::EOnlineServices member.
	 */
	UPROPERTY(Config, BlueprintReadOnly)
	FName ServiceProviderName;

	/**
	 * Net drivers that this backend will use. If specified, this backend will be allowed to host sessions and will do so through these drivers.
	 */
	UPROPERTY(Config)
	TArray<FNetDriverDefinition> NetDriverDefinitions;

	/**
	 * A set of all the backends mirror sessions should be created for when a session is hosted by this backend.
	 */
	UPROPERTY(Config)
	TSet<FName> MirrorSessionBackends;
	
	/**
	 * The connection status of this backend. 
	 */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	EOnlineBackendConnectionStatus ConnectionStatus = EOnlineBackendConnectionStatus::NotConnected;

	/**
	 * Traits that describe this backend.
	 */
	UPROPERTY(Config, BlueprintReadOnly, FieldNotify)
	FGameplayTagContainer BackendTraits;

	/**
	 * Default backend traits for this backend. Only exists as a separate field because FGameplayTagContainer cannot be initialized from a config file.
	 */
	UPROPERTY(Config)
	TArray<FGameplayTag> DefaultBackendTraits;

	/**
	 * If provided, this tag will be added to the ULocalUserInfo gameplay tags when they are logged in to this backend.
	 */
	UPROPERTY(Config)
	TArray<FGameplayTag> LoginTags;
	
	/** Online services, accessor to specific services */
	UE::Online::IOnlineServicesPtr ServicesPtr;
};
