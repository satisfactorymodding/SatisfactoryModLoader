// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "Templates/SubclassOf.h"
#include "FGItemFailedToSinkDependency.generated.h"

/**
 * Dependency that's met if we fail to sink a specific item for the first time
 * 
 * NOTE: Added as a narrative trigger and no other functionality is implemented
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGItemFailedToSinkDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
    TArray<TSubclassOf< class UFGItemDescriptor >> GetItemsFailedToSink() const{ return mItemsFailedToSink; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif
	
protected:
	/** If any of these items failed to sink this dependency is considered met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TArray<TSubclassOf< class UFGItemDescriptor >> mItemsFailedToSink;
	
};
