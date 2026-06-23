// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGVehiclePathValidation.h"
#include "Engine/DataAsset.h"
#include "FGVehiclePathPreset.generated.h"

class UFGHologramBuildModeDescriptor;

UCLASS( BlueprintType )
class FACTORYGAME_API UFGVehiclePathPreset : public UDataAsset
{
	GENERATED_BODY()
public:
	UFGVehiclePathPreset();

	/** Path validation config for this vehicle path preset */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Vehicle" )
	FVehiclePathValidationConfig mPathValidationConfig;

	/** Version number for this path preset. If path validation config changed for this preset, bump this to re-validate the paths in existing save games */
	UPROPERTY( EditAnywhere, Category = "Vehicle" )
	int32 mPathPresetVersionNumber{0};
};
