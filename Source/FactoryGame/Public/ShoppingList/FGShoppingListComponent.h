// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "ItemAmount.h"
#include "Components/ActorComponent.h"
#include "FGShoppingListComponent.generated.h"

USTRUCT()
struct FACTORYGAME_API FShoppingListBlueprintEntry
{
	GENERATED_BODY()

	FShoppingListBlueprintEntry( const FString& inBlueprintName, int32 inAmount ) :
		BlueprintName( inBlueprintName ),
		Amount( inAmount )
	{}

	FShoppingListBlueprintEntry(){}
	
	UPROPERTY( SaveGame )
	FString BlueprintName = "";
	
	UPROPERTY( SaveGame )
	int32 Amount = 0;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FShoppingListRecipeEntry
{
	GENERATED_BODY()

	FShoppingListRecipeEntry( TSubclassOf<class UFGRecipe> inRecipeClass, int32 inAmount ) :
		RecipeClass( inRecipeClass ),
		Amount( inAmount )
	{}

	FShoppingListRecipeEntry(){}
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	TSubclassOf<class UFGRecipe> RecipeClass = nullptr;
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	int32 Amount = 0;
};

// Shopping list class to move away code from bloated player state
// @todok2 This can use some cleaning up.
UCLASS( BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGShoppingListComponent : public UActorComponent, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	static UFGShoppingListComponent* GetShoppingListComponent( const class APlayerController* playerController );
	
	UFGShoppingListComponent();

	/** Used for copying data between player states */
	void CopyShoppingListComponent( const UFGShoppingListComponent* otherShoppingListComponent );
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	TArray<class UFGShoppingListObject*> GetShoppingListObjects();
	TArray<class UFGShoppingListObject*> GetShoppingListObjects_Slow();
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	UFGShoppingListObject* GetShoppingListObjectFromClass( TSubclassOf<UObject> objectClass, bool& out_result );
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	UFGShoppingListObject* GetShoppingListObjectFromObject( UObject* object, bool& out_result );
	
	UFUNCTION( BlueprintCallable )
	TArray< FItemAmount > GetShoppingListCost() const;
	TArray< FItemAmount > GetShoppingListCost_Slow() const;
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void SetShoppingListObject( class UFGShoppingListObject* shoppingListObject );

	// UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	// void UpdateShoppingListFromClass( TSubclassOf<UObject> objectClass, int32 diff );
	// UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	// void UpdateShoppingListFromObject( UObject* object, int32 diff );

	void RemoveRecipeFromShoppingList( TSubclassOf< class UFGRecipe > recipeClass, int32 amountToRemove );
	void RemoveBlueprintFromShoppingList( const FString& blueprintName, int32 amountToRemove );
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void ClearShoppingList();

	// Use only for migration
	void MigrateShoppingList( TArray< FShoppingListRecipeEntry > recipeEntries ); 
	
protected:
	
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

private:
	class UFGShoppingListObjectRecipe* Internal_GetShoppingListObjectFromRecipe( TSubclassOf<class UFGRecipe> recipe );
	class UFGShoppingListObjectBlueprint* Internal_GetShoppingListObjectFromBlueprint( class UFGBlueprintDescriptor* blueprintDescriptor );
	class UFGShoppingListObject* Internal_AddUniqueShoppingListObjectFromRecipe( TSubclassOf<class UFGRecipe> recipe, int32 amount );
	void Internal_AddOrReplaceShoppingListObjectFromRecipe( TSubclassOf<class UFGRecipe> recipe, int32 amount );
	class UFGShoppingListObject* Internal_AddUniqueShoppingListObjectFromBlueprint( class UFGBlueprintDescriptor* blueprintDescriptor, int32 amount );
	void Internal_AddOrReplaceShoppingListObjectFromBlueprint( class UFGBlueprintDescriptor* blueprintDescriptor, int32 amount );

	void Internal_RemoveShoppingListObjectFromRecipe( TSubclassOf<class UFGRecipe> recipe );
	void Internal_RemoveShoppingListObjectFromBlueprint( class UFGBlueprintDescriptor* blueprintDescriptor );
	
	void SetNumBlueprintsInShoppingList( class UFGShoppingListObjectBlueprint* shoppingListObjectBlueprint );
	UFUNCTION( Server, Reliable )
	void Server_SetNumBlueprintsInShoppingList( const FString& blueprintName, int32 totalAmount );
	
	void SetNumRecipeClassInShoppingList( class UFGShoppingListObjectRecipe* shoppingListObjectRecipe );
	UFUNCTION( Server, Reliable )
	void Server_SetNumRecipeClassInShoppingList( TSubclassOf< class UFGRecipe > recipeClass, int32 totalAmount );
	UFUNCTION( Server, Reliable )
	
	void Server_EmptyShoppingList();
	
	void BroadcastShoppingListUpdated();

	bool OwnerHasAuthority();
	bool OwnerHasLocalNetOwner();
	
	UFUNCTION()
	void OnRep_ShoppingListBlueprints();
	void SetupInitalShoppingListObjectForBlueprints();
	
	UFUNCTION()
	void OnRep_ShoppingListRecipes();
	void SetupInitalShoppingListObjectForRecipes();

private:
	// Used for UI representation to expose a more scalable system
	UPROPERTY( Transient )
	TArray< class UFGShoppingListObject* > mShoppingListObjects;

	// Underlying Shopping list data. Separated for different types.
	// We could look into saving and replicating mShoppingListObjects as subobjects but this feels cheaper network wise
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ShoppingListBlueprints )
	TArray< FShoppingListBlueprintEntry > mShoppingListBlueprints;
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ShoppingListRecipes )
	TArray< FShoppingListRecipeEntry > mShoppingListRecipes;

	// Silly quickfix for not knowing when blueprints are replicated.
	int32 mRetryCount = 0;
		
};
