// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "OnlineIntegrationTypes.h"
#include "Tickable.h"
#include "Online/OnlineServices.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Online/Connectivity.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineIntegrationSettings.h"
#include "OnlineIntegrationSubsystem.generated.h"

namespace UE::Online
{
class IOnlineServices;
}

struct FOnlineContextCache
{
	/** Online services, accessor to specific services */
	UE::Online::IOnlineServicesPtr OnlineServices;
	/** Cached auth service */
	UE::Online::IAuthPtr AuthService;

	/** Last connection status that was passed into the HandleNetworkConnectionStatusChanged hander */
	UE::Online::EOnlineServicesConnectionStatus CurrentConnectionStatus = UE::Online::EOnlineServicesConnectionStatus::NotConnected;

	// Any delegates we might have been bound to. They will be unbound on destruction
	TArray<UE::Online::FOnlineEventDelegateHandle> DelegateHandles;

	/** Resets state, important to clear all shared ptrs */
	void Reset()
	{
		OnlineServices.Reset();
		AuthService.Reset();
		CurrentConnectionStatus = UE::Online::EOnlineServicesConnectionStatus::NotConnected;
	}
};

UCLASS()
class ONLINEINTEGRATION_API UOnlineIntegrationComponent : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Returns true if we are currently connected to backend servers */
	bool HasOnlineConnection(EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Game) const;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnOnlineContextCreated();

	const FOnlineContextCache* GetMappedContextCache(EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Game) const;
	FOnlineContextCache* GetMappedContextCache(EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Game);

	const FOnlineContextCache* GetUnmappedContextCache(EOnlineIntegrationUnmappedContext Context) const;
	FOnlineContextCache* GetUnmappedContextCache(EOnlineIntegrationUnmappedContext Context);

	EOnlineIntegrationUnmappedContext ResolveOnlineContext(EOnlineIntegrationMappedContext Context) const;

	EOnlineIntegrationMode GetIntegrationMode() const;

	/** True if there is a separate platform and service interface */
	bool HasExternalServiceContext() const;
	const FGameplayTagContainer& GetTraitTags() const;
	bool HasTraitTag(const FGameplayTag& Tag) const;

	class UOnlineIntegrationSubsystem* GetOnlineIntegration() const;
};

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
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
		return CachedTraitTags.HasTag(TraitTag);
	}

	/** Get the services provider type, or None if there isn't one. */
	UE::Online::EOnlineServices GetOnlineServicesProvider(EOnlineIntegrationUnmappedContext Context) const;
	EOnlineIntegrationUnmappedContext GetServiceProviderContext(UE::Online::EOnlineServices ServiceProvider) const;

	/** Returns the current online connection status */
	UE::Online::EOnlineServicesConnectionStatus GetConnectionStatus(EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Game) const;

	/** Returns true if we are currently connected to backend servers */
	bool HasOnlineConnection(EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Game) const;

	/** True if there is a separate platform and service interface */
	bool HasExternalServiceContext() const;

	const FGameplayTagContainer& GetTraitTags() const;

	UFUNCTION(BlueprintCallable)
	class UCommonUserSubsystem* GetUserManager() const;

	UFUNCTION(BlueprintCallable)
	class UCommonSessionSubsystem* GetSessionManager() const;

	/** Gets internal data for a type of online system, can return null for service */
	const FOnlineContextCache* GetMappedContextCache(EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Game) const;
	FOnlineContextCache* GetMappedContextCache(EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Game);

	const FOnlineContextCache* GetUnmappedContextCache(EOnlineIntegrationUnmappedContext Context) const;
	FOnlineContextCache* GetUnmappedContextCache(EOnlineIntegrationUnmappedContext Context);

	FORCEINLINE FName GetPlatformOnlineServices() const
	{
		return PlatformOnlineServices;
	}

	bool HasInitializedBackend() const;
	bool CreateOnlineContexts(const FOnlineIntegrationPlatformSettings& Settings, FOnlineIntegrationInternalAccessKey&& AccessToken);

	/** Resolves a context that has default behavior into a specific context */
	EOnlineIntegrationUnmappedContext ResolveOnlineContext(EOnlineIntegrationMappedContext Context) const;
	EOnlineIntegrationMode GetOnlineIntegrationMode() const { return OnlineIntegrationMode; }
	EOnlineIntegrationUnmappedContext GetComplementaryContext(EOnlineIntegrationUnmappedContext Context) const;

	/** Temporary utility functions that can restart the process. Don't use them unless you have a strong reason to.*/
	void ShutdownProcess();
	void RestartProcess();
protected:
	// UGameInstanceSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Deinitialize() override;
	// End

	/** The set of traits defined per-platform (e.g., the default input mode, whether or not you can exit the application, etc...) */
	UPROPERTY()
	EOnlineIntegrationMode OnlineIntegrationMode = EOnlineIntegrationMode::Undefined;

	UPROPERTY(config, meta=(ConfigHierarchyEditable))
	FName PlatformOnlineServices;

	UPROPERTY(config, meta=(ConfigHierarchyEditable))
	FName ExternalOnlineServices;

	UPROPERTY()
	TArray<TObjectPtr<UOnlineIntegrationComponent>> OnlineIntegrationComponents;
private:
	friend class UOnlineIntegrationComponent;
	
	/** Cached platform/mode trait tags */
	FGameplayTagContainer CachedTraitTags;

	/** Do not access this outside of initialization */
	TUniquePtr<FOnlineContextCache> ServiceContextInternal;
	TUniquePtr<FOnlineContextCache> PlatformContextInternal;
};
