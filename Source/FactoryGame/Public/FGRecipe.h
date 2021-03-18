// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "ItemAmount.h"
#include "Hologram/HologramSplinePathMode.h"
#include "FGEventSubsystem.h"
#include "FGRecipe.generated.h"


/**
 * This is a class describing a recipe, subclass this in blueprint to make a new recipe.
 */
UCLASS( Blueprintable, Meta=(AutoJSON=true) )
class FACTORYGAME_API UFGRecipe : public UObject
{
	GENERATED_BODY()
public:
	UFGRecipe();

	// Begin UObject interface
#if WITH_EDITOR
	virtual bool CanEditChange( const FProperty* InProperty ) const override;
	virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
	// End UObject interface

	/** Get the display name for this recipe. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static FText GetRecipeName( TSubclassOf< UFGRecipe > inClass );

	/** Get the ingredients for this recipe. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static TArray< FItemAmount > GetIngredients( TSubclassOf< UFGRecipe > inClass );

	/** Get the products for this recipe. @todo remove unused allowChildRecipes. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static TArray< FItemAmount > GetProducts( TSubclassOf< UFGRecipe > inClass, bool allowChildRecipes = false );

	/** Returns this recipe item category. Either overridden or fetched from the produced item */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static TSubclassOf< UFGItemCategory > GetCategory( TSubclassOf< UFGRecipe > inClass );

	/** The order we want recipes in the manufacturing menu, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static float GetManufacturingMenuPriority( TSubclassOf< UFGRecipe > inClass );

	/** Get the base manufacturing duration for this recipe. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static float GetManufacturingDuration( TSubclassOf< UFGRecipe > inClass );

	/** Get the manual manufacturing duration. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static float GetManualManufacturingDuration( TSubclassOf< UFGRecipe > inClass );

	/** Get which buildings/or build gun this recipe can be used in. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static TArray< TSubclassOf< UObject > > GetProducedIn( TSubclassOf< UFGRecipe > inClass );

	/** True if this recipe can be produced in the game. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
    static bool HasAnyProducers( TSubclassOf< UFGRecipe > inClass );

	/** Can the given player afford the recipe. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static bool IsRecipeAffordable( class AFGCharacterPlayer* player, TSubclassOf< class UFGRecipe > recipe );

	/** Sort an array dependent on their name. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static void SortByName( UPARAM(ref) TArray< TSubclassOf< UFGRecipe > >& recipes );

	/** Sort an array dependent on their manufacturing menu priority. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static void SortByManufacturingMenuPriority( UPARAM( ref ) TArray< TSubclassOf< UFGRecipe > >& recipes );

	/** Get descriptor for recipe specified 
	* @note - This will only return the first product so recipes that produce more than one will only return the first in the array.
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static TSubclassOf< class UFGItemDescriptor > GetDescriptorForRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Returns the relevant events this recipe is present in. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
    static TArray< EEvents > GetRelevantEvents( TSubclassOf< UFGRecipe > inClass );

	/** Native accessors. */
	virtual FText GetDisplayName() const;
	void GetProducedIn( TArray< TSubclassOf< UObject > >& out_producedIn ) const;
	FORCEINLINE const TArray<FItemAmount>& GetProducts() const { return mProduct; }
	FORCEINLINE const TArray<FItemAmount>& GetIngredients() const { return mIngredients; }
	FORCEINLINE float GetManufacturingDuration() const { return mManufactoringDuration; }
	FORCEINLINE float GetManualManufacturingDuration() const { return mManufactoringDuration * mManualManufacturingMultiplier; }

	float GetPowerConsumptionConstant() const { return mVariablePowerConsumptionConstant; }
	float GetPowerConsumptionFactor() const { return mVariablePowerConsumptionFactor; }

#if WITH_EDITOR
	/** Sets the products produced from this recipe. Only for editor use */
	UFUNCTION( BlueprintCallable, Category = "Editor|Recipe" )
	static void SetProduct( TSubclassOf< UFGRecipe > recipe, TArray< FItemAmount > product );
#endif

	EHologramSplinePathMode GetLastSplineMode();
	void SetLastSplineMode( EHologramSplinePathMode mode );
public: // MODDING EDIT: protected -> public
	friend class FRecipeDetails;

	/** If we override the display name or get it from the first products item name. */
	UPROPERTY( meta=(NoAutoJson = true) )
	bool mDisplayNameOverride;

	/** Overridden name for this recipe, if mDisplayNameOverride is false the first product's item name is used. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe", meta = ( EditCondition = mDisplayNameOverride ) )
	FText mDisplayName;

	EHologramSplinePathMode mLastSplineMode;

	/** Ingredients needed to produce the products. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	TArray< FItemAmount > mIngredients;
	
	/** The products produced from this recipe. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	TArray< FItemAmount > mProduct;

	/** The overridden category. If not overridden we return the item category given by the produced item */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	TSubclassOf< class UFGItemCategory> mOverriddenCategory;
	 
	/** The order in the manufacturing menu is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	float mManufacturingMenuPriority;

	/** The time it takes to produce the output. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	float mManufactoringDuration;

	/** The time it takes to produce the output. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	float mManualManufacturingMultiplier;

	/** Defines where this recipe can be produced */
	UPROPERTY( EditDefaultsOnly, Meta = ( MustImplement = "FGRecipeProducerInterface", Category = "Recipe" ) )
	TArray< TSoftClassPtr< UObject > > mProducedIn;

	/** The events this recipe are present in */
	UPROPERTY( EditDefaultsOnly, Category = "Events" )
	TArray< EEvents > mRelevantEvents;

	/**
	*	Added to the variable power consumption. If the power-consumption curve's range (all possible output values)
	*	is normalized to [0.0, 1.0], this constant can be thought of as a power-consumption minimum.
	*	@note Only available if "Produced In" contains any class that supports variable power consumption.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Recipe|Variable Power" )
	float mVariablePowerConsumptionConstant;

	/**
	*	Multiplied into the variable power consumption. If the power-consumption curve's range (all possible output values)
	*	is normalized to [0.0, 1.0], this value added to the power-consumption constant can be thought of as a power-consumption maximum.
	*	@note Only available if "Produced In" contains any class that supports variable power consumption.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Recipe|Variable Power" )
	float mVariablePowerConsumptionFactor;
};
