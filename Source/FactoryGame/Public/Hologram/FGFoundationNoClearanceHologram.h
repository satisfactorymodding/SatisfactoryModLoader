// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGFoundationHologram.h"
#include "FGFoundationNoClearanceHologram.generated.h"

/**
 * Hax to get the cheaty corners back.
 */
UCLASS()
class FACTORYGAME_API AFGFoundationNoClearanceHologram : public AFGFoundationHologram
{
	GENERATED_BODY()
public:
	// Begin FGHologram
	virtual void CheckClearance() override;
	// End FGHologram
};
