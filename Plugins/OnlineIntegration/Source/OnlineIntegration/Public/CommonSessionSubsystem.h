// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "OnlineIntegrationSubsystem.h"
#include "OnlineIntegrationTypes.h"
#include "Online/Sessions.h"
#include "UObject/StrongObjectPtr.h"
#include "Engine/EngineBaseTypes.h"
#include "Online/CoreOnline.h"
#include "CommonSessionTypes.h"
#include "CommonSessionSubsystem.generated.h"

class USessionMigrationSequence;
class UOnlineFriend;
DECLARE_LOG_CATEGORY_EXTERN(LogCommonSession, Log, All);

namespace UE {namespace Online
{
struct FUILobbyJoinRequested;
struct FLobby;
}}

class FCommonOnlineSearchSettingsOSSv2;
using FCommonOnlineSearchSettings = FCommonOnlineSearchSettingsOSSv2;

USTRUCT(BlueprintType)
struct FCommonSessionCreationSettings
{
	GENERATED_BODY()

	/** Indicates if the session is a full online session or a different type */
	UPROPERTY(BlueprintReadWrite, Category=Session)
	ECommonSessionOnlineMode OnlineMode;

	/** Indicates the visibility (or discoverability) of this session. eg: Invite only */
	UPROPERTY(BlueprintReadWrite, Category=Session)
	ECommonSessionJoinPolicy JoinPolicy;

	/** True if this request should create a player-hosted lobbies if available */
	UPROPERTY(BlueprintReadWrite, Category = Session)
	bool bUseLobbies;

	/** String used during matchmaking to specify what type of game mode this is */
	UPROPERTY(BlueprintReadWrite, Category=Session)
	FString ModeNameForAdvertisement;

	/** The map that will be loaded at the start of gameplay, this needs to be a valid long package name */
	UPROPERTY(BlueprintReadWrite, Category=Session, meta=(AllowedTypes="World"))
	FTopLevelAssetPath MapID;

	/** Extra arguments passed as URL options to the game */
	UPROPERTY(BlueprintReadWrite, Category=Session)
	TMap<FString, FString> ExtraArgs;

	/** Maximum players allowed per gameplay session */
	UPROPERTY(BlueprintReadWrite, Category=Session)
	int32 MaxPlayerCount = 16;
	
	UPROPERTY(BlueprintReadWrite, Category=Session)
	TObjectPtr<ULocalUserInfo> Host;

	/** Returns the full map name that will be used during gameplay */
	FString GetMapName() const;
	/** Constructs the full URL that will be passed to ServerTravel */
	FString ConstructTravelURL() const;
};

//////////////////////////////////////////////////////////////////////
// CommonSessionSubsystem Events

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommonSessionUpdateReceived, const UE::Online::FSessionUpdate& SessionUpdate,
	TSharedRef<const UE::Online::ISession> Session);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnFindSessionByIdSessionComplete, const FCommonSession&, Session);

/**
 * 
 */
UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UCommonSessionSubsystem : public UOnlineIntegrationComponent
{
	GENERATED_BODY()

public:
	/**
	 * Creates and initializes a session creation sequence. It is up to the caller to begin the execution of the sequence.
	 * Only one session creation sequence may exist at any given time so this function may fail
	 * @param SessionSettings These settings will be used for the newly created session
	 * @return The sequence object or a nullptr on failure
	 */
	UFUNCTION(BlueprintCallable, Category = Session)
	class USessionMigrationSequence* CreateSessionCreationSequence(const FCommonSessionCreationSettings &SessionSettings, TScriptInterface<ISessionCreationInteractionHandler> InteractionHandler);

	UFUNCTION(BlueprintCallable, Category = Session)
	class USessionMigrationSequence* CreateSessionJoiningSequence(APlayerController* Player, FCommonSession Session);

	/** Clean up any active sessions, called from cases like returning to the main menu */
	UFUNCTION(BlueprintCallable, Category=Session)
	virtual void CleanUpSessions();

	UFUNCTION(BlueprintCallable, Category=Session)
	void InviteFriendToGameSession(const UOnlineFriend* OnlineFriend);

	UFUNCTION(BlueprintCallable, Category=Session)
	void RespondToGameInvite(APlayerController* Player, UOnlineFriend* OnlineFriend, bool bAccept);

	UFUNCTION(BlueprintCallable, Category=Session)
	void JoinFriendGame(APlayerController* Player, UOnlineFriend* OnlineFriend);

	/**
	 * A temporary helper function that should be used when one has a string session id and wants to resolve the session behind it.
	 * This will be replaced
	 */
	UFUNCTION(BlueprintCallable)
	void FetchSessionById(APlayerController* Player, const FString& SessionId, FOnFindSessionByIdSessionComplete OnComplete);

	//////////////////////////////////////////////////////////////////////
	/// Native API - should be preferred when used from native code

	// @todo: We will slowly wrap these APIs but it's more practical to start here
	/** Queries the relevant API session service for sessions matching the given parameters */
	TFuture<UE::Online::TOnlineResult<UE::Online::FFindSessions>> FindSessions(UE::Online::FFindSessions::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	TFuture<UE::Online::TOnlineResult<UE::Online::FFindSessions>> FindSession(ULocalUserInfo* User, FCommonSession Session);
	
	TFuture<UE::Online::TOnlineResult<UE::Online::FJoinSession>> JoinSession(UE::Online::FJoinSession::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	void LeaveSession(ULocalUserInfo* UserInfo, FName SessionName);
	TFuture<UE::Online::TOnlineResult<UE::Online::FLeaveSession>> LeaveSession(UE::Online::FLeaveSession::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	
	UE::Online::TOnlineResult<UE::Online::FGetSessionByName> GetSessionByName(UE::Online::FGetSessionByName::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	TFuture<UE::Online::TOnlineResult<UE::Online::FUpdateSessionSettings>> UpdateSessionSettings(UE::Online::FUpdateSessionSettings::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	void UpdateSessionKey(APlayerController* Player, FName SessionName, FName Key, const UE::Online::FCustomSessionSetting& Value);
	void UpdateSessionJoinability(APlayerController* Player, FName SessionName, ECommonSessionJoinPolicy JoinPolicy);
	
	UE::Online::FOnlineSessionId MakeOnlineSessionId(const FString& SessionIdString, EOnlineIntegrationUnmappedContext Context);

	static FString OnlineSessionIdToString(UE::Online::FOnlineSessionId SessionId); 
	TFuture<UE::Online::TOnlineResult<UE::Online::FLeaveSession>> DestroySession(ULocalUserInfo* LocalUserInfo, FName SessionName, EOnlineIntegrationUnmappedContext Context);
	TFuture<UE::Online::TOnlineResult<UE::Online::FCreateSession>> CreateSession(ULocalUserInfo* LocalUserInfo, FName SessionName, EOnlineIntegrationUnmappedContext Context, const FCommonSessionCreationSettings& Settings);
	TFuture<UE::Online::TOnlineResult<UE::Online::FAddSessionMember>> AddSessionMember(UE::Online::FAccountId User, FName SessionName);
	TFuture<UE::Online::TOnlineResult<UE::Online::FRemoveSessionMember>> RemoveSessionMember(UE::Online::FAccountId User, FName SessionName);

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

	FDelegateHandle AddOnSessionUpdateReceivedDelegate(const FOnCommonSessionUpdateReceived::FDelegate& Delegate);
	void RemoveSessionUpdateReceivedDelegate(FDelegateHandle Handle);

	/**
	 * Looks for any startup parameters indicating that we may have to join some game as a result or accepting an invite or other means.
	 * It only produces effects the first time it is called. Subsequent calls are silently ignored.
	 * Care should be put into only calling this only after all the online subsystems and users are fully initialized. 
	 */
	void JoinStartupSession(ULocalUserInfo* LocalUserInfo, FName SessionName);
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void HandleSessionUpdated(const UE::Online::FSessionUpdated& SessionUpdated, EOnlineIntegrationUnmappedContext Context) const;

	// Functions called during the process of creating or joining a session, these can be overidden for game-specific behavior

	/** Called when traveling to a session fails */
	virtual void TravelLocalSessionFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ReasonString);

	/** Called after traveling to the new hosted session map */
	virtual void HandlePostLoadMap(UWorld* World);

	virtual void OnOnlineContextCreated() override;

	UE::Online::ISessionsPtr GetSessionsInterface(EOnlineIntegrationUnmappedContext Context) const;

	/** Get the local user id for a given controller */
	UE::Online::FAccountId GetAccountId(APlayerController* PlayerController) const;
	/** Event handle for UI lobby join requested */
	UE::Online::FOnlineEventDelegateHandle LobbyJoinRequestedHandle;

	/** The travel URL that will be used after session operations are complete */
	FString PendingTravelURL;

	/** True if we want to cancel the session after it is created */
	bool bWantToDestroyPendingSession = false;

	/** True if this is a dedicated server, which doesn't require a LocalPlayer to create a session */
	bool bIsDedicatedServer = false;

	bool bAlreadyJoinedStartupSession = false;

	/** Settings for the current search */
	TSharedPtr<FCommonOnlineSearchSettings> SearchSettings;
	
	FOnCommonSessionUpdateReceived SessionUpdateDelegate;
	TArray<UE::Online::FOnlineEventDelegateHandle> DelegateHandles;
	
	void UpdatePresencePostLoadMap(UWorld* World);

	/**
	 * Any pending only async operation that have the desired outcome to joining another session, either by means to creating one or joining an existing one.
	 */
	UPROPERTY()
	TObjectPtr<USessionMigrationSequence> SessionMigrationSequence = nullptr;
};

/**
 *This is only a temporary API for session lookups and session interactions from BP. 
 **/ 
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnFetchFriendSessionComplete, class UOnlineFriend*, Friend, const FCommonSession&, Session);

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UCommonSessionStatics : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=Sessions)
	static void FetchFriendSession(class UOnlineFriend* Friend, const FOnFetchFriendSessionComplete& CompletionDelegate);

	UFUNCTION(BlueprintCallable, Category=Sessions)
	static USessionMigrationSequence* JoinSession(APlayerController* PlayerController, const FCommonSession& Session);
};
