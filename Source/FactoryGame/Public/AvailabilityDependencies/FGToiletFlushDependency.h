// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "Templates/SubclassOf.h"
#include "FGToiletFlushDependency.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGToiletFlushDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	UFGToiletFlushDependency();
	
	TSubclassOf< class UFGItemDescriptor > GetFlushedItemClass() const { return mFlushedItemClass; }
	
#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** What item needs to be flushed in order to trigger this dependency, will trigger on any flushed item if unassigned. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	TSubclassOf< class UFGItemDescriptor > mFlushedItemClass;
};
