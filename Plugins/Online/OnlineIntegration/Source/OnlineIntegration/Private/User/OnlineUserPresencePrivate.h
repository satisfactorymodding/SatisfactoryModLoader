// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineUserPresence.h"

#include "OnlineUserPresencePrivate.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEINTEGRATION_API UOnlineUserPresencePrivate : public UOnlineUserPresence
{
	GENERATED_BODY()
public:
	void Init(UOnlineIntegrationBackend* Backend);
	
	void Update(TSharedRef<const UE::Online::FUserPresence> OnlinePresence);
};
