// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
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

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The recipes that should have been unlocked for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TArray< TSubclassOf< class UFGRecipe > > mRecipes;

	/** Do we need to have unlocked all of the recipes to or is it enough with just one of them */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	bool mRequireAllRecipesToBeUnlocked;

};
