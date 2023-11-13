#pragma once

#include "EngineMinimal.h"
#include "OnlineIntegrationTypes.h"
#include "Online/Sessions.h"
#include "CommonSessionTypes.generated.h"

USTRUCT(BlueprintType)
struct FCommonSessionInfo
{
	GENERATED_BODY()

	/* Whether the session is only available in the local network and not via internet connection. Only available in some platforms. False by default */
	UPROPERTY(BlueprintReadOnly)
	bool bIsLANSession = false;

	/* Whether the session is configured to run as a dedicated server. Only available in some platforms. False by default */
	UPROPERTY(BlueprintReadOnly)
	bool bIsDedicatedServerSession = false;

	/* Whether this session will allow sanctioned players to join it. True by default */
	UPROPERTY(BlueprintReadOnly)
	bool bAllowSanctionedPlayers = true;

	/* Whether this is a secure session protected by anti-cheat services. False by default */
	UPROPERTY(BlueprintReadOnly)
	bool bAntiCheatProtected = false;
};

USTRUCT(BlueprintType)
struct FCommonSessionSettings
{
	GENERATED_BODY()

	/* Maximum number of slots for session members */
	UPROPERTY(BlueprintReadOnly)
	int32 NumMaxConnections = 0;

	/* Enum value describing the level of restriction to join the session. Public by default */
	UPROPERTY(BlueprintReadOnly)
	ECommonSessionJoinPolicy JoinPolicy = ECommonSessionJoinPolicy::Public;

	/* Override value to restrict the session from accepting new members, regardless of other factors. True by default */
	UPROPERTY(BlueprintReadOnly)
	bool bAllowNewMembers = true;

	/* Map of user-defined settings to be passed to the platform APIs as additional information for various purposes */
	UE::Online::FCustomSessionSettingsMap CustomSettings;
};

USTRUCT(BlueprintType)
struct FCommonSession
{
	GENERATED_BODY()
	friend class UCommonSessionStatics;

	FCommonSession(EOnlineIntegrationUnmappedContext InContext, UE::Online::FOnlineSessionId InSessionId)
		: Context(InContext)
		, SessionId(InSessionId)
	{
	}

	FCommonSession() = default;
	FCommonSession(const FCommonSession&) = default;
	FCommonSession(FCommonSession&&) = default;

	FCommonSession& operator=(const FCommonSession&) = default;
	FCommonSession& operator=(FCommonSession&&) = default;

	bool IsValid() const
	{
		return SessionId.IsValid();
	}

	bool operator==(const FCommonSession& Session) const
	{
		return SessionId == Session.SessionId;
	}

	UE::Online::FOnlineSessionId GetSessionId() const
	{
		return SessionId;
	}

	EOnlineIntegrationUnmappedContext GetContext() const
	{
		return Context;
	}
protected:
	EOnlineIntegrationUnmappedContext Context;
	UE::Online::FOnlineSessionId SessionId;
};
 