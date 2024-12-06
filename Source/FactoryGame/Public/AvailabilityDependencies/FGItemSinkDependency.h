// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "Templates/SubclassOf.h"
#include "FGItemSinkDependency.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGItemSinkDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	UFGItemSinkDependency();

	const TArray< TSubclassOf< class UFGItemDescriptor > >& GetItemClasses() const { return mItemClasses; }
	
#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif
	
protected:
	/** If any of these items are sunk then the dependency is triggered */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TArray< TSubclassOf< class UFGItemDescriptor > > mItemClasses;
};
