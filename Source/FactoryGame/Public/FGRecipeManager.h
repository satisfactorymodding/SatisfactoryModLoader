// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGGamePhaseManager.h"
#include "FGRecipeManager.generated.h"

class UFGRecipe;

/**
 * Handles everything to do with recipes in the game.
 */
UCLASS()
class FACTORYGAME_API AFGRecipeManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Get the game phase manager, this should always return something unless you call it really early. */
	static AFGRecipeManager* Get( UWorld* world );

	/** Get the game phase manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe", DisplayName = "GetRecipeManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGRecipeManager* Get( UObject* worldContext );

public:
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//@todounlock Make private and add schematics manager as a friend
	/** Make a recipe available to the producers. */
	void AddAvailableRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Gets all available recipes. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	void GetAllAvailableRecipes( TArray< TSubclassOf< UFGRecipe > >& out_recipes );

	/** Gets the available recipes for the given class, may not be null. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	void GetAvailableRecipesForProducer( TSubclassOf< UObject > forProducer, TArray< TSubclassOf< UFGRecipe > >& out_recipes );

	/** Gets the available and affordable recipes for the given class, may not be null. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	void GetAffordableRecipesForProducer( class AFGCharacterPlayer* player, TSubclassOf< UObject > forProducer, TArray< TSubclassOf< UFGRecipe > >& out_recipes );

	/** Is the past recipe available? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	bool IsRecipeAvailable( TSubclassOf< UFGRecipe > recipeClass );

	/** Is the given buildable available to build? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
    bool IsBuidlingAvailable( TSubclassOf< class AFGBuildable > buildableClass ) const;

	/** Find all recipes using the given item as an ingredient. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Recipe" )
	TArray< TSubclassOf< UFGRecipe > > FindRecipesByIngredient( TSubclassOf< UFGItemDescriptor > ingredient ) const;

	/** Find all recipes having the given item as an product. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Recipe" )
	TArray< TSubclassOf< UFGRecipe > > FindRecipesByProduct( TSubclassOf< UFGItemDescriptor > product ) const;

	/** Resets recipes to their defaults, also cleans up pre alpha save state. */
	void ResetAllRecipes();

	/** Debug */
	void Debug_DumpStateToLog() const;

private:
	/** Filters recipes for a given producer. */
	void FilterRecipesByProducer( const TArray< TSubclassOf< UFGRecipe > >& inRecipes, TSubclassOf< UObject > forProducer, TArray< TSubclassOf< UFGRecipe > >& out_recipes );

	/** Checks if a recipe is valid for addition to the available recipes list. */
	bool CanAddToAvailableRecipes( TSubclassOf< UFGRecipe > recipe ) const;

	/** Checks if a recipe is valid for addition depending on it relevant events  */
	bool ShouldAddRecipeByEvent( TSubclassOf< UFGRecipe > recipe ) const;

	/** Steps through mAvailableRecipes and looks for buildings that we can build to add to mAvailableBuildings */
	void PopulateAvailableBuildings();

	/** Called when mAvailableRecipes have been replicated. used to generate mAvailableBuildings on client */
	UFUNCTION()
    void OnRep_AvailableRecipes();
	
private:
	//MODDING EDIT: Expose to AModContentRegistry
	friend class AModContentRegistry;
	/** All recipes that are available to the producers, i.e. build gun, workbench, manufacturers etc. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_AvailableRecipes )
	TArray< TSubclassOf< UFGRecipe > > mAvailableRecipes;

	/** All buildings that are available to produce in build gun. Generated from mAvailableRecipes. */
	UPROPERTY( Transient )
	TArray< TSubclassOf< class AFGBuildable > > mAvailableBuildings;
};
