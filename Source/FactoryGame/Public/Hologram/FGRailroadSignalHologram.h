// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
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
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual void PreHologramPlacement( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool CanNudgeHologram() const override;
	// End AFGHologram Interface

protected:
	bool IsLocallyOwnedHologram() const;

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface

private:
	/** The track connection we snapped to. */
	UPROPERTY( Replicated, CustomSerialization )
	class UFGRailroadTrackConnectionComponent* mSnappedConnection;

	/** The track we snapped to. */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildableRailroadTrack* mSnappedRailroadTrack;

	/** The distance at which we snapped to the railroad track. */
	float mSnappedDistance;

	/** Whether or not to flip the snapped direction. */
	bool mFlipSnappedDirection;

	/** If we upgrade a signal to another type of signal, this is the signal we are replacing. */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildableRailroadSignal* mUpgradeTarget;
};
