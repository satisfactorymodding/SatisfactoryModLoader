// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGFactoryBuildingHologram.h"
#include "FGWalkwayHologram.generated.h"

/**
 * Hologram for walkways.
 */
UCLASS()
class FACTORYGAME_API AFGWalkwayHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGWalkwayHologram();

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface
	
	// Begin AFGFactoryBuildingHologram interface
	virtual void UpdateZoop() override;
	virtual void ConstructZoop( TArray<AActor*>& out_children ) override;
	virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const override;
	// End AFGFactoryBuildingHologram interface
	
	virtual void BeginPlay() override;

private:
	/** Defaults from the default buildable. */
	float mSize;
	float mElevation;
	FFoundationSideSelectionFlags mDisableSnapOn;

	/** Limits zooping to only lines */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mOnlyAllowLineZoop;
};
