// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Async/Future.h"
#include "UObject/Interface.h"
#include "OnlineIntegrationTypes.h"
#include "OnlineInteractionHandlers.generated.h"


UENUM(BlueprintType)
enum class EOfflineSessionPromptResult
{
	CancelSessionCreation,
	CreateOfflineSession
};

UINTERFACE()
class ONLINEINTEGRATION_API USessionCreationInteractionHandler: public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE_OneParam(FOnlineSessionPromptResultKnown, EOfflineSessionPromptResult);

class ONLINEINTEGRATION_API ISessionCreationInteractionHandler
{
	GENERATED_BODY()
	
public:
	virtual void ShowSessionCreationFailurePopup(FOnlineSessionPromptResultKnown Delegate) = 0;
	virtual void HideSessionCreationFailurePopup() = 0;
};