// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Online/Sessions.h"
#include "SessionInformation.h"

#include "SessionInformationPrivate.generated.h"

/**
 *
 */
UCLASS(Hidden, Within=CommonSessionSubsystem)
class USessionInformationPrivate : public USessionInformation
{
	GENERATED_BODY()
public:
	void RegisterSessionBackend(UOnlineSessionBackendLink* InBackend, bool bIsHostingBackend, TSharedPtr<const UE::Online::ISession> SessionPtr);
	void OnSessionUpdateReceived(const UE::Online::FSessionUpdate& SessionUpdate, UOnlineIntegrationBackend* Backend);
	
	void SetSessionHost(UOnlineUserInfo* InUserInfo);
	void SetSessionDefinition(USessionDefinition* InSessionDefinition);

	virtual void RefreshCachedData(FDateTime UpdateTimestampUtc) override;
	void InitializeSessionData(TSharedRef<const UE::Online::ISession> Session, UOnlineSessionBackendLink* Backend);
	void SetGameSessionActor(AGameSession* GameSession);
};
