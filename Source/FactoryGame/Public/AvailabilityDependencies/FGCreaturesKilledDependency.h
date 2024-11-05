// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "Templates/SubclassOf.h"
#include "FGCreaturesKilledDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGCreaturesKilledDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	TMap< TSubclassOf< class AFGCreature >, int32 > GetCreaturesKilledCount() const { return mCreaturesKilledCount; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The amount of the given creatures that should have been killed for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TMap< TSubclassOf< class AFGCreature >, int32 > mCreaturesKilledCount;
};
