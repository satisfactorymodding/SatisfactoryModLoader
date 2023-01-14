// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGActorRepresentation.h"
#include "FGMapCompassSettings.generated.h"

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
	
	class UFGWorldScannableData* GetWorldScannableData() const;
	
	class UFGWorldHeightData* GetWorldHeightData() const;

	UPROPERTY( EditAnywhere, config, Category = Compass, meta = ( ToolTip = "The distance in unreal units where a compass object with a corresponding compass view distance should be visible. -1 is infinite distance" ) )
	TMap<ECompassViewDistance, float> mCompassViewDistances;

	UPROPERTY( EditAnywhere, config, Category = "Map Data", meta = ( ToolTip = "" ) )
	float mLowestWorldLocation;

	UPROPERTY( EditAnywhere, config, Category = "Map Data", meta = ( ToolTip = "" ) )
	float mHighestWorldLocation;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TAssetPtr<UStaticMesh> mMapMarkerMesh;
	
	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TAssetPtr<UMaterialInterface> mMapMarkerMaterial;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	int32 mDefaultStampIconID;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	int32 mMigratedBeaconIconID;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	float mMapMarkerFadeOutDuration;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	float mMapMarkerObjectHeightOffset;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TAssetPtr<UStaticMesh> mHighlightedMarkerMesh;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	FVector mHighlightMarkerMeshScale;
	
	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TAssetPtr<UMaterialInterface> mHighlightedMarkerMaterial;

	UPROPERTY( EditAnywhere, config, Category = "Map Markers", meta = ( ToolTip = "" ) )
	TAssetPtr<class UNiagaraSystem> mHighlightedMarkerNiagaraSystem;

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
	TSoftObjectPtr<class UFGWorldScannableData> mWorldScannableData;

	UPROPERTY( EditAnywhere, config, Category = "World", meta = ( ToolTip = "" ) )
	TSoftObjectPtr<class UFGWorldHeightData> mWorldHeightData;

};