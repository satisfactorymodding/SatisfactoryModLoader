// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Online/FGNat.h"
#include "GameFramework/OnlineReplStructs.h"
#include "FGOnlineSessionSettings.generated.h"

UENUM(BlueprintType)
enum class ESessionVisibility: uint8
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
struct FFGOnlineSessionSettings
{
	GENERATED_BODY()

	/** For how long has the game been played in seconds */
	UPROPERTY(BlueprintReadOnly)
	int32				PlayDuration = 0;

	/** The build version on the form ++FactoryGame+Main-4.20-CL-123456 */
	UPROPERTY( BlueprintReadOnly )
	FString				BuildVersion = {};

	/** Name of the session, same as the name exposed in the Save/Load menus */
	UPROPERTY(BlueprintReadOnly)
	FString				SaveSessionName = {};

	/** Hosts nat type */
	UPROPERTY(BlueprintReadOnly)
	ECachedNATType		NATType = ECachedNATType::CNT_TBD;

	/** IF creative mode is enabled for this session. i.e. players can use advanced game settings */
	UPROPERTY(BlueprintReadOnly)
	bool				IsCreativeModeEnabled = false;

	UPROPERTY(BlueprintReadOnly)
	ESessionVisibility	Visibility = ESessionVisibility::SV_Private;

	/** The number of players currently in the session */
	UPROPERTY(BlueprintReadOnly)
	int32				NumSessionMembers = 0;

	/** The maximum number of players allowed by the session */
	UPROPERTY(BlueprintReadOnly)
	int32				MaxSessionMembers = 0;

	/** The session host nickname. */
	UPROPERTY(BlueprintReadOnly)
	FString				HostNickname;
};