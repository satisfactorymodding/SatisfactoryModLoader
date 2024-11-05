// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGNarrativeSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Narrative" ) )
class FACTORYGAME_API UFGNarrativeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UFGNarrativeSettings* Get() { return GetDefault<UFGNarrativeSettings>(); };

	/* The default value for how far away will other players hear a message */
	UPROPERTY( EditAnywhere, config, Category = Sharing )
	float mDefaultMessageSharingDistance = 1000.f;

	/* How many messages can be queued. If zero there is no queue limit */
	UPROPERTY( EditAnywhere, config, Category = Queue )
	int32 mQueueLimit = 0;

	/* Every time a message is triggered a cooldown will start running. Some message will not be played if triggered while this cooldown is active. */
	UPROPERTY( EditAnywhere, config, Category = Cooldown, meta=(Units="s") )
	float mMessageCooldown = 600.0f;
};
