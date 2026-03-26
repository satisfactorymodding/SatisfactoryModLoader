// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGPluginDeveloperSettings.generated.h"

/**
 * Base class that should be used instead of UDeveloperSettings when declaring new config settings in plugins for them
 * to save to the correct configuration file when edited through Project Settings/Editor Preferences and not to the project defaults
 * Config name for such settings must match the name of the plugin. You should not use base inis such as Engine or Game for plugin-specific content
 * Example:
 * UCLASS(DefaultConfig, Config = "MyCoolPlugin")
 * class MYCOOLPLUGIN_API UMCPGameplaySettings : public UFGPluginDeveloperSettings { ... }
 */
UCLASS(Abstract)
class FACTORYGAME_API UFGPluginDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	// Begin UObject interface
	virtual FString GetDefaultConfigFilename() const override;
	// End UObject interface

	// Begin UDeveloperSettings interface
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	// End UDeveloperSettings interface
};
