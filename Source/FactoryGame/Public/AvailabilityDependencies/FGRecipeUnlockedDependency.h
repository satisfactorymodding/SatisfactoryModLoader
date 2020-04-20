// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGRecipeUnlockedDependency.generated.h"

/**
 * Dependency that's met if we have unlocked all the given recipes
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGRecipeUnlockedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	void GetRecipes( TArray< TSubclassOf< class UFGRecipe > >& out_recipes ) const;

protected:
	/** The recipes that should have been unlocked for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGRecipe > > mRecipes;

	/** Do we need to have unlocked all of the recipes to or is it enough with just one of them */
	UPROPERTY( EditDefaultsOnly )
	bool mRequireAllRecipesToBeUnlocked;


public:
	FORCEINLINE ~UFGRecipeUnlockedDependency() = default;
};
