// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGCompassMaterialSettings.generated.h"

enum class ESelfDrivingLocomotiveError : uint8;
enum class ETrainStatus : uint8;
enum class EDockingStationStatus : uint8;
enum class EVehicleStatus : uint8;
class UMaterialInterface;
class UTexture2D;

/** Settings for compass materials used by representation system*/
UCLASS( Config = Game, DefaultConfig, meta = ( DisplayName = "Compass Material Settings" ) )
class FACTORYGAME_API UFGCompassMaterialSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Map" )
	TSoftObjectPtr<UMaterialInterface> mStampMaterial;

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Map" )
	TSoftObjectPtr<UMaterialInterface> mMarkerMaterial;
	
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Ping" )
	TSoftObjectPtr<UMaterialInterface> mPlayerPingCompassMaterial;

	/** Text used for localizing the "{0}m name of the player ping on the compass */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Ping" )
	FText mPlayerPingText;

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce" )
	TSoftObjectPtr<UMaterialInterface> mResourceCompassMaterial;

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce" )
	TSoftObjectPtr<UMaterialInterface> mFrackingNodeCompassMaterial;

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce" )
	TSoftObjectPtr<UMaterialInterface> mClusterResourceCompassMaterial;

	/** Text used for localizing the "{0}m name of the resource node on the compass */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce" )
	FText mResourceNodeDistanceToPlayerText;

	/** Material for the resource scanner ping effect to play in compass */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce|Ping" )
	TSoftObjectPtr<UMaterialInterface> mResourceScannerPingEffectMaterial;

	/** Size of the scanner ping effect on the compass, in screen space units */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce|Ping" )
	FVector2f mResourceScannerPingEffectImageSize{400.0f};

	/** Amount of time in seconds it takes for one loop of the resource scanner effect to play */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce|Ping" )
	float mResourceScannerPingEffectLoopTime{0.5f};

	/** Total amount of time in seconds the scanner ping effect should be shown on compass */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce|Ping" )
	float mResourceScannerPingEffectTotalTime{2.0f};

	/** The scale of the resource node icon on compass when it's the furthest away from the player possible */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce|Ping" )
	float mResourceCompassDistanceFarScale{0.5f};

	/** The scale of the resource node icon on compass when it's very close to the player */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce|Ping" )
	float mResourceCompassDistanceNearScale{1.5f};

	/** The maximum distance the player can be away from the resource node before considering it "far" away. */
	UPROPERTY( EditAnywhere, Config, Category = "Compass|Resouce|Ping" )
	float mResourceMaxCompassDistance{50000.0f};

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Vehicle")
	TSoftObjectPtr<UTexture2D> mWarningIcon;
	
	UPROPERTY( EditAnywhere, Config, Category= "Compass|Vehicle" )
	FLinearColor mWarningIconColor = FLinearColor( 0.783538f, 0.291771f, 0.057805f );

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Vehicle")
	TMap<EVehicleStatus, FLinearColor> mVehicleStatusWarningColors;

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Vehicle")
	TMap<EDockingStationStatus, FLinearColor> mDockingStationWarningColors;

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Vehicle")
	TMap<ETrainStatus, FLinearColor> mTrainStatusWarningColors;

	UPROPERTY( EditAnywhere, Config, Category = "Compass|Vehicle")
    TMap<ESelfDrivingLocomotiveError, FLinearColor> mTrainSelfDrivingErrorWarningColorOverrides;

	FORCEINLINE static const UFGCompassMaterialSettings* Get()
	{
		return GetDefault<UFGCompassMaterialSettings>();
	}
};
