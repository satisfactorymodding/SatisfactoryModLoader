// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGWallAttachmentHologram.generated.h"

/**
 * Hologram for wall attachments, like wall mounts for conveyors and power.
 */
UCLASS()
class FACTORYGAME_API AFGWallAttachmentHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGWallAttachmentHologram();

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	virtual int32 GetRotationStep() const override;
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

	/** The rotation step for when rotating, if 0 then use the default granularity. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	int32 mRotationStep;

	/** Snapping offset of this attachment on the walls surface. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	FVector2D mSnapOffset;

	/** Distance to inset the hologram when attaching to a foundation. */
	UPROPERTY( EditDefaultsOnly, Category = "Wall Attachment" )
	float mFoundationSnappingInset;
};
