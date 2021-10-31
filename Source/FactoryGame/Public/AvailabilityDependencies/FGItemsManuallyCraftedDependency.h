// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGItemsManuallyCraftedDependency.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGItemsManuallyCraftedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	TMap< TSubclassOf< class UFGItemDescriptor >, int32 > GetItemsManuallyCraftedCount() const { return mItemsManuallyCraftedCount; }

protected:
	/** The amount of the given items that should have been manually crafted for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TMap< TSubclassOf< class UFGItemDescriptor >, int32 > mItemsManuallyCraftedCount;
};
