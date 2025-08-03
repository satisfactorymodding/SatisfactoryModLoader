// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildable.h"
#include "FGBuildablePoleBase.generated.h"

/**
 * Base class for all support poles in the game.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePoleBase : public AFGBuildable
{
	GENERATED_BODY()
public:
	virtual bool ShouldBeConsideredForBase_Implementation() override;

	virtual bool ShouldShowCenterGuidelinesForHologram( const class AFGHologram* hologram ) const override;
};
