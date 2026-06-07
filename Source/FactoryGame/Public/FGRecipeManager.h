// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
	
	/** Make a recipe available to the producers. */
	void AddAvailableRecipe( TSubclassOf< UFGRecipe > recipe );

	/** Makes multiple recipes available to the producers */
	void AddAvailableRecipes( TArray<TSubclassOf<UFGRecipe>> recipes );

	/** Makes multiple item descriptors available to the consumers */
	void AddAvailableItemDescriptors( const TArray<TSubclassOf<UFGItemDescriptor>>& itemDescriptors );
	/** Makes a single item descriptor available */
	void AddAvailableItemDescriptor( const TSubclassOf<UFGItemDescriptor>& itemDescriptor );
	
	/** Removes a list of recipes from the available list */
	void RemoveAvailableRecipes( const TArray<TSubclassOf<UFGRecipe>>& recipes );

	/** Gets all available recipes. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe", BlueprintPure = false )
	void GetAllAvailableRecipes( TArray< TSubclassOf< UFGRecipe > >& out_recipes ) const;

	/** Returns all available recipes as a reference */
	const TArray<TSubclassOf<UFGRecipe>>& GetAllAvailableRecipes() const { return mAvailableRecipes; }

	/** Returns an unsorted list of all item descriptors unlocked explicitly or through unlocked recipes. Ordering is not consistent between client and host */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	const TArray<TSubclassOf<UFGItemDescriptor>>& GetAllAvailableItemDescriptors() const { return mAllAvailableItemDescriptorsList; }

	/** Gets all recipes in the game, including recipes yet to be unlocked. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	const TArray<TSubclassOf<UFGRecipe>>& GetAllRecipes() const { return mAllRecipes; }

	/** Returns all item descriptors that can be unlocked in the game */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	const TArray<TSubclassOf<UFGItemDescriptor>>& GetAllItemDescriptors() const { return mAllItemDescriptors; }
	
	/** Gets all available Customization Recipes. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe", BlueprintPure = false )
	void GetAllAvailableCustomizationRecipes( TArray< TSubclassOf< UFGCustomizationRecipe > >& out_recipes ) const;

	/** Returns the customization recipe the specified customization desc belongs to, if any. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Recipe" )
	TSubclassOf< class UFGCustomizationRecipe > GetCustomizationRecipeFromDesc( TSubclassOf< class UFGFactoryCustomizationDescriptor > desc );

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

	/** Returns true if the given item descriptor is available, e.g. has a recipe that produces it or it has been explicitly unlocked */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Recipe" )
	bool IsItemDescriptorAvailable( TSubclassOf<UFGItemDescriptor> itemDescriptor ) const;

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

	/** Returns customization recipe associated with the given buildable recipe, or null */
	TSubclassOf<UFGCustomizationRecipe> FindMaterialCustomizationRecipeForBuildableRecipe( const TSubclassOf<UFGRecipe>& buildableRecipe ) const;

	/** Resets recipes to their defaults, also cleans up pre alpha save state. */
	void ResetAllRecipes();

	/** Debug */
	void Debug_DumpStateToLog() const;

	void RegisterReplicationComponent(class UFGRecipeManagerReplicationComponent* ReplicationComponent) { mReplicationComponents.Add(ReplicationComponent); }
	void UnregisterReplicationComponent(UFGRecipeManagerReplicationComponent* ReplicationComponent) { mReplicationComponents.Remove(ReplicationComponent); }

	void Internal_ReceivedInitialState(const TArray<TSubclassOf<UFGRecipe>>& allRecipes, const TArray<TSubclassOf<UFGItemDescriptor>>& allItemDescriptors, const TArray<TSubclassOf<UFGRecipe>>& initialAvailableRecipes, const TArray<TSubclassOf<UFGItemDescriptor>>& initialAvailableItemDescriptors);
	void Internal_ReceivedStateUpdate(const TArray<TSubclassOf<UFGRecipe>>& newAvailableRecipes, const TArray<TSubclassOf<UFGRecipe>>& removedRecipes, const TArray<TSubclassOf<UFGItemDescriptor>>& newAvailableItemDescriptors);

	/** Returns item descriptors that have been explicitly made available (not derived from recipe products) */
	FORCEINLINE const TArray<TSubclassOf<UFGItemDescriptor>>& GetExplicitlyAvailableItemDescriptors() const { return mAvailableItemDescriptors; }
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

	/** Evaluates newly unlocked recipes for the additions to the available buildings */
	void UpdatedDerivedAvailableRecipesData(const TArray<TSubclassOf<UFGRecipe>>& newAvailableRecipes);
	/** Steps through mAvailableRecipes and looks for buildings that we can build to add to mAvailableBuildings. This is a full rebuild. */
	void RebuildDerivedAvailableRecipesData();

	/** Functions to either rebuild a segment of available item descriptor lookup or the entire lookup */
	void UpdateAvailableItemDescriptorLookup(const TArray<TSubclassOf<UFGRecipe>>& newAvailableRecipes, const TArray<TSubclassOf<UFGItemDescriptor>>& newAvailableItemDescriptors);
	void RebuildAvailableItemDescriptorLookup();

	/** Finds every recipe available in the game and stores it in mAllRecipes. */
	void PopulateAllRecipesList();
private:
	/** All recipes that are available to the producers, i.e. build gun, workbench, manufacturers etc. */
	UPROPERTY( SaveGame )
	TArray<TSubclassOf<UFGRecipe>> mAvailableRecipes;

	/** Item descriptors that have been made explicitly available to the consumers */
	UPROPERTY( SaveGame )
	TArray<TSubclassOf<UFGItemDescriptor>> mAvailableItemDescriptors;

	TMultiMap< TSubclassOf< UFGItemDescriptor >, TSubclassOf< UFGRecipe > > mAvailableRecipesByProduct;
	TMultiMap< TSubclassOf< UFGItemDescriptor >, TSubclassOf< UFGRecipe > > mAvailableRecipesByIngredient;
	
	/** Every single recipe in the game */
	UPROPERTY( Transient )
	TArray<TSubclassOf<UFGRecipe>> mAllRecipes;

	/** Every single item descriptor in the game */
	UPROPERTY( Transient )
	TArray<TSubclassOf<UFGItemDescriptor>> mAllItemDescriptors;

	TMultiMap< TSubclassOf< UFGItemDescriptor >, TSubclassOf< UFGRecipe > > mAllRecipesByProduct;
	TMultiMap< TSubclassOf< UFGItemDescriptor >, TSubclassOf< UFGRecipe > > mAllRecipesByIngredient;

	/** All customization Recipes. A subset of all recipes for quicker customization look ups */
	UPROPERTY( Transient )
	TArray<TSubclassOf<UFGCustomizationRecipe>> mAvailableCustomizationRecipes;

	/** Set for quick contains checks on customization recipes */
	UPROPERTY( Transient )
	TSet<TSubclassOf<UFGCustomizationRecipe>> mAvailableCustomizationRecipesLookup;

	/** Maps buildable recipe to the material customization recipe associated with it */
	UPROPERTY( Transient )
	TMap<TSubclassOf<UFGRecipe>, TSubclassOf<UFGCustomizationRecipe>> mBuildableRecipeToMaterialCustomizationRecipeLookup;

	/** Maps customization descriptor to the recipes that produced them. This assumes one customization recipe per descriptor */
	UPROPERTY( Transient )
	TMap<TSubclassOf<UFGFactoryCustomizationDescriptor>, TSubclassOf<UFGCustomizationRecipe>> mCustomizationDescriptorToRecipeLookup;

	/** All buildings that are available to produce in build gun. Generated from mAvailableRecipes. */
	UPROPERTY( Transient )
	TArray< TSubclassOf< class AFGBuildable > > mAvailableBuildings;

	/** Mapping of buildings to their descriptors. Generated from mAvailableRecipes */
	UPROPERTY( Transient )
	TMap< TSubclassOf< class AFGBuildable >, TSubclassOf< class UFGBuildingDescriptor > > mBuildingToDescriptorLookup;

	UPROPERTY( Transient )
	TArray<TSubclassOf<UFGItemDescriptor>> mAllAvailableItemDescriptorsList;
	UPROPERTY( Transient )
	TSet<TSubclassOf<UFGItemDescriptor>> mAllAvailableItemDescriptorsLookup;

	/** Replication components currently listening for recipe additions and removals */
	UPROPERTY()
	TArray<TObjectPtr<class UFGRecipeManagerReplicationComponent>> mReplicationComponents;

	bool mHasPendingAvailableRecipeRequest = false;
	bool mHasPendingTotalRecipeRequest = false;
};

template< typename BuildingType >
TArray< TSubclassOf< BuildingType > > AFGRecipeManager::GetAvailableBuildingsOfType() const
{
	TArray< TSubclassOf< BuildingType > > result;

	for( const auto& building : mAvailableBuildings )
	{
		if( building->IsChildOf( BuildingType::StaticClass() ) )
		{
			result.Add( TSubclassOf< BuildingType >( building ) );
		}
	}
	
	return result;
}
