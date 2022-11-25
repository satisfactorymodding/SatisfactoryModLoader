// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGShoppingListObject.generated.h"

/**
 * 
 */
UCLASS( BlueprintType, Abstract )
class FACTORYGAME_API UFGShoppingListObject : public UObject
{
	GENERATED_BODY()

public:
	UFGShoppingListObject();

	UFUNCTION( BlueprintPure )
	FText GetShoppingListName() const { return Internal_GetShoppingListName(); }

	UFUNCTION( BlueprintPure )
	FString GetShoppingListNameAsString() const { return Internal_GetShoppingListName().ToString(); }

	UFUNCTION( BlueprintPure )
	FORCEINLINE int32 GetAmount() const { return mAmount; }

	UFUNCTION( BlueprintCallable )
	void SetAmount( int32 totalAmount );
	UFUNCTION( BlueprintCallable )
	void IncreaseAmount( int32 amountToAdd );
	UFUNCTION( BlueprintCallable )
	void DecreaseAmount( int32 amountToRemove );

	virtual void Native_OnAmountUpdated();

	virtual UObject* GetIdentifierObject() const;
	virtual void AddCost( TMap<TSubclassOf<class UFGItemDescriptor>, int32>& totalCost ) const;

protected:
	virtual FText Internal_GetShoppingListName() const { return FText::GetEmpty(); }
	
	int32 mAmount = 0;
	
};
