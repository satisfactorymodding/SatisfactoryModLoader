#pragma once

#include "CoreMinimal.h"
#include "Online/Sessions.h"
#include "CommonSessionTypes.generated.h"

class UOnlineIntegrationBackend;

USTRUCT(BlueprintType)
struct FCommonSession
{
	GENERATED_BODY()
	friend class UCommonSessionStatics;

	FCommonSession(UOnlineIntegrationBackend* InBackend, UE::Online::FOnlineSessionId InSessionId)
		: Backend(InBackend)
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

	UOnlineIntegrationBackend* GetBackend() const
	{
		return Backend;
	}
protected:
	UPROPERTY()
	TObjectPtr<UOnlineIntegrationBackend> Backend;
	UE::Online::FOnlineSessionId SessionId;
};
 