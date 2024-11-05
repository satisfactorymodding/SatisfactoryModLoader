// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableHologram.h"

#include "FGPowerSwitchHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPowerSwitchHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGPowerSwitchHologram();
	
	// Begin AFGHologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual void ConfigureActor( AFGBuildable* inBuildable ) const override;
	// End AFGHologram Interface

private:
	/** Power switch we are upgrading */
	UPROPERTY()
	class AFGBuildableCircuitSwitch* mUpgradeTarget;
};
