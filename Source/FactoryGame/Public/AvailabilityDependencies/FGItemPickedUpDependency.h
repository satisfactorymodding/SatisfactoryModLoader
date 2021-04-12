// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
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

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	void GetItems( TArray< TSubclassOf< class UFGItemDescriptor > >& out_items ) const;

protected:
	/** The items that should have been picked up for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGItemDescriptor > > mItems;

	/** Do we need to have picked up all of the items to or is it enough with just one of them */
	UPROPERTY( EditDefaultsOnly )
	bool mRequireAllItemsToBePickedUp;

};
