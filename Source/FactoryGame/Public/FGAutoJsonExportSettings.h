// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGAutoJsonExportSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Auto JSON Export Settings" ) )
class FACTORYGAME_API UFGAutoJsonExportSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGAutoJsonExportSettings* Get() { return GetDefault<UFGAutoJsonExportSettings>(); };
public:
	UPROPERTY( EditAnywhere, config, Category = "Custom Classes" )
	TArray<TSubclassOf<UObject>> mCustomClasses;
};
