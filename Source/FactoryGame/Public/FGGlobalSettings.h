// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Object.h"
#include "FGGlobalSettings.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, config = Engine, defaultconfig )
class FACTORYGAME_API UFGGlobalSettings : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGGlobalSettings* GetGlobalSettingsClassCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGResourceSettings* GetResourceSettingsCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGFactorySettings* GetFactorySettingsCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGDropPodSettings* GetDropPodSettingsCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGHardDriveSettings* GetHardDriveSettingsCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGEnvironmentSettings* GetEnvironmentSettingsCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGSubsystemClasses* GetSubsystemClassesCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGSignSettings* GetSignSettingsCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGIconLibrary* GetIconLibraryCDO();

	UFUNCTION( BlueprintPure, Category = "Settings" )
	static class UFGServerManagerSettings* GetServerManagerSettingsCDO();

protected:
	/** Settings for resources */
	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGResourceSettings > mResourceSettings;

	/** Settings for resources */
	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGFactorySettings > mFactorySettings;
	
	/** Settings for drop pods */
	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGDropPodSettings > mDropPodSettings;

	/** Settings for Hard Drive Research */
	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGHardDriveSettings > mHardDriveSettings;

	/** Settings for drop pods */
	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGEnvironmentSettings > mEnvironmentSettings;

	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGSubsystemClasses > mSubsystemClasses;

	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGSignSettings > mSignSettings;

	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGIconLibrary > mIconLibrary;

	/** Settings for the server manager, which lives on the client */
	UPROPERTY( EditDefaultsOnly, Category = "Settings" )
	TSubclassOf< class UFGServerManagerSettings > mServerManagerSettings;

	/** Default class for specifying the settings class */
	UPROPERTY( config, noclear )
	FSoftClassPath mGlobalSettingsClassName;

	/** The actual class */
	static TSubclassOf< UFGGlobalSettings > mGlobalSettingsClass;
};
