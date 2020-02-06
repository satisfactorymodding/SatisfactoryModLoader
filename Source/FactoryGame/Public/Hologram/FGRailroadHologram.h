// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGFactoryHologram.h"
#include "../Buildables/FGBuildableRailroadTrack.h"
#include "FGRailroadHologram.generated.h"

/**
 * Hologram base for railroad buildings, stations, signals, switch controls etc. but not special cases like tracks, vehicles.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	// Begin AFGHologram interface
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End of AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual void CheckValidPlacement() override;
	// End of AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface
	
protected:
	/** Overload to also scroll the track direction we face when scrolling rotation. */
	int32 mScrollTrackDirection;

	/** The track position for this hologram. If valid this station has snapped to a track. */
	UPROPERTY()
	FRailroadTrackPosition mSnappedTrackPosition;
};
