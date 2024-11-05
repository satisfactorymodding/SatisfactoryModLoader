// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGBuildEffectSettings.generated.h"

class UFGMaterialEffect_Build;

/**
 * Default build effects used by most buildables
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Build Effects" ) )
class FACTORYGAME_API UFGBuildEffectSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGBuildEffectSettings* Get() { return GetDefault<UFGBuildEffectSettings>(); };
	
	/** What build effect to use when building this building */
	UPROPERTY( EditAnywhere, Config, Category = "Build Effects | Default" )
	TSoftClassPtr< UFGMaterialEffect_Build > mDefaultBuildEffect;

	/** What build effect to use when dismantling this building */
	UPROPERTY( EditAnywhere, Config, Category = "Build Effects | Default" )
	TSoftClassPtr< UFGMaterialEffect_Build > mDefaultDismantleEffect;

	/** Build effect that wire buildables use by default */
	UPROPERTY( EditAnywhere, Config, Category = "Build Effects | Wire" )
	TSoftClassPtr< UFGMaterialEffect_Build > mWireBuildEffect;

};
