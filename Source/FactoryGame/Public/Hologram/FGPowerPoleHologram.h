// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "../FGCircuitConnectionComponent.h"
#include "FGPowerPoleHologram.generated.h"

/**
* Hologram for power poles.
*/
UCLASS()
class FACTORYGAME_API AFGPowerPoleHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	//Begin hologram interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	//End hologram interface

	/** Get the connections the wires snap to. */
	FORCEINLINE UFGCircuitConnectionComponent* GetSnapConnection() const { return mSnapConnection; }



private:
	/** The connection wires snap to, used when placing a pole automatically. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mSnapConnection;

	class AFGBuildablePowerPole* mUpgradeTarget = nullptr;

public:
	FORCEINLINE ~AFGPowerPoleHologram() = default;
};
