// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DeveloperSettings.h"
#include "OnlineIntegrationSettings.generated.h"

USTRUCT()
struct ONLINEINTEGRATION_API FOnlineIntegrationPlatformSettings
{
	GENERATED_BODY()

	UPROPERTY(config, meta=(ConfigHierarchyEditable))
	bool bMultiUser = false;
	
	UPROPERTY(config, meta=(ConfigHierarchyEditable))
	FName PlatformOnlineServices;
	
	UPROPERTY(config, meta=(ConfigHierarchyEditable))
	FName ExternalOnlineServices;
};


/**
 * 
 */
UCLASS(Config=Game, DefaultConfig)
class ONLINEINTEGRATION_API UOnlineIntegrationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UOnlineIntegrationSettings();
};
