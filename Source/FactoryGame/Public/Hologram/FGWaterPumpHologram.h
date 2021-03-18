// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Hologram/FGResourceExtractorHologram.h"
#include "FGWaterPumpHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGWaterPumpHologram : public AFGResourceExtractorHologram
{
	GENERATED_BODY()
	
	AFGWaterPumpHologram();

public:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface

protected:
	// Begin AFGResourceExtractorHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void TrySnapToExtractableResource( const FHitResult& hitResult, FVector& newHitLocation ) override;
	void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End AFGResourceExtractorHologram Interface

	/**
	 * Check if this hologram meets minimum depth requirements.
	 */
	void CheckMinimumDepth();

protected:
	UPROPERTY()
	const class AFGBuildableWaterPump* mDefaultWaterPump = nullptr;

};
