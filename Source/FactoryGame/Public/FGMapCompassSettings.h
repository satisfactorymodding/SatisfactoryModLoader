// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGActorRepresentation.h"
#include "Engine/DeveloperSettings.h"
#include "FGMapCompassSettings.generated.h"

USTRUCT()
struct FCompassCardinalDirection
{
	GENERATED_BODY()

	/** The cardinal direction for this icon */
	UPROPERTY( EditAnywhere, Config, Category = "Cardinal Direction" )
	FVector2f CardinalDirection{ForceInit};

	/** Texture to use for displaying this cardinal direction */
	UPROPERTY( EditAnywhere, Config, Category = "Cardinal Direction" )
	TSoftObjectPtr<UTexture2D> CardinalDirectionTexture{};

	UPROPERTY( EditAnywhere, Config, Category = "Cardinal Direction" )
	float CompassHeightOffset{0.0f};

	UPROPERTY( EditAnywhere, Config, Category = "Cardinal Direction" )
	FVector2f ImageSize{};
};

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Map and Compass" ) )
class FACTORYGAME_API UFGMapCompassSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGMapCompassSettings* Get() { return GetDefault<UFGMapCompassSettings>(); };

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetMapMarkerMesh() const;

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetMapMarkerDefaultMaterial() const;

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetHighlightedMarkerMesh() const;

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetHighlightedMarkerMaterial() const;
	
	class UNiagaraSystem* GetHighlightedMarkerNiagaraSystem() const;
	
	class UFGWorldHeightData* GetWorldHeightData() const;

	UPROPERTY( EditAnywhere, config, Category = Compass, meta = ( ToolTip = "The distance in unreal units where a compass object with a corresponding compass view distance should be visible. -1 is infinite distance" ) )
	TMap<ECompassViewDistance, float> mCompassViewDistances;

	UPROPERTY( EditAnywhere, config, Category = "Map Data", meta = ( ToolTip = "" ) )
	float mLowestWorldLocation;

	UPROPERTY( EditAnywhere, config, Category = "Map Data", meta = ( ToolTip = "" ) )
	float mHighestWorldLocation;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<UStaticMesh> mMapMarkerMesh;
	
	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<UMaterialInterface> mMapMarkerMaterial;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	int32 mDefaultStampIconID;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	int32 mMigratedBeaconIconID;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	float mMapMarkerFadeOutDuration;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	float mMapMarkerObjectHeightOffset;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<UStaticMesh> mHighlightedMarkerMesh;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	FVector mHighlightMarkerMeshScale;
	
	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<UMaterialInterface> mHighlightedMarkerMaterial;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<class UNiagaraSystem> mHighlightedMarkerNiagaraSystem;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	FText mMapMarkerFailedToAddMessage;

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

	UPROPERTY( EditAnywhere, config, Category = "World", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<class UFGWorldHeightData> mWorldHeightData;

	/** Cardinal direction indicators to show on compass */
	UPROPERTY( EditAnywhere, Config, Category = "Compass" )
	TArray<FCompassCardinalDirection> mCompassCardinalDirections;

	/** Size of the single icon on the compass, in slate units. */
	UPROPERTY( EditAnywhere, Config, Category = "Compass" )
	FVector2f mCompassIconSize{ForceInit};
};