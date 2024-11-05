// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "ItemAmount.h"
#include "Components/ActorComponent.h"
#include "FGShoppingListComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnShoppingListUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnShoppingListCleared );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnShoppingListObjectAdded, class UFGShoppingListObject*, shoppingListObject );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnShoppingListObjectUpdated, class UFGShoppingListObject*, shoppingListObject );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnShoppingListObjectRemoved, class UFGShoppingListObject*, shoppingListObject );

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

/* Replaced by FShoppingListClassEntry. Kept it for save migration purposes */
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

USTRUCT( BlueprintType )
struct FACTORYGAME_API FShoppingListClassEntry
{
	GENERATED_BODY()

	FShoppingListClassEntry( TSubclassOf<UObject> inObjectClass, int32 inAmount ) :
		ObjectClass( inObjectClass ),
		Amount( inAmount )
	{}

	FShoppingListClassEntry(){}
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	TSubclassOf<class UObject> ObjectClass = nullptr;
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	int32 Amount = 0;
};

// Shopping list class to move away code from bloated player state
UCLASS( BlueprintType, ClassGroup=(Custom) )
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
	void GetShoppingListObjects( TArray<class UFGShoppingListObject*>& out_ShoppingListObjects );
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	UFGShoppingListObject* GetShoppingListObjectFromClass( TSubclassOf<UObject> objectClass, bool& out_result );
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	UFGShoppingListObject* GetShoppingListObjectFromObject( UObject* object, bool& out_result );
	
	UFUNCTION( BlueprintCallable )
	TArray< FItemAmount > GetShoppingListCost() const;
	
	void RemoveFromShoppingList( TSubclassOf< UObject > inClass );
	void RemoveAmountFromShoppingList( TSubclassOf< UObject > inClass, int32 amountToRemove );
	void RemoveBlueprintFromShoppingList( const FString& blueprintName, int32 amountToRemove );
	
	UFUNCTION( BlueprintCallable, Category = "Shopping List" )
	void ClearShoppingList();

	// Use only for migration
	void MigrateShoppingList( TArray< FShoppingListRecipeEntry > recipeEntries );
	
	void OnBlueprintRemoved( const FString& blueprintName );

	void UpdateShoppingListObjectBlueprint( class UFGShoppingListObject_Object* shoppingListObject_Object );
	void UpdateShoppingListObjectClass( class UFGShoppingListObject_Class* shoppingListObject_Class  );

	void UpdateShoppingList();

protected:
	
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

private:
//void UpdateShoppingListObjectBlueprint( class UFGShoppingListObjectBlueprint* shoppingListObjectBlueprint );
	UFUNCTION( Server, Reliable )
	void Server_SetNumBlueprintsInShoppingList( const FString& blueprintName, int32 totalAmount );
	
	//void UpdateShoppingListObjectRecipe( class UFGShoppingListObjectRecipe* shoppingListObjectRecipe );
	UFUNCTION( Server, Reliable )
	void Server_SetNumForClassInShoppingList( TSubclassOf< class UObject > inClass, int32 totalAmount );
	
	UFUNCTION( Server, Reliable )
	void Server_ClearShoppingList();
	
	void BroadcastShoppingListUpdated() const;

	bool OwnerHasAuthority() const;
	bool OwnerHasLocalNetOwner() const;
	
	UFUNCTION()
	void OnRep_ShoppingListBlueprints();
	UFUNCTION()
	void OnBlueprintAvailable( class UFGBlueprintDescriptor* blueprintDescriptor );

	void SetupInitialShoppingListObjectForBlueprints();
	void SetupBlueprintFromBlueprintEntry( class UFGBlueprintDescriptor* blueprintDescriptor, int32 amount );
	
	UFUNCTION()
	void OnRep_ShoppingListClassEntries();
	void SetupInitialShoppingListObjectForClassEntries();

public:
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Shopping List")
	FOnShoppingListUpdated mOnShoppingListUpdated;
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Shopping List")
	FOnShoppingListCleared mOnShoppingListCleared;
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Shopping List")
	FOnShoppingListObjectAdded mOnShoppingListObjectAdded;
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Shopping List")
	FOnShoppingListObjectUpdated mOnShoppingListObjectUpdated;
	UPROPERTY( BlueprintAssignable, BlueprintCallable, Category = "Shopping List")
	FOnShoppingListObjectRemoved mOnShoppingListObjectRemoved;

private:
	// Used for UI representation to expose a more scalable system
	UPROPERTY( Transient )
	TMap< UObject*, class UFGShoppingListObject* >mShoppingListObjects;

	// Underlying Shopping list data. Separated for different types.
	// We could look into saving and replicating mShoppingListObjects as subobjects but this feels cheaper network wise
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ShoppingListBlueprints )
	TArray< FShoppingListBlueprintEntry > mShoppingListBlueprints;
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ShoppingListClassEntries )
	TArray< FShoppingListClassEntry > mShoppingListClassEntries;
	/** Deprecated. Only kept for save compatability */
	UPROPERTY( SaveGame )
	TArray< FShoppingListRecipeEntry > mShoppingListRecipes;

	FTimerHandle mUpdateShoppingListHandle;
};
