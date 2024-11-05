// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGCentralStorageSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Central Storage" ) )
class FACTORYGAME_API UFGCentralStorageSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UFGCentralStorageSettings* Get() { return GetDefault<UFGCentralStorageSettings>(); };

	/** Affected in game by AFGUnlockSubssytem::mUnlockedCentralStorageUploadSpeedMultiplier */
	UPROPERTY( EditAnywhere, config, Category = "Central Storage", meta = ( ToolTip = "The time it takes to upload an item to central storage. Affects both player and container upload speed", Units="s" ) )
	float mDefaultTimeToUpload;

	/** Affects AFGUnlockSubssytem::mUnlockedCentralStorageUploadSpeedMultiplier in game */
	UPROPERTY( EditAnywhere, config, Category = "Central Storage", meta = ( ToolTip = "What is the maximum decrease in percentage we can unlock for mDefaultTimeToUpload", Units="Percent" ) )
	float mMaxTimeToUploadPercentageDecrease;

	/** Affected in game by AFGUnlockSubssytem::mUnlockedCentralStorageItemLimit */
	UPROPERTY( EditAnywhere, config, Category = "Central Storage", meta = ( ToolTip = "The number of item stacks we can have in the stockpile of each item class at the same time" ) )
	int32 mDefaultItemStackLimit;
	
};
