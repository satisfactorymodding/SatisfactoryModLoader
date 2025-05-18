// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "FGElevatorFloorStopHologram.generated.h"


class AFGBuildableElevatorFloorStop;
class AFGBuildableElevator;
class AFGElevatorHologram;

UCLASS()
class FACTORYGAME_API AFGElevatorFloorStopHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGElevatorFloorStopHologram();

	//Begin Hologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void CheckValidPlacement() override;
	virtual bool CanNudgeHologram() const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual void ConfigureActor(AFGBuildable* inBuildable) const override;
	virtual void ConfigureComponents(AFGBuildable* inBuildable) const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual bool TryUpgrade(const FHitResult& hitResult) override;
	virtual int32 GetRotationStep() const override;
	//End Hologram Interface

private:
	friend class AFGElevatorHologram;

	// Only valid if we are a forced child of a constructing elevator
	UPROPERTY()
	TObjectPtr< AFGElevatorHologram > mParentElevatorHologram;

	// Only valid if we are a force child of constructing elevator
	UPROPERTY()
	int32 mChildIndex;

	// Either the elevator we snap to OR if we are a child of an elevator hologram this is assigned on construct of the ElevatorHologram
	UPROPERTY()
	TObjectPtr< AFGBuildableElevator> mOwningElevator;

	// To allow for rotation after placement we allow upgrades so as long as the player changes the rotation of the stop
	UPROPERTY()
	TObjectPtr< AFGBuildableElevatorFloorStop > mUpgradedFloorStop;
	
};