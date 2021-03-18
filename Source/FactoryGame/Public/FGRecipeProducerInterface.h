// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGRecipeProducerInterface.generated.h"

/**
 * Interface to identify classes that can produce recipies, e.g. buildgun, manufacturer, workbench.
 * This makes them selectable as produced in, in the recipe and UI.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGRecipeProducerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGRecipeProducerInterface
{
	GENERATED_IINTERFACE_BODY()
};