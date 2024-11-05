// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Async/Future.h"
#include "CommonSessionTypes.h"
#include "CoreMinimal.h"
#include "Engine/EngineBaseTypes.h"
#include "IPAddress.h"
#include "NativeGameplayTags.h"
#include "Online/CoreOnline.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Online/Sessions.h"
#include "OnlineIntegrationSubsystem.h"
#include "SessionCreationSettings.h"
#include "UObject/StrongObjectPtr.h"

#include "CommonSessionSubsystem.generated.h"

class UOnlineIntegrationSession;
class USessionInformation;
class UOnlineSessionBackendLink;
class USessionMigrationSequence;
class UOnlineFriend;
class ULocalUserInfo;

DECLARE_LOG_CATEGORY_EXTERN(LogCommonSession, Log, All);

struct ONLINEINTEGRATION_API FSessionTraitTags
{
	static FNativeGameplayTag HasFindFriendSessionSupport;
};

using FOptionsMap = TMap<FString, FString>;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnJustAboutToTravel, ULocalUserInfo* /*LocalUSerInfo*/, FOptionsMap& /*OutOptions*/);

struct ONLINEINTEGRATION_API FSessionDelegates
{
	/**
	 * Fired when a player is about to travel to a new session as a client. This is an opportunity to modify the travel URL options.
	 */
	static FOnJustAboutToTravel OnJustAboutToTravel;
};

//////////////////////////////////////////////////////////////////////
// CommonSessionSubsystem Events

/**
 * 
 */
UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UCommonSessionSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	/**
	 * Creates and initializes a session creation sequence. It is up to the caller to begin the execution of the sequence.
	 * Only one session creation sequence may exist at any given time so this function may fail
	 * @param SessionSettings These settings will be used for the newly created session
	 * @return The sequence object or a nullptr on failure
	 */
	class USessionMigrationSequence* CreateSessionCreationSequence(const FCommonSessionCreationSettings &SessionSettings);
	
	/**
	 * Creates a session joining sequence. A session joining sequence is an object that encapsulates all the required steps for joining a game. 
	 * @return The valid session joining sequence, or nullptr if another session is already pending or invalid params were passed
	 */
	class USessionMigrationSequence* CreateSessionJoiningSequence(const FSessionJoinParams& JoinParams);
	
	/**
	 * Looks up the session that the respective friend is in, for the respective backend.
	 */
	TFuture<USessionInformation*> FetchFriendSession(UOnlineFriend* Friend, UOnlineIntegrationBackend* Backend);

	//////////////////////////////////////////////////////////////////////
	/// Native API - should be preferred when used from native code
	UE::Online::TOnlineResult<UE::Online::FGetSessionByName> GetSessionByName(UE::Online::FGetSessionByName::Params&& Params, UOnlineIntegrationBackend* Backend);

	static bool IsProviderNameSupported(const FString& ProviderName);
	static UE::Online::FOnlineSessionId MakeOnlineSessionId(const FString& SessionIdString);
	static FString OnlineSessionIdToString(UE::Online::FOnlineSessionId SessionId);

	UFUNCTION(BlueprintPure)
	static FString ToString_OnlineSessionBackendLink(UOnlineSessionBackendLink* SessionBackendLink);
	
	TFuture<UE::Online::TOnlineResult<UE::Online::FLeaveSession>> DestroySession(ULocalUserInfo* LocalUserInfo, FName SessionName, UOnlineIntegrationBackend* Backend);

	UFUNCTION(BlueprintPure, Category=Sessions)
	FString GetStringAttributeFromSession(const FCommonSession& Session, FName Key) const;

	UFUNCTION(BlueprintPure, Category=Sessions)
	int64 GetIntAttributeFromSession(const FCommonSession& Session, FName Key) const;

	UFUNCTION(BlueprintPure, Category=Sessions)
	double GetDoubleAttributeFromSession(const FCommonSession& Session, FName Key) const;

	UFUNCTION(BlueprintPure, Category=Sessions)
	bool GetBoolAttributeFromSession(const FCommonSession& Session, FName Key) const;

	UFUNCTION(BlueprintCallable, Category=Sessions)
	static bool IsValidSession(const FCommonSession& Session);

	TSharedPtr<const UE::Online::ISession> GetSession(const FCommonSession& SessionHandle) const;

	/**
	 * Looks for any startup parameters indicating that we may have to join some game as a result or accepting an invite or other means.
	 * It only produces effects the first time it is called. Subsequent calls are silently ignored.
	 * Care should be put into only calling this only after all the online subsystems and users are fully initialized. 
	 */
	void JoinStartupSession(ULocalUserInfo* LocalUserInfo, FName SessionName);

	const TArray<FNetDriverDefinition>& GetDefaultNetDriverDefinitions() const;

	// <FL> [WuttkeP] Store platform invites that were received before logging into EOS so they can be joined later.
	void SetPendingJoinRequest(const UE::Online::FUISessionJoinRequested& JoinRequest);
	// </FL>

	void RegisterSessionBackendMapping(UE::Online::FOnlineSessionId OnlineSessionId, UOnlineSessionBackendLink* SessionBackend);

	// @todo: This will backfire if multiple calls are made to this function for the same backend link. We should handle this case.
	TFuture<USessionInformation*> ResolveOnlineSession(ULocalUserInfo* LocalUser, UOnlineSessionBackendLink* BackendLink);
	TFuture<USessionInformation*> ResolveOnlineSession(ULocalUserInfo* LocalUser, UE::Online::FOnlineSessionId SessionId);

	/// Will find a session backend link for the provided session id or will create one if not found. 
	UOnlineSessionBackendLink* FindOrCreateSessionBackendLink(UE::Online::FOnlineSessionId SessionId);
	
	/// Will always create a new session backend link for the provided session id. Assumes the session id does not already have a backend link.
	/// Passing in an invalid session id is considered a programming error
	UOnlineSessionBackendLink* CreateSessionBackendLink(UE::Online::FOnlineSessionId SessionId);
	
	/// Tries to find a session backend link with the provided session id. 
	UOnlineSessionBackendLink* FindSessionBackendLink(UE::Online::FOnlineSessionId SessionId);

	USessionInformation* GetOnlineSessionInfo(UE::Online::FOnlineSessionId SessionId);
	void EnqueueSessionDataUpdate(USessionInformation* SessionInfo);

protected:
	// Begin FTickableGameObject
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const;
	virtual TStatId GetStatId() const override;
	// End
	USessionMigrationSequence* CreateSessionMigrationSequence(UClass* Class);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void HandleSessionUpdated(const UE::Online::FSessionUpdated& SessionUpdated, UOnlineIntegrationBackend* Backend) const;

	// Functions called during the process of creating or joining a session, these can be overidden for game-specific behavior

	/** Called when traveling to a session fails */
	virtual void TravelLocalSessionFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ReasonString);

	/** Called after traveling to the new hosted session map */
	virtual void HandlePostLoadMap(UWorld* World);

	virtual void BindDelegates();

	UE::Online::ISessionsPtr GetSessionsInterface(UOnlineIntegrationBackend* InBackend) const;

	/** Event handle for UI lobby join requested */
	UE::Online::FOnlineEventDelegateHandle LobbyJoinRequestedHandle;

	/** The travel URL that will be used after session operations are complete */
	FString PendingTravelURL;

	/** True if this is a dedicated server, which doesn't require a LocalPlayer to create a session */
	bool bIsDedicatedServer = false;

	bool bAlreadyJoinedStartupSession = false;

	TArray<UE::Online::FOnlineEventDelegateHandle> DelegateHandles;
	
	void UpdatePresencePostLoadMap(const UWorld* World) const;
	
	TMap<UE::Online::FOnlineSessionId, TWeakObjectPtr<UOnlineSessionBackendLink>> SessionIdToBackendMap;
	TMap<TWeakObjectPtr<UOnlineSessionBackendLink>, TWeakObjectPtr<USessionInformation>> BackendToSessionMap;
	TMap<UE::Online::FOnlineSessionId, TArray<TPromise<USessionInformation*>>> OnlineSessionIdResolvePromises;

	UPROPERTY()
	TSet<TObjectPtr<USessionInformation>> SessionDataUpdateQueue;

	// <FL> [WuttkeP] Store platform invites that were received before logging into EOS so they can be joined later.
	TOptional<UE::Online::FUISessionJoinRequested> PendingJoinRequest;
	// </FL>
};

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UCommonSessionStatics : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category=Sessions)
	static USessionMigrationSequence* JoinSession(APlayerController* PlayerController, USessionInformation* SessionInfo);

	UFUNCTION(Blueprintable, Category=Session)
	static USessionDefinition* GetSessionDefinitionForWorld(const UWorld* World);

	static void CombineOptionsToString(FString& OutCombinedString, const TMap<FString, FString> &Options);
};
