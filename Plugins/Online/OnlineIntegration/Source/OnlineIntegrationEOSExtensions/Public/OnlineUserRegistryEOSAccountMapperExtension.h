#pragma once

#include "IEOSSDKManager.h"
#include "OnlineServicesEOS.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "User/OnlineUserRegistryExtension.h"
#include "Async/Future.h"
#include "OnlineUserRegistryEOSAccountMapperExtension.generated.h"

/**
 * UPROPERTY compatible wrapper for TSet<UOnlineUserBackendLink*>
 */
USTRUCT()
struct FOnlineUserBackendLinkSet
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<TObjectPtr<UOnlineUserBackendLink>> BackendLinksSet;
};

UCLASS()
class UOnlineUserRegistryEOSAccountMapperExtension: public UGameInstanceSubsystem, public IOnlineUserRegistryExtension, public FTickableGameObject
{
	GENERATED_BODY()
public:

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Begin IOnlineUserRegistryExtension interface
	virtual TOptional<TFuture<UOnlineUserInfo*>> ResolveOnlineUser(ULocalUserInfo* LocalUser, UOnlineUserBackendLink* BackendLink) override;
	virtual void UserBackendLinkInitialized(UOnlineUserBackendLink* UserBackendLink) override;
	// End IOnlineUserRegistryExtension interface

	// Begin FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableWhenPaused() const override;
	// End FTickableGameObject interface

	void WorkOnResolves(ULocalUserInfo* LocalUser);
	
	/**
	 * These are the backend links that have not been mapped to a user yet nor have we started resolving them.
	 * There may or may not be a promise for them. @PendingPromises is the place to look for those.
	 */
	UPROPERTY()
	TMap<TObjectPtr<ULocalUserInfo>, FOnlineUserBackendLinkSet> UnmappedBackendLinksByLocalUser;

	/**
	 * These are the backend links that are currently being resolved.
	 */
	UPROPERTY()
	TSet<TObjectPtr<UOnlineUserBackendLink>> BackendLinksPendingResolve;

	/**
	 * These are promises that were made, and they concern both unmapped and pending backend links.
	 */
	TMap<TObjectPtr<UOnlineUserBackendLink>, TArray<TPromise<UOnlineUserInfo*>>> PendingPromises;
	
	EOS_HPlatform EOS_PlatformHandle = nullptr;
	EOS_HUserInfo EOS_UserInfoHandle = nullptr;
};
