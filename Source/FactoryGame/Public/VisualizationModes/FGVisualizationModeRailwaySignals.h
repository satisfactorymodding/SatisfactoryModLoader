// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGVisualizationMode.h"
#include "FGVisualizationModeRailwaySignals.generated.h"

UCLASS()
class FACTORYGAME_API UFGVisualizationModeRailwaySignals : public UFGVisualizationMode
{
	GENERATED_BODY()
public:
	// Begin UFGVisualizationMode interface
	virtual void BeginMode_Implementation() override;
	virtual void EndMode_Implementation() override;
	// End UFGVisualizationMode interface
};
