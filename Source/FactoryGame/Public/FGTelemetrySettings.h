// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/SaveGame.h"
#include "Misc/Guid.h"
#include "FGTelemetrySettings.generated.h"


/**
 * Save game object used for persistent telemetry settings.
 */
UCLASS()
class UFGTelemetrySettingsSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	/** Randomly generated, persistent identifier used to correlate data across multiple sessions. */
	UPROPERTY( SaveGame )
	FGuid mPersistentPlayerId;
};


/**
 * Helper for loading and saving persistent telemetry settings.
 * 
 * On desktop platforms, the settings are saved to a file in the save directory.
 * On console platforms, the settings are saved using a save slot.
 */
class FGTelemetrySettings
{
public:
	static UFGTelemetrySettingsSaveGame* LoadTelemetrySettings();
	static UFGTelemetrySettingsSaveGame* LoadOrCreateTelemetrySettings();
	
private:
	static bool SaveTelemetrySettings(UFGTelemetrySettingsSaveGame* settings );

	/**
	 * Populate default telemetry settings.
	 * 
	 * Note: This should only be called if we do not have a settings file to load.
	 *		 Calling this under any other circumstances can break data persistency.
	 */
	static UFGTelemetrySettingsSaveGame* LoadDefaultTelemetrySettings();
};
