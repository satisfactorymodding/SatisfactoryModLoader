// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGVisualizationMode.h"
#include "FGVisualizationModeVehiclePaths.generated.h"

class UFGVehiclePathPreset;
struct FVehiclePathVisualizationHandle;
class AFGWheeledVehicle;

UCLASS()
class FACTORYGAME_API UFGVisualizationModeVehiclePaths : public UFGVisualizationMode
{
	GENERATED_BODY()
public:
	// Begin UFGVisualizationMode interface
	virtual void BeginMode_Implementation() override;
	virtual void EndMode_Implementation() override;
	// End UFGVisualizationMode interface
protected:
	/** Vehicle path preset to specifically visualize paths for. This will check path validity for that particular vehicle type */
	UPROPERTY( EditDefaultsOnly, Category = "Visualization Mode" )
	TObjectPtr<UFGVehiclePathPreset> mVehiclePathPreset;

	TSharedPtr<FVehiclePathVisualizationHandle> mPathVisualizationHandle;
};
