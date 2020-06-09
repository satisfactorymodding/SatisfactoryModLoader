#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/Class.h"

/**
 * @OSS
 * Exposes a lot of OSS functionality to blueprint. This drives a lot of the functionality in the join game menu and for invites
 * @todo: Migrate UFGPresenceLibrary, UFGFriendsLibrary, UFGSessionLibrary and UFGInviteLibrary into their own .h and .cpp files
 */

#include "FGLocalPlayer.h"
#include "NAT.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineSessionSettings.h"
#include "FGOnlineSessionSettings.h"
#include "FGOnlineSessionClient.h"
#include "FGNetworkLibrary.generated.h"



DECLARE_DYNAMIC_DELEGATE_OneParam(FSearchQueryCompleteDelegate, FBlueprintSessionResult, result);
DECLARE_DYNAMIC_DELEGATE_TwoParams( FChangeSessionIDDelegate, bool, result, FString, newID );

USTRUCT(BlueprintType)
struct FACTORYGAME_API FOnlinePresence
{
	GENERATED_BODY()

	FOnlinePresence(){}
	
	FOnlinePresence( const TSharedPtr<FOnlineUserPresence> presence ) :
		Presence( presence )
	{
	}

	/** Return true if the presence is valid */
	FORCEINLINE bool IsValid() const { return Presence.IsValid(); }
	
	TSharedPtr<FOnlineUserPresence> Presence;

public:
	FORCEINLINE ~FOnlinePresence() = default;
};

UENUM(BlueprintType)
enum class ENetIdType : uint8
{
	NIT_EPIC UMETA(DisplayName = "Epic"),
	NIT_STEAM UMETA(DisplayName = "Steam"),
	NIT_OTHER UMETA(DisplayName = "Other")
};

UENUM(BlueprintType)
enum ECantJoinReason
{
	CJR_InvalidGame UMETA(DisplayName="Invalid Game"),
	CJR_NotInAGame UMETA(DisplayName="Not in a game"),
	CJR_PlayingOtherGame UMETA(DisplayName="Playing Other Game"),
	CJR_PrivateGame UMETA(DisplayName="Private Game"),
	CJR_DifferentVersion UMETA(DisplayName="Different Version"),
	CJR_FullGame UMETA(DisplayName="Full Game"),
	CJR_Ok UMETA(DisplayName="Ok")
};

//This is just the data from the feedback widget.
USTRUCT( BlueprintType )
struct FACTORYGAME_API FUserFeedbackFrontEndData
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, Category = "User Feedback" )
	bool isSatisfactory;

	UPROPERTY( BlueprintReadWrite, Category = "User Feedback" )
	FString typeOfFeedback;

	UPROPERTY( BlueprintReadWrite, Category = "User Feedback" )
	FString body;

	FUserFeedbackFrontEndData() : isSatisfactory( false ), typeOfFeedback( "" ), body( "" ) {}

public:
	FORCEINLINE ~FUserFeedbackFrontEndData() = default;
};

// @todosession: We assume we always have cached presence for people. So we need to find where a we don't and it matters (friends-friends, discord invites)

UCLASS()
class FACTORYGAME_API UFGPresenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Return true if the presence is online, false if the presence isn't valid */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Presence", Meta = ( DefaultToSelf = "worldContext" ) )
	static bool IsOnline( const FOnlinePresence& presence );

	/** Get the presence of a friend */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Presence", Meta = ( DefaultToSelf = "worldContext" ) )
	static FOnlinePresence GetPresenceFromNetId( UObject* worldContext, const FUniqueNetIdRepl& netId );

	/** Get the presence of a friend */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Presence", Meta = ( DefaultToSelf = "worldContext" ) )
	static bool NetIdHasValidPresence( UObject* worldContext, const FUniqueNetIdRepl& netId );

	/** Get the presence string */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Presence", Meta = ( DefaultToSelf = "worldContext" ) )
	static FString GetPresenceString( const FOnlinePresence& presence );

	/** NOTICE: Only use for remote players. Get the local session for reading session ID for local players. Get the session ID from the presence if the remote player is in a session. Else return value is empty.*/
	UFUNCTION(BlueprintPure, Category = "FactoryGame|Online|Presence", Meta = (DefaultToSelf = "worldContext"))
	static FString GetSessionIDFromPresence(const FOnlinePresence& presence);

	/** @return true if the user is playing satisfactory */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Presence" )
	static bool IsPlayingThisGame( const FOnlinePresence& presence );

	/** @return true if the user is playing another game */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Presence" )
	static bool IsPlayingOtherGame( const FOnlinePresence& presence );

	/** Returns true if a OnlinePresence is valid */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online", meta=(DisplayName = "Valid (OnlinePresence)", CompactNodeTitle = "Is Valid", Keywords = "valid presence"))
	static bool IsValid_OnlinePresence( const FOnlinePresence& a );

public:
	FORCEINLINE ~UFGPresenceLibrary() = default;
};

UCLASS()
class FACTORYGAME_API UFGFriendsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Test if the input friends are equal
	 * @param A - friend
	 * @param B - friend to compare with
	 * @returns True if the friend are the same, false otherwise
	 */
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (OnlineFriends)", CompactNodeTitle = "==", Keywords = "== equal"), Category="Online|Friends")
	static bool EqualEqual_FriendFriend( const FFGOnlineFriend& A, const FFGOnlineFriend& B );

	/** Get the session the current friend is in */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Friends" )
	static FUniqueNetIdRepl GetFriendUniqueNetId( const FFGOnlineFriend& onlineFriend );

	/** Get a friend from a net id */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Friends" )
	static FFGOnlineFriend GetFriendFromNetId( ULocalPlayer* friendOf, const FUniqueNetIdRepl& netId );
		
	/** @return Get the name of the friend */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Friends" )
	static bool GetFriendName( ULocalPlayer* friendOf,  const FFGOnlineFriend& onlineFriend, FString& out_displayName );
	
	/** @return true if the friend is waiting for data, true is bad data is passed in */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Friends" )
	static bool IsWaitingForData( ULocalPlayer* friendOf, const FFGOnlineFriend& onlineFriend );

	/** Returns true if a OnlinePresence is valid */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Friends", meta=(DisplayName = "Valid (FGOnlineFriend)", CompactNodeTitle = "Is Valid", Keywords = "valid friend"))
	static bool IsValid_Friend( const FFGOnlineFriend& a );

public:
	FORCEINLINE ~UFGFriendsLibrary() = default;
};

UCLASS()
class FACTORYGAME_API UFGSessionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Get the settings from a session **/
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Session" )
	static FFGOnlineSessionSettings GetSessionSettings( const FBlueprintSessionResult& session );

	/** Get the settings from a session **/
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Session" )
	static TEnumAsByte<ESessionVisibility> GetSessionVisibility( const FBlueprintSessionResult& session );

	/** Get the session information about my session */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Session" )
	static FBlueprintSessionResult GetMySession( ULocalPlayer* localPlayer );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Online|Session" )
	static void GetPlayersInMySession( ULocalPlayer* localPlayer, TArray< FUniqueNetIdRepl >& out_playersInSession );

	/** Check if a local player is in a game session */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Session" )
	static bool IsInGameSession( ULocalPlayer* localPlayer );
	
	/** return true if the session is valid */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Session", meta=(DisplayName = "Valid (FBlueprintSessionResult)", CompactNodeTitle = "Is Valid", Keywords = "valid session") )
	static bool IsSessionValid( FBlueprintSessionResult session );

	UFUNCTION(BlueprintPure, Category = "FactoryGame|Online|Session")
	static TEnumAsByte<ECantJoinReason> IsSessionJoinable(const FBlueprintSessionResult& session);

	/** Join a session gracefully */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Online|Session", Meta = ( DefaultToSelf = "worldContext" )  )
	static void JoinSession( UObject* worldContext, const FBlueprintSessionResult& session );

	///** Join a session by session ID */
	//UFUNCTION( BlueprintCallable, Category = "FactoryGame|Online|Session", Meta = ( DefaultToSelf = "worldContext" ) )
	//static void JoinSessionByID( UObject* worldContext, const FString sessionID );

	/** Get the max number of players in a session */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Session" )
	static int32 GetMaxNumberOfPlayers( const FBlueprintSessionResult& session );
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Online|Session")
	static bool QuerySessionByFriend(UObject* worldContext, const FUniqueNetIdRepl& playerId, const FFGOnlineFriend& targetFriend, FSearchQueryCompleteDelegate onComplete);

	///** Get the session ID in the form of a string */
	//UFUNCTION( BlueprintPure, Category = "FactoryGame|Online|Session" )
	//static FString GetSessionID( ULocalPlayer* localPlayer );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Online|Session")
	static bool QuerySessionByID(UObject* worldContext, const FUniqueNetIdRepl& playerId, FString sessionOnlineID, FSearchQueryCompleteDelegate onComplete);

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Online|Session" )
	static void SetSessionID( UObject* worldContext, const FUniqueNetIdRepl& playerId, const FString requestedID, FChangeSessionIDDelegate onComplete );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Online" )
	static bool CheckIsCompatibleVersion( const FFGOnlineSessionSettings& session );

public:
	// Native library functions
	static void UpdateSessionFromSessionSettings( FOnlineSessionSettings& session, const FFGOnlineSessionSettings& sessionSettings );
	static void SessionSettingsFromSession( const FOnlineSessionSettings& session, FFGOnlineSessionSettings& sessionSettings );

private:
	void OnFindCompleteDelicgateFunction(bool wasSucsessful);

public:
	FORCEINLINE ~UFGSessionLibrary() = default;
};

UCLASS()
class FACTORYGAME_API UFGInviteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Get net id of a invite */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Invite" )
	static FUniqueNetIdRepl GetInviteSenderUniqueNetId( const FPendingInvite& invite );

	/** Get session from an invite */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Online|Invite" )
	static FBlueprintSessionResult GetSessionFromInvite( const FPendingInvite& invite );

	/** Get invites that's not accepted or rejected */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Online|Invite", Meta = ( DefaultToSelf = "worldContext" ))
	static void GetPendingInvites( UObject* worldContext, TArray<FPendingInvite>& out_invites );

	/** Get invites from a sender */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online|Invite", Meta = ( DefaultToSelf = "worldContext" ))
	static FPendingInvite GetInviteFromSender( UObject* worldContext, const FUniqueNetIdRepl& sender );

	/** Sends a invite to a friend */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Online|Invite")
	static void SendInviteToFriend( ULocalPlayer* fromPlayer, const FFGOnlineFriend& toFriend );

	/** Join a pending invite */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Online|Invite")
	static void JoinInvite( UObject* worldContext, const FPendingInvite& invite );

	/** Discard a pending invite */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Online|Invite")
	static void DiscardInvite( UObject* worldContext, const FPendingInvite& invite );

public:
	FORCEINLINE ~UFGInviteLibrary() = default;
};



UCLASS()
class FACTORYGAME_API UFGNetworkLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** 
	 * Opens a webpage to the specified url. 
	 * (In the case of steam, this opens the steam overlay with a webpage. Dunno what happens elsewhere).
	 * @note: DO NOT INCLUDE HTTP:// IN THE URL.
	 * @return returns true if it succeeds.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Browser" )
	static bool OpenWebURL( const FString& Url );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Feedback" )
	static bool SubmitFeedback( FUserFeedbackFrontEndData frontEndFeedbackData, class APlayerController* playerController );
	
	/** Get the name from a unique net id */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online", Meta = ( DefaultToSelf = "worldContext" ) )
	static bool GetNameFromUniqueNetId( const ULocalPlayer* querier, const FUniqueNetIdRepl& netId, FString& out_name );
	
	/** Get the name from a unique net id */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online" )
	static ENetIdType GetUniqueNetIdType(const FUniqueNetIdRepl& netId);

	/** Compare two net ids */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online", meta=(DisplayName = "Equal (UniqueNetIdRepl)", CompactNodeTitle = "==", Keywords = "== equal"))
	static bool EqualEqual_NetIdNetId( const FUniqueNetIdRepl& a, const FUniqueNetIdRepl& b );
	
	/** Returns true if a UniqueNetId is valid */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online", meta=(DisplayName = "Valid (UniqueNetIdRepl)", CompactNodeTitle = "Is Valid", Keywords = "valid uniquenetid"))
	static bool IsValid_UniqueNetId( const FUniqueNetIdRepl& a );

	/** Query our current NAT-type */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|Online", Meta = ( DefaultToSelf = "worldContext" ) )
	static void QueryNATType( UObject* worldContext );

	/** Get the last cached value of our NAT-type */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Online", Meta = ( DefaultToSelf = "worldContext" ) )
	static ECachedNATType GetCachedNATType( UObject* worldContext );

	UFUNCTION( BlueprintPure, Category="FactoryGame|Online", meta=(DisplayName = "ToText (ECachedNATType)", CompactNodeTitle = "ToText", Keywords = "NAT ToText") )
	static FText NATTypeToText( ECachedNATType NatType );

	UFUNCTION( BlueprintPure, Category="FactoryGame|Online" )
	static FString GetLocalBuildVersion();

	/** Get UniqueNetId from fg local player.*/
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Online" )
	static FUniqueNetIdRepl GetUniqueID( UFGLocalPlayer* localPlayer );

public:
	FORCEINLINE ~UFGNetworkLibrary() = default;
};