// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableManufacturer.h"
#include "FGBuildableAutomatedWorkBench.generated.h"

/**
 * 
 */
UCLASS( Meta = (AutoJson = false) )
class FACTORYGAME_API AFGBuildableAutomatedWorkBench : public AFGBuildableManufacturer
{
	GENERATED_BODY()
public:
	/** Constructor */
	AFGBuildableAutomatedWorkBench();

	/** This function sets the filters on the input output inventories. */
	virtual void SetUpInventoryFilters() override;

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	
	/**
	* Helper function that actually removes ingredients from the manufacturers input.
	* This can differ between buildings (eg. Converters), so override if you need something special.
	* @note this function assumes the available ingredients are there and have been checked with CanProduce()
	*/
	virtual void Factory_ConsumeIngredients();

	/**
	 * The player can increase the manufacturing speed in the UI "minigame"
	 */
	UFUNCTION( BlueprintCallable, Category = "Automated WorkBench" )
	void SetManufacturingSpeed( float newManufacturingSpeed );

protected:
	virtual void CreateInventories() override;
public:
	/** Size of the input inventory for the workbench */
	UPROPERTY( EditDefaultsOnly, Category = "Automated WorkBench" )
	int32 mInputInventorySize;
};
