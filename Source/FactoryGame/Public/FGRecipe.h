// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "ItemAmount.h"
#include "Hologram/HologramSplinePathMode.h"
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

	/** Get the display name for this recipe. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static FText GetRecipeName( TSubclassOf< UFGRecipe > inClass );

	/** Get the ingredients for this recipe. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static TArray< FItemAmount > GetIngredients( TSubclassOf< UFGRecipe > inClass );

	/** Get the products for this recipe. @todo remove unused allowChildRecipes. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static TArray< FItemAmount > GetProducts( TSubclassOf< UFGRecipe > inClass, bool allowChildRecipes = false );

	/** Get the base manufacturing duration for this recipe. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static float GetManufacturingDuration( TSubclassOf< UFGRecipe > inClass );

	/** Get the manual manufacturing duration. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static float GetManualManufacturingDuration( TSubclassOf< UFGRecipe > inClass );

	/** Get which buildings/or build gun this recipe can be used in. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	static TArray< TSubclassOf< UObject > > GetProducedIn( TSubclassOf< UFGRecipe > inClass );

	/** Can the given player afford the recipe. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static bool IsRecipeAffordable( class AFGCharacterPlayer* player, TSubclassOf< class UFGRecipe > recipe );

	/** Sort an array dependent on their name. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static void SortByName( UPARAM(ref) TArray< TSubclassOf< UFGRecipe > >& recipes );

	/** Get descriptor for recipe specified */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	static TSubclassOf< class UFGItemDescriptor > GetDescriptorForRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Native accessors. */
	virtual FText GetDisplayName() const;
	void GetProducedIn( TArray< TSubclassOf< UObject > >& out_producedIn ) const;
	FORCEINLINE const TArray<FItemAmount>& GetProducts() const { return mProduct; }
	FORCEINLINE const TArray<FItemAmount>& GetIngredients() const { return mIngredients; }
	FORCEINLINE float GetManufacturingDuration() const { return mManufactoringDuration; }
	FORCEINLINE float GetManualManufacturingDuration() const { return mManufactoringDuration * mManualManufacturingMultiplier; }

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

	/** The time it takes to produce the output. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	float mManufactoringDuration;

	/** The time it takes to produce the output. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	float mManualManufacturingMultiplier;

	/** Defines where this recipe can be produced */
	UPROPERTY( EditDefaultsOnly, Meta = ( MustImplement = "FGRecipeProducerInterface", Category = "Recipe" ) )
	TArray< TSoftClassPtr< UObject > > mProducedIn;

public:
	FORCEINLINE ~UFGRecipe() = default;
};
