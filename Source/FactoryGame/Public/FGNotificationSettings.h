// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGNotificationSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Notifications" ) )
class FACTORYGAME_API UFGNotificationSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGNotificationSettings* Get() { return GetDefault<UFGNotificationSettings>(); };
public:
	UPROPERTY( EditAnywhere, config, Category = "Timings", meta = ( ToolTip = "If the autosave interval is longer than the timing each of these timings will trigger a autosave notifications when there is that amount of time left on the auto save timer " ) )
	TArray<float> mAutoSaveNotificationTimings;

public:
	FORCEINLINE ~UFGNotificationSettings() = default;
};
