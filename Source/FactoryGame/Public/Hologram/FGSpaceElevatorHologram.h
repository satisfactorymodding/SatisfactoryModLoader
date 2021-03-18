// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
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
