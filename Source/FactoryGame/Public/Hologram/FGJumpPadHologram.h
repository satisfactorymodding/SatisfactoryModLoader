// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGFactoryHologram.h"
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
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

protected:
	void DisplayNearbyJumpPadTrajectories();

private:
	void OnTraceCompleted( const FTraceHandle& Handle, FOverlapDatum& Data );
	
private:
	// The radius in which we looks for other jump pad's trajectories to display.
	UPROPERTY( EditDefaultsOnly, Category="JumpPad")
	float mTrajectorySearchRadius;

	UPROPERTY()
	TArray<class AFGBuildableJumppad*> mNearbyJumpPads;

	FTraceHandle mTraceHandle;
	FOverlapDelegate mOverlapDelegate;
};
