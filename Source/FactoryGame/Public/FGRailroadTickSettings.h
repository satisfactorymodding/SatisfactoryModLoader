// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGRailroadTickSettings.generated.h"


UCLASS( Config = "Game", DefaultConfig, meta = ( DisplayName = "Railroad Tick") )
class FACTORYGAME_API UFGRailroadTickSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Maximum delta time allowed, longer deltas are clamped down or sub-stepped. */
	UPROPERTY( EditAnywhere, config, Category = "Factory Tick" )
	float mMaxDeltaTime{0.05f}; // 20 frames per second

	/** Max max number of substeps to use to compensate for a long delta time. */
	UPROPERTY(EditAnywhere, config, Category = "Factory Tick" )
	int32 mMaxSubsteps{3}; // Enough to compensate for up to 10 frames per second + a potential hitch
};
