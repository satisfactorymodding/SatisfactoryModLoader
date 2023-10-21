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

class UOnlineFriend;

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
// UCommonSession_SearchResult

/** A result object returned from the online system that describes a joinable game session */
UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UCommonSession_SearchResult : public UObject
{
	GENERATED_BODY()

public:
	/** Returns an internal description of the session, not meant to be human readable */
	UFUNCTION(BlueprintCallable, Category=Session)
	FString GetDescription() const;

	/** Gets an arbitrary string setting, bFoundValue will be false if the setting does not exist */
	UFUNCTION(BlueprintPure, Category=Sessions)
	void GetStringSetting(FName Key, FString& Value, bool& bFoundValue) const;

	/** Gets an arbitrary integer setting, bFoundValue will be false if the setting does not exist */
	UFUNCTION(BlueprintPure, Category = Sessions)
	void GetIntSetting(FName Key, int32& Value, bool& bFoundValue) const;

	/** The number of private connections that are available */
	UFUNCTION(BlueprintPure, Category=Sessions)
	int32 GetNumOpenPrivateConnections() const;

	/** The number of publicly available connections that are available */
	UFUNCTION(BlueprintPure, Category=Sessions)
	int32 GetNumOpenPublicConnections() const;

	/** The maximum number of publicly available connections that could be available, including already filled connections */
	UFUNCTION(BlueprintPure, Category = Sessions)
	int32 GetMaxPublicConnections() const;

	/** Ping to the search result, MAX_QUERY_PING is unreachable */
	UFUNCTION(BlueprintPure, Category=Sessions)
	int32 GetPingInMs() const;

public:
	/** Pointer to the platform-specific implementation */
	TSharedPtr<const UE::Online::FLobby> Lobby;
};

//////////////////////////////////////////////////////////////////////
// UCommonSession_SearchSessionRequest

/** Delegates called when a session search completes */
DECLARE_MULTICAST_DELEGATE_TwoParams(FCommonSession_FindSessionsFinished, bool bSucceeded, const FText& ErrorMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCommonSession_FindSessionsFinishedDynamic, bool, bSucceeded, FText, ErrorMessage);

/** Request object describing a session search, this object will be updated once the search has completed */
UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UCommonSession_SearchSessionRequest : public UObject
{
	GENERATED_BODY()

public:
	/** Indicates if the this is looking for full online games or a different type like LAN */
	UPROPERTY(BlueprintReadWrite, Category = Session)
	ECommonSessionOnlineMode OnlineMode;

	/** True if this request should look for player-hosted lobbies if they are available, false will only search for registered server sessions */
	UPROPERTY(BlueprintReadWrite, Category = Session)
	bool bUseLobbies;

	/** List of all found sessions, will be valid when OnSearchFinished is called */
	UPROPERTY(BlueprintReadOnly, Category=Session)
	TArray<TObjectPtr<UCommonSession_SearchResult>> Results;

	/** Native Delegate called when a session search completes */
	FCommonSession_FindSessionsFinished OnSearchFinished;

	/** Called by subsystem to execute finished delegates */
	void NotifySearchFinished(bool bSucceeded, const FText& ErrorMessage);

private:
	/** Delegate called when a session search completes */
	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (DisplayName = "On Search Finished", AllowPrivateAccess = true))
	FCommonSession_FindSessionsFinishedDynamic K2_OnSearchFinished;
};

//////////////////////////////////////////////////////////////////////
// CommonSessionSubsystem Events

/**
 * Event triggered when the local user has requested to join a session from an external source, for example from a platform overlay.
 * Generally, the game should transition the player into the session.
 * @param LocalPlatformUserId the local user id that accepted the invitation. This is a platform user id because the user might not be signed in yet.
 * @param RequestedSession the requested session. Can be null if there was an error processing the request.
 * @param RequestedSessionResult result of the requested session processing
 */
DECLARE_MULTICAST_DELEGATE_ThreeParams(FCommonSessionOnUserRequestedSession, const FPlatformUserId& /*LocalPlatformUserId*/,
	UCommonSession_SearchResult* /*RequestedSession*/, const FOnlineResultInformation& /*RequestedSessionResult*/);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCommonSessionOnUserRequestedSession_Dynamic, const FPlatformUserId&, LocalPlatformUserId,
	UCommonSession_SearchResult*, RequestedSession, const FOnlineResultInformation&, RequestedSessionResult);

/**
 * Event triggered when a session join has completed, after joining the underlying session and before traveling to the server if it was successful.
 * The event parameters indicate if this was successful, or if there was an error that will stop it from traveling.
 * @param Result result of the session join
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FCommonSessionOnJoinSessionComplete, const FOnlineResultInformation& /*Result*/);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommonSessionOnJoinSessionComplete_Dynamic, const FOnlineResultInformation&, Result);

/**
 * Event triggered when a session creation for hosting has completed, right before it travels to the map.
 * The event parameters indicate if this was successful, or if there was an error that will stop it from traveling.
 * @param Result result of the session join
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FCommonSessionOnCreateSessionComplete, const FOnlineResultInformation& /*Result*/);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCommonSessionOnCreateSessionComplete_Dynamic, const FOnlineResultInformation&, Result);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCommonSessionUpdateReceived, const UE::Online::FSessionUpdate& SessionUpdate,
	TSharedRef<const UE::Online::ISession> Session);
/**
 * Event triggered when a session join has completed, after resolving the connect string and prior to the client traveling.
 * @param URL resolved connection string for the session with any additional arguments
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FCommonSessionOnPreClientTravel, FString& /*URL*/);

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
	class UOnlineAsyncOperation* CreateSessionCreationSequence(const FCommonSessionCreationSettings &SessionSettings);

	/** Creates a session search object with default options to look for default online games, this can be modified after creation */
	UFUNCTION(BlueprintCallable, Category = Session)
	virtual UCommonSession_SearchSessionRequest* CreateOnlineSearchSessionRequest();

	/** Starts process to join an existing session, if successful this will connect to the specified server */
	UFUNCTION(BlueprintCallable, Category=Session)
	virtual void JoinSession(APlayerController* JoiningPlayer, UCommonSession_SearchResult* Request);

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
	
	TFuture<UE::Online::TOnlineResult<UE::Online::FJoinSession>> JoinSession(UE::Online::FJoinSession::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	void LeaveSession(ULocalUserInfo* UserInfo, FName SessionName);
	TFuture<UE::Online::TOnlineResult<UE::Online::FLeaveSession>> LeaveSession(UE::Online::FLeaveSession::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	
	UE::Online::TOnlineResult<UE::Online::FGetSessionByName> GetSessionByName(UE::Online::FGetSessionByName::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	TFuture<UE::Online::TOnlineResult<UE::Online::FUpdateSessionSettings>> UpdateSessionSettings(UE::Online::FUpdateSessionSettings::Params&& Params, EOnlineIntegrationUnmappedContext Context);
	UE::Online::FOnlineSessionId MakeOnlineSessionId(const FString& SessionIdString, EOnlineIntegrationUnmappedContext Context);

	static FString OnlineSessionIdToString(UE::Online::FOnlineSessionId SessionId); 
	TFuture<UE::Online::TOnlineResult<UE::Online::FLeaveSession>> DestroySession(ULocalUserInfo* LocalUserInfo, FName SessionName, EOnlineIntegrationUnmappedContext Context);
	TFuture<UE::Online::TOnlineResult<UE::Online::FCreateSession>> CreateSession(ULocalUserInfo* LocalUserInfo, FName SessionName, EOnlineIntegrationUnmappedContext Context, const FCommonSessionCreationSettings& Settings);
	TFuture<UE::Online::TOnlineResult<UE::Online::FAddSessionMember>> AddSessionMember(UE::Online::FAccountId User, FName SessionName, EOnlineIntegrationUnmappedContext Context);
	//////////////////////////////////////////////////////////////////////
	// Events

	/** Native Delegate when a local user has accepted an invite */
	FCommonSessionOnUserRequestedSession OnUserRequestedSessionEvent;
	/** Event broadcast when a local user has accepted an invite */
	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (DisplayName = "On User Requested Session"))
	FCommonSessionOnUserRequestedSession_Dynamic K2_OnUserRequestedSessionEvent;

	/** Native Delegate when a JoinSession call has completed */
	FCommonSessionOnJoinSessionComplete OnJoinSessionCompleteEvent;
	/** Event broadcast when a JoinSession call has completed */
	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (DisplayName = "On Join Session Complete"))
	FCommonSessionOnJoinSessionComplete_Dynamic K2_OnJoinSessionCompleteEvent;

	/** Native Delegate when a CreateSession call has completed */
	FCommonSessionOnCreateSessionComplete OnCreateSessionCompleteEvent;
	/** Event broadcast when a CreateSession call has completed */
	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (DisplayName = "On Create Session Complete"))
	FCommonSessionOnCreateSessionComplete_Dynamic K2_OnCreateSessionCompleteEvent;

	/** Native Delegate for modifying the connect URL prior to a client travel */
	FCommonSessionOnPreClientTravel OnPreClientTravelEvent;

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
	void FindSessionsInternal(APlayerController* SearchingPlayer, const TSharedRef<FCommonOnlineSearchSettings>& InSearchSettings);
	void JoinSessionInternal(ULocalPlayer* LocalPlayer, UCommonSession_SearchResult* Request);
	void InternalTravelToSession(const FName SessionName);
	void NotifyUserRequestedSession(const FPlatformUserId& PlatformUserId, UCommonSession_SearchResult* RequestedSession,
		const FOnlineResultInformation& RequestedSessionResult);
	void NotifyJoinSessionComplete(const FOnlineResultInformation& Result);
	void NotifyCreateSessionComplete(const FOnlineResultInformation& Result);

	void FindSessionsInternalOSSv2(ULocalPlayer* LocalPlayer);
	void JoinSessionInternalOSSv2(ULocalPlayer* LocalPlayer, UCommonSession_SearchResult* Request);
	UE::Online::ISessionsPtr GetSessionsInterface(EOnlineIntegrationUnmappedContext Context) const;
	void CleanUpSessionsOSSv2();

	/** Process a join request originating from the online service */
	void OnSessionJoinRequested(const UE::Online::FUILobbyJoinRequested& EventParams);

	/** Get the local user id for a given controller */
	UE::Online::FAccountId GetAccountId(APlayerController* PlayerController) const;
	/** Get the lobby id for a given session name */
	UE::Online::FLobbyId GetLobbyId(const FName SessionName) const;
	/** Event handle for UI lobby join requested */
	UE::Online::FOnlineEventDelegateHandle LobbyJoinRequestedHandle;

	/** The travel URL that will be used after session operations are complete */
	FString PendingTravelURL;

	/** True if we want to cancel the session after it is created */
	bool bWantToDestroyPendingSession = false;

	/** True if this is a dedicated server, which doesn't require a LocalPlayer to create a session */
	bool bIsDedicatedServer = false;

	/** Settings for the current search */
	TSharedPtr<FCommonOnlineSearchSettings> SearchSettings;
	
	FOnCommonSessionUpdateReceived SessionUpdateDelegate;
	TArray<UE::Online::FOnlineEventDelegateHandle> DelegateHandles;
	
	void UpdatePresencePostLoadMap(UWorld* World);

	UPROPERTY()
	TObjectPtr<UOnlineAsyncOperation> SessionCreationSequence = nullptr;
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
	static void JoinSession(APlayerController* PlayerController, const FCommonSession& Session);
};
