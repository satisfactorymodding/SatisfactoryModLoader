// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGJumpPadHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGJumpPadHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
	
public:
	AFGJumpPadHologram();

	// Begin AActor interface
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

protected:
	void DisplayNearbyJumpPadTrajectories();

private:
	// The radius in which we looks for other jump pad's trajectories to display.
	UPROPERTY( EditDefaultsOnly, Category="JumpPad")
	float mTrajectorySearchRadius;

	// How frequently we update the display of nearby trajectories (For performance reasons).
	UPROPERTY( EditDefaultsOnly, Category = "JumpPad" )
	float mTrajectorySearchFrequency;

	float mTrajectorySearchTimer;

	UPROPERTY()
	TArray<class AFGBuildableJumppad*> mNearbyJumpPads;
};
