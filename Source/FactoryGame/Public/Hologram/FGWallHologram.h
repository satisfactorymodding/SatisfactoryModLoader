// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGFactoryBuildingHologram.h"
#include "FGWallHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGWallHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGWallHologram();

	virtual void BeginPlay() override;

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

private:
	/** Width of the wall, from the default buildable. */
	float mWidth;

	/** Height of the wall, from the default buildable. */
	float mHeight;

	/** Ratios for the snapping zones, how much of the wall to hit for snap to either direction. */
	float mSnapSidesHitZoneRatio = 0.2f;
	float mSnapBottomHitZoneRatio = 0.2f;

	class AFGBuildableWall* mUpgradeTarget = nullptr;

public:
	FORCEINLINE ~AFGWallHologram() = default;
};
