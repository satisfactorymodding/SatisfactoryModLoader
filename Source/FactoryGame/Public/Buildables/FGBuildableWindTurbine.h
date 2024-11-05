// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGBuildableWindTurbine.generated.h"

/**
 * Generates power from wind.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableWindTurbine : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
};
