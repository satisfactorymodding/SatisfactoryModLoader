// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGGenericBuildableHologram.h"
#include "FGWallAttachmentHologram.generated.h"

/**
 * Hologram for wall attachments, like wall mounts for conveyors and power.
 */
UCLASS()
class FACTORYGAME_API AFGWallAttachmentHologram : public AFGGenericBuildableHologram
{
	GENERATED_BODY()
public:
	AFGWallAttachmentHologram();

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance( const FVector& locationOffset ) override;
	// End AFGHologram interface
};
