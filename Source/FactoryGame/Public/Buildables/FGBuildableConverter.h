// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGBuildableManufacturer.h"
#include "FGBuildableConverter.generated.h"

UCLASS( Blueprintable, Meta = (AutoJson=false) )
class FACTORYGAME_API AFGBuildableConverter : public AFGBuildableManufacturer
{
	GENERATED_BODY()

public:
	//Constructor-chan
	AFGBuildableConverter();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//@todo Converter can maybe use a recipe with the wildcard resource so the UI does not need to cast and take different path depending on if it's a converter or manufacturer, or move this to base.
	//Get number of input connections
	UFUNCTION( BlueprintCallable, Category = "Converter" )
	FORCEINLINE int32 GetNumberOfInputs() const { return mFactoryInputConnections.Num(); }

protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_CollectInput_Implementation() override;
	// End AFGBuildableFactory interface

	/** This function sets the filters on the input output inventories. */
	virtual void SetUpInventoryFilters() override;

	/**
	* Helper function that actually removes ingredients from the manufacturers input.
	* This can differ between buildings (eg. Converters), so override if you need something special.
	* @note this function assumes the available ingredients are there and have been checked with CanProduce()
	*/
	virtual void Factory_ConsumeIngredients() override;

	/**
	* Returns true if the required ingredients are in the input slots.
	* How this is checked can differ between buildings (eg. Converters), so override if you need something special.
	*/
	virtual bool HasRequiredIngredients() const override;

	/** Bound to mItemFilter to filter what items can be used in the item slots. */
	UFUNCTION()
	bool FilterIngredientClasses( TSubclassOf< UObject > object, int32 idx ) const;

	/** Setups the item filter without crashing */
	UFUNCTION()
	void SetupItemFilter();
protected:

	//Number of ingredients needed to consume to produce
	UPROPERTY( EditDefaultsOnly, Category = "Converter" )
	int32 mNumberOfIngredientsNeeded;

	// this little guy ensures that the input index for consuming ingredients keeps cycling across all inputs.
	// otherwise there could be a bias between which inputs are used across production cycles.
	int32 mPreservedInputIndex;

public:
	FORCEINLINE ~AFGBuildableConverter() = default;
};