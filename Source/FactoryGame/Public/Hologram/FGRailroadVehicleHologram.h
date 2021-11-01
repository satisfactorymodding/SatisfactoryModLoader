// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGVehicleHologram.h"
#include "FGRailroadSubsystem.h"
#include "FGRailroadVehicleHologram.generated.h"

/**
 * Hologram for railroad vehicles, this snaps to train tracks and couple with each other.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadVehicleHologram : public AFGVehicleHologram
{
	GENERATED_BODY()
	
public:
	/** Do all custom initialization from mBuildClass here. */
	virtual void BeginPlay() override;

	// Begin AFGHologram interface
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End of AFGHologram interface

	// Begin Net Construction Messages
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	// End of Net Construction Messages 

protected:
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void CheckValidPlacement() override;
	// End of AFGHologram interface

	/** @copydoc AFGVehicleHologram::ConstructVehicle */
	virtual class AFGVehicle* ConstructVehicle( FNetConstructionID netConstructionID ) const override;
	
private:
	/** Find overlapping railroad vehicles/tracks. */
	class AFGRailroadVehicle* OverlapRailroadVehicle( const FTransform& boxTransform, const FVector& boxExtent ) const;
	
protected:
	/** Overload to also scroll the track direction we face when scrolling rotation. */
	int32 mScrollTrackDirection;

private:
	/** The length of our vehicle. */
	UPROPERTY()
	float mLength;

	/** The track position for this hologram. If valid this vehicle has snapped to a track. */
	UPROPERTY()
	FRailroadTrackPosition mTrackPosition;

	/** The snapped vehicle. */
	UPROPERTY()
	class AFGRailroadVehicle* mSnappedVehicle;
};
