// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "Templates/SubclassOf.h"
#include "FGProximityToItemDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGProximityToItemDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	TSubclassOf< class UFGItemDescriptor > GetItemClass() const { return mItemClass; } 
	bool GetItemAsResourceNode() const { return mItemAsResourceNode; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The item class that we care about getting close to */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TSubclassOf< class UFGItemDescriptor > mItemClass;

	/** Do we want to find the item as resource node? If false we look for placed single items */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	bool mItemAsResourceNode;
	
};
