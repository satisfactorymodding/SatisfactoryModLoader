 // Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGServerManagerSettings.generated.h"

UCLASS( Config=Game, defaultconfig, meta = ( DisplayName = "Server Manager Settings" ) )
class FACTORYDEDICATEDCLIENT_API UFGServerManagerSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Returns the default from specified SoftClass */
	static const UFGServerManagerSettings* Get();

	UPROPERTY( EditDefaultsOnly, Config, Category = "Server manager settings" )
	TSoftClassPtr< class UFGBaseServerInteractionHandler > mServerInteractionHandlerClass;
};
