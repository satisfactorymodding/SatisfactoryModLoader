// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGSpaceElevatorHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGSpaceElevatorHologram : public AFGFactoryHologram
{
	GENERATED_BODY()	

	// Begin AFGHologram interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram interface
	
};
