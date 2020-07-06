#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "NAT.h"
#include "GameFramework/OnlineReplStructs.h"
#include "FGOnlineSessionSettings.generated.h"

UENUM(BlueprintType)
enum ESessionVisibility
{
	SV_Private UMETA(DisplayName=Private),
	SV_FriendsOnly UMETA(DisplayName=FriendsOnly),
	SV_Invalid UMETA(Hidden)
};


/**
 * The content of this struct is used to populate the session settings automatically
 * using the Unreal Reflection system, the keys names used to propagate the settings is
 * the variable name, then the variables is converted to strings and back.
 */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FFGOnlineSessionSettings
{
	GENERATED_BODY()

	/** IMPORTANT: Don't rename this! This is parsed in engine code */
	UPROPERTY()
	FUniqueNetIdRepl	HostId;

	/** Number of players currently connected to the game */
	UPROPERTY(BlueprintReadOnly)
	int32				NumConnectedPlayers;

	/** For how long has the game been played in seconds */
	UPROPERTY(BlueprintReadOnly)
	int32				PlayDuration;

	/** The build version on the form ++FactoryGame+Main-4.20-CL-123456 */
	UPROPERTY( BlueprintReadOnly )
	FString				BuildVersion;

	/** Name of the session, same as the name exposed in the Save/Load menus */
	UPROPERTY(BlueprintReadOnly)
	FString				SaveSessionName;

	/** A unique identifier of a game session */
	UPROPERTY(BlueprintReadOnly)
	FString				CSS_SessionId;

	/** Hosts nat type */
	UPROPERTY(BlueprintReadOnly)
	ECachedNATType		NATType;

public:
	FORCEINLINE ~FFGOnlineSessionSettings() = default;
};