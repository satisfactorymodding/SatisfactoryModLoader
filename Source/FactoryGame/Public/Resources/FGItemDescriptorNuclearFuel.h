// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Resources/FGItemDescriptor.h"
#include "FGItemDescriptorNuclearFuel.generated.h"

/**
 * Base descriptor for nuclear fuel.
 */
UCLASS()
class FACTORYGAME_API UFGItemDescriptorNuclearFuel : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGItemDescriptorNuclearFuel();
	
	/** @return The descriptor to use when the fuel is removed from the reactor (waste). */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|NuclearFuel" )
	static TSubclassOf< UFGItemDescriptor > GetSpentFuelClass( TSubclassOf< UFGItemDescriptorNuclearFuel > inClass );

	/** @return The amount of waste to create */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|NuclearFuel" )
	static int32 GetAmountWasteCreated( TSubclassOf< UFGItemDescriptorNuclearFuel > inClass );

private:
	/** The descriptor to use when the fuel is removed from the reactor (waste). */
	UPROPERTY( EditDefaultsOnly, Category = "Nuclear Fuel", meta = ( AddAutoJSON = true ) )
	TSubclassOf< UFGItemDescriptor > mSpentFuelClass;

	/** How much waste to produce */
	UPROPERTY( EditDefaultsOnly, Category = "Nuclear Fuel" )
	int32 mAmountOfWaste;
};
