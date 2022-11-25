// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "ShoppingList/FGShoppingListObject.h"
#include "FGShoppingListObjectRecipe.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGShoppingListObjectRecipe : public UFGShoppingListObject
{
	GENERATED_BODY()
public:
	void Init( TSubclassOf< class UFGRecipe > recipe, int32 amount );
	
	UFUNCTION( BlueprintCallable )
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

	UFUNCTION( BlueprintPure )
	TSubclassOf< class UFGRecipe > GetRecipe() const { return mRecipe; }

	virtual UObject* GetIdentifierObject() const override;
	
protected:
	virtual FText Internal_GetShoppingListName() const override;
	virtual void AddCost( TMap<TSubclassOf<class UFGItemDescriptor>, int32>& totalCost ) const override;
	
	UPROPERTY( Transient, BlueprintReadOnly, Meta = ( ExposeOnSpawn = "true" ) )
	TSubclassOf< class UFGRecipe > mRecipe;
	
};
