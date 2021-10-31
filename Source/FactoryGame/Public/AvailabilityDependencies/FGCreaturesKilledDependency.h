// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGCreaturesKilledDependency.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreaturesKilledDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	TMap< TSubclassOf< class AFGCreature >, int32 > GetCreaturesKilledCount() const { return mCreaturesKilledCount; }

protected:
	/** The amount of the given creatures that should have been killed for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TMap< TSubclassOf< class AFGCreature >, int32 > mCreaturesKilledCount;
};
