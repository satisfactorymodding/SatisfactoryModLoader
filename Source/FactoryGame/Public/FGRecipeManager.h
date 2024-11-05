// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGRemoteCallObject.h"
#include "FGGamePhaseManager.h"
#include "FGRecipeManager.generated.h"

class UFGRecipe;
class UFGCustomizationRecipe;
class UFGBuildingDescriptor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnRecipeAvailableDelegate, TSubclassOf<UFGRecipe>, recipeClass );


UCLASS()
class FACTORYGAME_API UFGRecipeRCO : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGRecipeRemoteCallObject = false;

	UFUNCTION( Server, Reliable )
	void Server_RequestAvailableRecipeUpdate( const int32& currentIndex );

	UFUNCTION( Client, Reliable )
	void Client_RespondAvailableRecipeUpdate( const TArray< TSubclassOf< UFGRecipe > >& recipes );
	
	UFUNCTION( Server, Reliable )
	void Server_RequestAllRecipeUpdate( const int32& currentIndex );

	UFUNCTION( Client, Reliable )
	void Client_RespondAllRecipeUpdate( const TArray< TSubclassOf< UFGRecipe > >& recipes );
	
};


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
	virtual void BeginPlay() override;
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

	/** Gets all recipes in the game, including recipes yet to be unlocked. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	FORCEINLINE TArray< TSubclassOf< UFGRecipe > > const& GetAllRecipes() const { return mAllRecipes; }
	
	/** Gets all available Customization Recipes. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	void GetAllAvailableCustomizationRecipes( TArray< TSubclassOf< UFGCustomizationRecipe > >& out_recipes );

	/** Gets the available recipes for the given class, may not be null. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	void GetAvailableRecipesForProducer( TSubclassOf< UObject > forProducer, TArray< TSubclassOf< UFGRecipe > >& out_recipes );

	/** Gets the available and affordable recipes for the given class, may not be null. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	void GetAffordableRecipesForProducer( class AFGCharacterPlayer* player, TSubclassOf< UObject > forProducer, TArray< TSubclassOf< UFGRecipe > >& out_recipes );

	/** Is the past recipe available? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	bool IsRecipeAvailable( TSubclassOf< UFGRecipe > recipeClass ) const;

	/** Is the provided customization recipe available? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	bool IsCustomizationRecipeAvailable( TSubclassOf< UFGCustomizationRecipe > recipeClass ) const;

	/** Is the given buildable available to build? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
    bool IsBuildingAvailable( const TSubclassOf< class AFGBuildable > buildableClass ) const;

	/** Gets a list of available buildings inheriting from a certain buildable class. */
	template< typename BuildingType >
	TArray< TSubclassOf< BuildingType > > GetAvailableBuildingsOfType() const;

	/** Attempts to find the descriptor for the given building class */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	TSubclassOf< UFGBuildingDescriptor > FindBuildingDescriptorByClass( TSubclassOf< AFGBuildable > buildable ) const;

	/** Find all recipes using the given item as an ingredient. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Recipe" )
	TArray< TSubclassOf< UFGRecipe > > FindRecipesByIngredient( TSubclassOf< UFGItemDescriptor > ingredient, bool onlyAvailableRecipes = true, bool availableFirst = true ) const;

	/** Find all recipes having the given item as an product. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Recipe" )
	TArray< TSubclassOf< UFGRecipe > > FindRecipesByProduct( TSubclassOf< UFGItemDescriptor > product, bool onlyAvailableRecipes = true, bool availableFirst = true ) const;

	/** Resets recipes to their defaults, also cleans up pre alpha save state. */
	void ResetAllRecipes();

	/** Debug */
	void Debug_DumpStateToLog() const;

	
	UFUNCTION()
	void NotifyGameStateReadyOnClient();

public:
	/** Called when the provided recipe becomes available. Called for both normal recipes and customization recipes. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Recipe" )
	FFGOnRecipeAvailableDelegate mOnRecipeAvailable;
	
private:
	void OnSubsystemsValid();
	
	/** Filters recipes for a given producer. */
	void FilterRecipesByProducer( const TArray< TSubclassOf< UFGRecipe > >& inRecipes, TSubclassOf< UObject > forProducer, TArray< TSubclassOf< UFGRecipe > >& out_recipes );

	/** Checks if a recipe is valid for addition to the available recipes list. */
	bool CanAddToAvailableRecipes( TSubclassOf< UFGRecipe > recipe ) const;

	/** Checks if a recipe is valid for addition depending on it relevant events  */
	bool ShouldAddRecipeByEvent( TSubclassOf< UFGRecipe > recipe ) const;

	/** Steps through mAvailableRecipes and looks for buildings that we can build to add to mAvailableBuildings */
	void PopulateAvailableBuildings();

	/** Finds every recipe available in the game and stores it in mAllRecipes. */
	void PopulateAllRecipesList();

	void Internal_FindRecipesByIngredient( TSubclassOf< UFGItemDescriptor > ingredient, const TArray< TSubclassOf< UFGRecipe > >& recipeList, TArray< TSubclassOf< UFGRecipe > >& out_recipes, bool ignoreUniqueCheck = true ) const;
	void Internal_FindRecipesByProduct( TSubclassOf< UFGItemDescriptor > product, const TArray< TSubclassOf< UFGRecipe > >& recipeList, TArray< TSubclassOf< UFGRecipe > >& out_recipes, bool ignoreUniqueCheck = true ) const;

	UFUNCTION()
	void OnRep_NumAvailableRecipes();

	UFUNCTION()
	void OnRep_NumTotalRecipes();

	
private:
	friend class UFGRecipeRCO;
	
	/** All recipes that are available to the producers, i.e. build gun, workbench, manufacturers etc. */
	UPROPERTY( SaveGame )
	TArray< TSubclassOf< UFGRecipe > > mAvailableRecipes;

	/** Property to track whether a client should request an update of available recipes */
	UPROPERTY(ReplicatedUsing=OnRep_NumAvailableRecipes )
	int32 mNumAvailableRecipes;
	
	/** Every single recipe in the game. */
	UPROPERTY( Transient )
	TArray< TSubclassOf< UFGRecipe > > mAllRecipes;

	/** Property to track whether a client should request an update of available recipes */
	UPROPERTY(ReplicatedUsing=OnRep_NumTotalRecipes )
	int32 mNumAllRecipes;

	/** All customization Recipes. A subset of all recipes for quicker customization look ups */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< UFGCustomizationRecipe > > mAvailableCustomizationRecipes;

	/** All buildings that are available to produce in build gun. Generated from mAvailableRecipes. */
	UPROPERTY( Transient )
	TArray< TSubclassOf< class AFGBuildable > > mAvailableBuildings;

	/** Mapping of buildings to their descriptors. Generated from mAvailableRecipes */
	UPROPERTY( Transient )
	TMap< TSubclassOf< class AFGBuildable >, TSubclassOf< class UFGBuildingDescriptor > > mBuildingToDescriptorLookup;

	bool mHasPendingAvailableRecipeRequest = false;
	bool mHasPendingTotalRecipeRequest = false;
};

template< typename BuildingType >
TArray< TSubclassOf< BuildingType > > AFGRecipeManager::GetAvailableBuildingsOfType() const
{
	TArray< TSubclassOf< BuildingType > > result;

	for( const auto building : mAvailableBuildings )
	{
		if( building->IsChildOf( BuildingType::StaticClass() ) )
		{
			result.Add( TSubclassOf< BuildingType >( building ) );
		}
	}
	
	return result;
}
