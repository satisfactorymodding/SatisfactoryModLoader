// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGFactoryTickSettings.generated.h"


UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Factory Tick") )
class FACTORYGAME_API UFGFactoryTickSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Maximum delta time allowed, longer deltas are clamped down or substepped. */
	UPROPERTY( EditAnywhere, config, Category = "Factory Tick" )
	float mMaxFactoryDeltaTime;

	/** Max max number of substeps to use to compensate for a long delta. */
	UPROPERTY(EditAnywhere, config, Category = "Factory Tick" )
	int32 mMaxSubsteps;
};
