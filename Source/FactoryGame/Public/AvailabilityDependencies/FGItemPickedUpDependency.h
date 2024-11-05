// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "ItemAmount.h"
#include "FGItemPickedUpDependency.generated.h"

/**
 * Dependency that's met if we have picked up all selected items at least once 
 * only items with mRememberPickUp set to true will be remembered when picked up
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGItemPickedUpDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;
	
	bool DoesItemAmountMatchDependency( const FItemAmount& totalAmountPickuped ) const;

	// Get the items needed to be pickuped
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	void GetItems( TArray< TSubclassOf< class UFGItemDescriptor > >& out_items ) const;
	// Get the items and amounts needed to be pickuped
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	void GetItemAmounts( TMap< TSubclassOf< class UFGItemDescriptor >, int32 >& out_items ) const;

#if WITH_EDITOR
	void Init( TArray< TSubclassOf< class UFGItemDescriptor > > items, bool requireAllItemsToBePickedUp );
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The items that should have been picked up for this dependency to be met, maps item class to amount */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TMap< TSubclassOf< class UFGItemDescriptor >, int32 > mItems;

	/** Do we need to have picked up all of the item classes or is it enough with just one of them */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	bool mRequireAllItemsToBePickedUp;

};
