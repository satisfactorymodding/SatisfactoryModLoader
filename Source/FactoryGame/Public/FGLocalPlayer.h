// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/LocalPlayer.h"
#include "FGErrorMessage.h"
#include "NativeGameplayTags.h"
#include "Online/CoreOnline.h"
#include "Online/FGOnlineHelpers.h"
#include "OnlineIntegrationTypes.h"
#include "OnlineSubsystemTypes.h"
#include "PlayerPresenceState.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FGLocalPlayer.generated.h"

class UAddOnEntitlement;
class UFGJoinableGamesViewModel;
class UOnlineIntegrationBackend;
class IFGSessionSettingsInterface;
class UFGInputMappingContext;
class ISessionCreationInteractionHandler;
class ULocalUserInfo;

namespace UE::Online
{
struct FAccountInfo;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnMultiplayerStatusUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnAccountConnectionComplete, const FName, currentPlatform, EEosAccountConnectionResult, result );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAccountUnlinkComplete, bool, result );

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPublicAddressUpdated );

/** Called when the friends list is done with it's initial query */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFriendsListQueried);

/**
 * @IMPORTANT that loading games should always be done through AFGAdminInterface::LoadGame, as that handles travel on dedicated servers.
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
public:
	UFGLocalPlayer();

	//~Begin ULocalPlayer interface
	virtual void PlayerAdded( class UGameViewportClient* inViewportClient, FPlatformUserId inUserId ) override;
	virtual void PlayerRemoved() override;
	virtual void SwitchController(class APlayerController* PC) override;
	virtual void ReceivedPlayerController(APlayerController* NewController) override;
	virtual FString GetNickname() const override;
	virtual void CleanupViewState(FStringView MidParentRootPath) override;
	//~End ULocalPlayer interface
	
	//~Begin FExec Interface
	virtual bool Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar ) override;
	//~End FExec Interface

	/** Listen to option changes we care about */
	void SubscribeToOptionUpdates();
	
	/** Triggered when Maintain Y Axis FOV option have changed */
	UFUNCTION()
    void OnMaintainYAxisFOVUpdated( FString updatedCvar );
	
	/** Returns information about the user embedded into the watermark */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "User" )
	void GetUserWatermarkInformation( TArray<FString>& OutWatermarkData ) const;

	/** Called regularly to update the users presence, can also be called to force update presence and delays the next presence update */
	UFUNCTION()
	void UpdatePresence();

	/** Checks if last logged in user id matches the current logged in user and if not updates the cached value */
	void RefreshRecentRegisteredSocialAccountID();

	void PopulateEnhancedInputUserSettingsWithContexts( class UEnhancedInputUserSettings* inputUserSettings );
	void PopulateChildMappingContexts( const UFGInputMappingContext* mainContext, TArray<UFGInputMappingContext*>& out_childContexts );

	/** Forcefully hides the early loading screen if it is visible */
	void ForceHideEarlyLoadingScreen();
protected:
	//~Begin OnlineIdentity delegates
	void OnLoginStatusChanged( ULocalUserInfo* userInfo, TSharedRef<UE::Online::FAccountInfo> accountInfo, UOnlineIntegrationBackend* backend );
	//~End OnlineIdentity delegates

	/** Get the presence string we should show to other users */
	virtual FString GetPresenceString() const;

	void OnAboutToTravel( ULocalUserInfo* UserInfo, TMap<FString ,FString> &ExtraOptions );

	void GetPresenceState(FPlayerPresenceState& outState) const;
private:

	/** Push error and autosave the game */
	void PushErrorAndAutosave( TSubclassOf<class UFGErrorMessage> errorMessage );

	/** Called when the map is loaded */
	void OnMapLoadedWithWorld( UWorld* InWorld );

	/** Checks whenever the early loading screen should still be visible for the current player controller */
	void CheckEarlyLoadingScreenVisibility();

	/** Sends an http request to ipify.org to get the players public IP address used in the watermark */
	void RequestPublicPlayerAddress();

	/** Handles response for the public IP address used in the watermark */
	void OnPublicPlayerAddressResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccesful);
	
	FString mCachedPublicAddress;
public:

	/** Notify UI that the public address used in the watermark information has been updated */
	UPROPERTY(BlueprintAssignable, Category = "Watermark")
	FOnPublicAddressUpdated mOnPublicAddressUpdated;

protected:
	friend class UFGCheatManager;
	
	// Handle for updating presence info
	FTimerHandle mPresenceUpdateHandle;

	FTimerHandle mCheckStartupArgumentsHanlde;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr< UFGJoinableGamesViewModel > mJoinableGamesModel;

	/** A list of all mapping contexts that can be re-bound. Used for pre-populating input user settings with correct values */
	UPROPERTY()
	TArray<UFGInputMappingContext*> mAllRebindableMappingContexts;

	/**
	 * A cache of the parent to children mapping contexts, built when the player is added
	 * Used to avoid frequently looking up asset registry when we are re-binding the input contexts on the player
	 */
	TMultiMap<TSoftObjectPtr<UFGInputMappingContext>, TSoftObjectPtr<UFGInputMappingContext>> mParentToChildMappingContexts;
	bool mInitializedParentToChildInputMappings{false};

	/** Widget used as an early loading screen after movie player has finished but until we have a valid HUD */
	TSharedPtr<class SWidget> mEarlyLoadingScreenWidget;

	/**
	 * Just a place to store the entitlement pointers after loading them they do not get garbage collected
	 */
	UPROPERTY()
	TArray<TObjectPtr<UAddOnEntitlement>> mAddOnEntitlements;
};
