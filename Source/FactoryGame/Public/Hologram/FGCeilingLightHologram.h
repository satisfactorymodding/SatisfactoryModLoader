// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "FGCeilingLightHologram.generated.h"

/**
 * Hologram for the ceiling lights.
 */
UCLASS()
class FACTORYGAME_API AFGCeilingLightHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGCeilingLightHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void CheckValidPlacement() override;
	virtual void CheckClearance( const FVector& locationOffset ) override;
	// End AFGHologram interface
};
