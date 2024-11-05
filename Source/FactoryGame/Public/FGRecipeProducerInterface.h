// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "FGRecipeProducerInterface.generated.h"

class UFGItemDescriptor;

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

	/** Called on the Class Default Object of the Recipe Producer to determine which Item Descriptor it maps to. Should not modify the object. */
	UFUNCTION( BlueprintNativeEvent, Category = "Recipe Producer Interface" )
	TSubclassOf<UFGItemDescriptor> GetRecipeProducerItemDescriptor( UObject* WorldContext ) const;
};