// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGVisualizationModeDescriptor.generated.h"

class UFGVisualizationMode;

UCLASS( Abstract )
class FACTORYGAME_API UFGVisualizationModeDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGVisualizationModeDescriptor();

	/** Returns the visualization mode class from the descriptor */
	UFUNCTION( BlueprintPure, Category = "Visualization Mode" )
	static TSubclassOf<UFGVisualizationMode> GetVisualizationModeClass( const TSubclassOf<UFGVisualizationModeDescriptor>& descriptor );
protected:
	/** Visualization mode that this descriptor describes */
	UPROPERTY( EditDefaultsOnly, Category = "Visualization Mode" )
	TSubclassOf<UFGVisualizationMode> mVisualizationModeClass;
};
