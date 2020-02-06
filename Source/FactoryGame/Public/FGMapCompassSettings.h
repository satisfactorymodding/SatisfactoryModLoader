#pragma once
#include "Engine/DeveloperSettings.h"
#include "UObject/Class.h"

#include "FGActorRepresentation.h"
#include "FGMapCompassSettings.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Map and Compass" ) )
class FACTORYGAME_API UFGMapCompassSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY( EditAnywhere, config, Category = Compass, meta = ( ToolTip = "The distance in unreal units where a compass object with a corresponding compass view distance should be visible. -1 is infinite distance" ) )
	TMap<ECompassViewDistance, float> mCompassViewDistances;

	UPROPERTY( EditAnywhere, config, Category = Map, meta = ( ToolTip = "" ) )
	float mLowestWorldLocation;

	UPROPERTY( EditAnywhere, config, Category = Map, meta = ( ToolTip = "" ) )
	float mHighestWorldLocation;

	UPROPERTY( EditAnywhere, config, Category = FogOfWar, meta = ( ToolTip = "", ClampMin = "0.0", ClampMax = "255.0", UIMin = "0", UIMax = "255.0" ) )
	float mFogOfWarUpperRangeMin;

	UPROPERTY( EditAnywhere, config, Category = FogOfWar, meta = ( ToolTip = "", ClampMin = "0.0", ClampMax = "255.0", UIMin = "0", UIMax = "255.0" ) )
	float mFogOfWarUpperRangeMax;
	
	UPROPERTY( EditAnywhere, config, Category = FogOfWar, meta = ( ToolTip = "", ClampMin = "1.0", ClampMax = "5.0", UIMin = "1.0", UIMax = "5.0" ) )
	float mFogOfWarGradientExpandValue;

	UPROPERTY( EditAnywhere, config, Category = FogOfWar, meta = ( ToolTip = "Enables the fog of war reveal calculations" ) )
	bool mEnableFogOfWarRevealCalculations;

	UPROPERTY( EditAnywhere, config, Category = FogOfWar, meta = ( ToolTip = "Enables the fog of war texture update" ) )
	bool mEnableFogOfWarTextureUpdates;

	UPROPERTY( EditAnywhere, config, Category = FogOfWar, meta = ( ToolTip = "" ) )
	bool mForceSingleThreadedCalculations;

};