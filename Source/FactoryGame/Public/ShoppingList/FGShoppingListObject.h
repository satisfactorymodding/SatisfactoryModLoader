// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
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
	UFUNCTION( BlueprintCallable )
	void ClearAmount();

	virtual void Native_OnAmountUpdated();

	virtual UObject* GetIdentifierObject() const;
	virtual void AddCost( TMap<TSubclassOf<class UFGItemDescriptor>, int32>& totalCost ) const;

protected:
	virtual FText Internal_GetShoppingListName() const { return FText::GetEmpty(); }
	
	int32 mAmount = 0;
	
};

UCLASS()
class FACTORYGAME_API UFGShoppingListObject_Class : public UFGShoppingListObject
{
	GENERATED_BODY()
public:
	void Init( TSubclassOf< class UObject > subClass, int32 amount );
	
	UFUNCTION( BlueprintCallable )
	void SetSubClass( TSubclassOf< class UObject > subClass );

	UFUNCTION( BlueprintPure )
	TSubclassOf< class UObject > GetSubclass() const { return mSubclass; }

	virtual UObject* GetIdentifierObject() const override;

	virtual void Native_OnAmountUpdated() override;
	
protected:
	virtual FText Internal_GetShoppingListName() const override;
	virtual void AddCost( TMap<TSubclassOf<class UFGItemDescriptor>, int32>& totalCost ) const override;
	
	UPROPERTY( Transient, BlueprintReadOnly, Meta = ( ExposeOnSpawn = "true" ) )
	TSubclassOf< class UObject > mSubclass;
	
};

UCLASS()
class FACTORYGAME_API UFGShoppingListObject_Object : public UFGShoppingListObject
{
	GENERATED_BODY()
public:
	void Init( UObject* object, int32 amount );
	
	UFUNCTION( BlueprintCallable )
	void SetObject( UObject* object );

	UFUNCTION( BlueprintPure )
	UObject* GetObject() const { return mObject; }

	virtual UObject* GetIdentifierObject() const override;

	virtual void Native_OnAmountUpdated() override;
	
protected:
	virtual FText Internal_GetShoppingListName() const override;
	virtual void AddCost( TMap<TSubclassOf<class UFGItemDescriptor>, int32>& totalCost ) const override;
	
	UPROPERTY( Transient, BlueprintReadOnly, Meta = ( ExposeOnSpawn = "true" ) )
	UObject* mObject;
	
};

