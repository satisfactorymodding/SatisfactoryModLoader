// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "ItemAmount.h"
#include "FGConsumablesConsumedDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGConsumablesConsumedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

    TMap< TSubclassOf< class UFGConsumableDescriptor >, int32 > GetItemAmount() const { return mConsumablesConsumedCount; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The amount of the given consumables that should have been consumed up for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TMap< TSubclassOf< class UFGConsumableDescriptor >, int32 > mConsumablesConsumedCount;
	
};
