// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Object.h"
#include "FGGlobalSettings.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, config = Engine, defaultconfig )
class FACTORYGAME_API UFGGlobalSettings : public UObject
{
	GENERATED_BODY()

public:
	/** Called during startup of factorygame module */
	static void Initialize();

	/** Called during shutdown of factorygame module */
	static void Shutdown();

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

	/** Default class for specifying the settings class */
	UPROPERTY( config, noclear )
	FSoftClassPath mGlobalSettingsClassName;

	/** The actual class */
	static TSubclassOf< UFGGlobalSettings > mGlobalSettingsClass;
};
