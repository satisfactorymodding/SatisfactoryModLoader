// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "ShoppingList/FGShoppingListObject.h"
#include "FGShoppingListObjectBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGShoppingListObjectBlueprint : public UFGShoppingListObject
{
	GENERATED_BODY()
public:
	void Init( class UFGBlueprintDescriptor* blueprintDescriptor, int32 amount );
	
	UFUNCTION( BlueprintCallable )
	void SetBlueprintDescriptor( class UFGBlueprintDescriptor* blueprintDescriptor );

	UFUNCTION( BlueprintPure )
	UFGBlueprintDescriptor* GetBlueprintDescriptor() const;

	virtual UObject* GetIdentifierObject() const override;

protected:
	virtual FText Internal_GetShoppingListName() const override;
	virtual void AddCost( TMap<TSubclassOf<class UFGItemDescriptor>, int32>& totalCost ) const override;

	UPROPERTY( Transient, BlueprintReadOnly, Meta = ( ExposeOnSpawn = "true" ) )
	UFGBlueprintDescriptor* mBlueprintDescriptor;
	
};
