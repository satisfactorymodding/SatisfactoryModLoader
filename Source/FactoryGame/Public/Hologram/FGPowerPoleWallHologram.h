// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPowerPoleHologram.h"
#include "FGPowerPoleWallHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPowerPoleWallHologram : public AFGPowerPoleHologram
{
	GENERATED_BODY()
public:
	AFGPowerPoleWallHologram();

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	// End AFGHologram interface

private:
	/** Are you allowed to rotate this attachment on the walls surface. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	bool mIsRotationAllowed;

	/** Whether or not it is possible to snap to the ceiling. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	bool mCanSnapToFoundationCeiling;

	/** Whether or not it is possible to snap to the side of foundations. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	bool mCanSnapToFoundationSide;

	/** Snapping offset of this attachment on the walls surface. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	FVector2D mSnapOffset;

	/** Distance to inset the hologram when attaching to a foundation. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	float mFoundationSnappingInset;

	/** Whether or not we are currently snapping to a ceiling, used to move the power connection mesh so it doesn't clip with the ceiling. */
	bool mIsOnCeiling;
};
