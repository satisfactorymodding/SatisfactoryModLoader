#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineIntegrationTypes.h"

#include "OnlineUserPresence.generated.h"

class UOnlineIntegrationBackend;
namespace UE {namespace Online
{
struct FUserPresence;
}}

UENUM(BlueprintType)
enum class EOnlineUserPresenceStatus : uint8
{
	/** User is offline */
	Offline,
	/** User is online */
	Online,
	/** User is away */
	Away,
	/** User is away for >2 hours (can change depending on platform) */
	ExtendedAway,
	/** User is in do not disturb mode */
	DoNotDisturb,
	/** Default */
	Unknown
};

UENUM(BlueprintType)
enum class EOnlineUserPresenceJoinability : uint8
{
	/** Anyone can matchmake/discover and join this session */
	Public,
	/**  Anyone trying to join must be a friend of a lobby member */
	FriendsOnly,
	/** Anyone trying to join must have been invited first */
	InviteOnly,
	/** Not currently accepting invites */
	Private,
	/** Default */
	Unknown
};

UENUM(BlueprintType)
enum class EOnlineUserPresenceGameStatus : uint8
{
	/** The user is playing the same game as you */
	PlayingThisGame,
	/** The user is playing a different game than you */
	PlayingOtherGame,
	/** Default */
	Unknown
};

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UOnlineUserPresence: public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	EOnlineUserPresenceStatus GetStatus() const;
	EOnlineUserPresenceJoinability GetJoinability() const;
	EOnlineUserPresenceGameStatus GetGameStatus() const;
	FString GetStatusString() const;
	FString GetRichPresenceString() const;
	const TMap<FString, FString>& GetProperties() const;
	UOnlineIntegrationBackend* GetBackend() const;
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineIntegrationBackend> Backend;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	EOnlineUserPresenceStatus Status = EOnlineUserPresenceStatus::Unknown;
	/** Session state */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	EOnlineUserPresenceJoinability Joinability = EOnlineUserPresenceJoinability::Unknown;
	/** Playing this game */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	EOnlineUserPresenceGameStatus GameStatus = EOnlineUserPresenceGameStatus::Unknown;
	/** Stringified representation of the user status (online, offline, whatever the platform wants to define) */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString StatusString;
	/** Game-defined representation of the current game state (e.g. "Squads- 4 Remaining" or "Level 5 Warrior") */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString RichPresenceString;
	/** Key value pairs in the session metadata */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> Properties;
};
