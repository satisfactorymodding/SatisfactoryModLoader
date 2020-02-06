// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "ItemAmount.h"
#include "FGRecipe.generated.h"


/**
 * This is a class describing a recipe, subclass this in blueprint to make a new recipe.
 */
UCLASS( Blueprintable, Meta=(AutoJSON=true) )
class FACTORYGAME_API UFGRecipe : public UObject
{
	GENERATED_BODY()

public:
	UFGRecipe() :
		mDisplayNameOverride( false ),
		mManufactoringDuration( 1.0f )
	{
	}

	/** Used to get the recipe name in blueprint. */
	UFUNCTION( BlueprintPure, Category = "Recipe" )
	static FText GetRecipeName( TSubclassOf< UFGRecipe > inClass );

	/** Used to get the ingredients in blueprint. @todo: Make return value a out value instead */
	UFUNCTION( BlueprintPure, Category = "Recipe" )
	static TArray< FItemAmount > GetIngredients( TSubclassOf< UFGRecipe > inClass );

	/** Used to get the products in blueprint. @todo: Make return value a out value instead, @todo remove unused allowChildRecipes. */
	UFUNCTION( BlueprintPure, Category = "Recipe" )
	static TArray< FItemAmount > GetProducts( TSubclassOf< UFGRecipe > inClass, bool allowChildRecipes = false );

	/** Used to get the manufacturing duration in blueprint. */
	UFUNCTION( BlueprintPure, Category = "Recipe" )
	static float GetManufacturingDuration( TSubclassOf< UFGRecipe > inClass );

	/** @todo: change return value to out variable. Used to get the produced in buildings in blueprint. */
	UFUNCTION( BlueprintPure, Category = "Recipe" )
	static TArray< TSubclassOf< UObject > > GetProducedIn( TSubclassOf< UFGRecipe > inClass );

	/** Sort a array dependent on their names */
	UFUNCTION( BlueprintCallable, Category = "Recipe" )
	static void SortByName( UPARAM(ref) TArray< TSubclassOf< UFGRecipe > >& recipes );

	/** Accessor to get the products that this recipe produces */
	FORCEINLINE const TArray<FItemAmount>& GetProducts() const { return mProduct; }

	/** Accessor to get the ingredients to this recipe */
	FORCEINLINE const TArray<FItemAmount>& GetIngredients() const { return mIngredients; }

	/** Accessor to get the where this recipe is produced in */
	void GetProducedIn( TArray< TSubclassOf< UObject > >& out_producedIn ) const;

	/** Accessor to get how long time this recipes takes to manufacture */
	FORCEINLINE float GetManufacturingDuration() const { return mManufactoringDuration; }

	/** Accessor to get the displayname of the recipe */
	virtual FText GetDisplayName() const;

	/** Used to get the products in blueprint. @todo Deprecated since 2018-10-23, but have been unused since MAM refactor. */
	UFUNCTION( BlueprintPure, Category = "Recipe", meta = ( DeprecatedFunction, DeprecationMessage = "MAM is rewritten, use the new system instead!" ) )
	static TArray< TSubclassOf< UFGRecipe > > GetRewardedRecipes( TSubclassOf< UFGRecipe > inClass ){ return TArray< TSubclassOf< UFGRecipe > >(); }

	/** Can the given player afford the recipe */
	UFUNCTION( BlueprintCallable, Category = "Recipe" )
	static bool IsRecipeAffordable( class AFGCharacterPlayer* player, TSubclassOf< class UFGRecipe > recipe );

protected:
	friend class FRecipeDetails;

	/** If we override the display name or get it from the first products item name. */
	UPROPERTY( meta=(NoAutoJson = true) )
	bool mDisplayNameOverride;

	/** Overridden name for this recipe, if mDisplayNameOverride is false the first product's item name is used. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe", meta = ( EditCondition = mDisplayNameOverride ) )
	FText mDisplayName;

	/** Ingredients needed to produce the products. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	TArray< FItemAmount > mIngredients;
	
	/** The products produced from this recipe. */
	UPROPERTY( EditDefaultsOnly, Category = "Rewards" )
	TArray< FItemAmount > mProduct;

	/** The time it takes to produce the output. */
	UPROPERTY( EditDefaultsOnly, Category = "Recipe" )
	float mManufactoringDuration;

	/** Defines where this recipe can be produced */
	UPROPERTY( EditDefaultsOnly, Meta = ( MustImplement = "FGRecipeProducerInterface", Category = "Recipe" ) )
	TArray< TSoftClassPtr< UObject > > mProducedIn;
};
