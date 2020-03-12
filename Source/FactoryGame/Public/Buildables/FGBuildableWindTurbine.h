// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

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

public:
	FORCEINLINE ~AFGBuildableWindTurbine() = default;
};