// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGItemsManuallyCraftedDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGItemsManuallyCraftedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	TMap< TSubclassOf< class UFGItemDescriptor >, int32 > GetItemsManuallyCraftedCount() const { return mItemsManuallyCraftedCount; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The amount of the given items that should have been manually crafted for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TMap< TSubclassOf< class UFGItemDescriptor >, int32 > mItemsManuallyCraftedCount;
};
