// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGItemDescriptor.h"
#include "UFGItemDescriptorPowerBoosterFuel.generated.h"

/**
 * Base descriptor for power booster fuel.
 */
UCLASS()
class FACTORYGAME_API UFGItemDescriptorPowerBoosterFuel : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	/** @return The amount of additional boost. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|PowerBoosterFuel" )
	static float GetBoostPercentage( TSubclassOf< UFGItemDescriptorPowerBoosterFuel > inClass );

	/** @return The duration of the boost [seconds]. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|PowerBoosterFuel" )
	static float GetBoostDuration( TSubclassOf< UFGItemDescriptorPowerBoosterFuel > inClass );

private:
	/**
	 * Additional amount this booster fuel should boost the power production in the network.
	 * Example: 0.1 is a boost of 10%, 1.0 is a boost of 100%.
	 * If multiple boosters are added, the percentages are accumulated linearly.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Booster Fuel" )
	float mBoostPercentage;

	/** For how long can we apply this boost [seconds]. */
	UPROPERTY( EditDefaultsOnly, Category = "Booster Fuel" )
	float mBoostDuration;
};
