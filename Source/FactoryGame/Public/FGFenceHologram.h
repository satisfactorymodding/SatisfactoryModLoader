// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGWallHologram.h"
#include "FGFenceHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGFenceHologram : public AFGWallHologram
{
	GENERATED_BODY()
public:
	AFGFenceHologram();

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

protected:
	/** The rotation step for when rotating, if 0 then use the default granularity. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	int32 mRotationStep;
};
