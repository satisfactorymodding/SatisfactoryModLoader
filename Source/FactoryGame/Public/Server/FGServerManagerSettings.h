// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSettings.h"
#include "FGServerManagerSettings.generated.h"

/**
 * 
 */
UCLASS( abstract )
class FACTORYGAME_API UFGServerManagerSettings : public UFGSettings
{
	GENERATED_BODY()
public:
	/** Helper to get server manager settings without going through UFGGlobalSettings */
	static UFGServerManagerSettings* Get();

	UPROPERTY( EditDefaultsOnly, Category = "Server manager settings" )
	TSubclassOf< class UFGBaseServerInteractionHandler > mServerInteractionHandlerClass;
};
