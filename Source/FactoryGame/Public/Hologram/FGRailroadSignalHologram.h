// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGRailroadSignalHologram.generated.h"

/**
 * Hologram for placing railroad signals.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadSignalHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGRailroadSignalHologram();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End AFGHologram Interface

protected:
	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface

private:
	/** The track connection we snapped to. */
	UPROPERTY()
	class UFGRailroadTrackConnectionComponent* mSnappedConnection;
};
