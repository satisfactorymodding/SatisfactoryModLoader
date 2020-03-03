// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/AssetUserData.h"
#include "FGMinimapCaptureActor.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGHeightWaterUserData : public UAssetUserData
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGHeightWaterUserData() = default;
};

UCLASS()
class FACTORYGAME_API UFGHeightFoliageUserData : public UAssetUserData
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGHeightFoliageUserData() = default;
};

UCLASS()
class FACTORYGAME_API UFGHeightHideUserData : public UAssetUserData
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGHeightHideUserData() = default;
};

USTRUCT()
struct FACTORYGAME_API FFGHeightData
{
	GENERATED_BODY()

	FFGHeightData() :
		minZ( -9999999.0f ),
		maxZ( 9999999.0f ),
		lowestZ( 9999999.0f ),
		highestZ( -9999999.0f )
	{
	}

	float minZ;
	float maxZ;
	float lowestZ;
	float highestZ;

	TArray< float > zHitLocations;
	TArray< int32 > noHitIndexes;
	TArray< int32 > deepHitIndexes;

	void AddHitLocation( int32 index, float zValue )
	{
		zHitLocations[ index ] = zValue;
		lowestZ = FMath::Clamp(FMath::Min( zValue, lowestZ ), minZ, maxZ);
		highestZ = FMath::Max( zValue, highestZ );
	}

public:
	FORCEINLINE ~FFGHeightData() = default;
};

UENUM()
enum class EHeightDataType : uint8
{
	HDT_NONE,
	HDT_TERRAIN,
	HDT_WATER,
	HDT_FOLIAGE
};

UCLASS()
class FACTORYGAME_API AFGMinimapCaptureActor : public ASceneCapture2D
{
	GENERATED_BODY()
	
public:
	AFGMinimapCaptureActor();

	virtual void BeginPlay() override;

	/** Returns the map area texture that has been specified on this capture actor */
	UFUNCTION( BlueprintCallable, Category = "Minimap" )
	FORCEINLINE class UFGMapAreaTexture* GetMapAreaTexture() const { return mMapAreaTexture; }

#if WITH_EDITOR
	/** This function traces all over the level to find height info that can be used when we draw the minimap */
	UFUNCTION( BlueprintCallable, Category = "Minimap Height", meta = ( CallInEditor = "true" ) )
	void ExportHeightData();

private:

	void CalculateHeightData( FVector upperLeftWorld, const FVector xStepVect, const FVector yStepVect, const TArray< AActor* >& ignoreActors, FFGHeightData& out_terrainHeightData, FFGHeightData& out_waterHeightData, FFGHeightData& out_foliageHeightData );
	EHeightDataType GetTypeFromHitResult( const FHitResult& hitResult );
	void SetNotHitLocationsToLowestValue( FFGHeightData& out_heightData );
	void SetDeepHitLocationsToLowestValue( FFGHeightData& out_heightData );
	void ClampToBinaryValues( FFGHeightData& out_heightData );
	void CalculateDepthBetween( FFGHeightData& out_heightData, const FFGHeightData& otherHeightData, float maxDepth, float bufferMultiplier );
	TArray<FColor> CreatePixelArray( FFGHeightData &heightData );
	TArray<TArray<FColor>> CreateLayeredPixelArray( FFGHeightData &heightData, int32 numberOfLayers );
#endif

public:

#if WITH_EDITORONLY_DATA
	/** Do we want the foliage to be considered for the height data generation? */
	UPROPERTY( EditInstanceOnly, Category = "Minimap Height" )
	bool mIncludeFoliage;

	/** Should we ignore the userdata set on static meshes, all static meshes will be considered for the height data */
	UPROPERTY( EditInstanceOnly, Category = "Minimap Height" )
	bool mIgnoreUserData;

	/** Divides the terrain height map into the given amount of layers*/
	UPROPERTY( EditInstanceOnly, Category = "Minimap Height" )
	int32 mLayersForTerrain;

	/** Show depth on the water map */
	UPROPERTY( EditInstanceOnly, Category = "Minimap Height" )
	bool mShowDepthOnWaterMap;

	/** The max water depth considered, everything deeper than this will be clamped to this value */
	UPROPERTY( EditInstanceOnly, Category = "Minimap Height" )
	float mWaterMaxDepth = 1000.0f;

	/** Decides how big the buffer between "no water"-areas and the deepest water-area is */
	UPROPERTY( EditInstanceOnly, Category = "Minimap Height" )
	float mWaterDepthBufferMultiplier = 1.1f;

	UPROPERTY( EditInstanceOnly, Category = "Minimap Height" )
	int32 mHeightDataResolution;


#endif

protected:

	/* The areas defined as by this texture */
	UPROPERTY( EditInstanceOnly, Category = "Minimap" )
	UFGMapAreaTexture* mMapAreaTexture;
	

public:
	FORCEINLINE ~AFGMinimapCaptureActor() = default;
};
