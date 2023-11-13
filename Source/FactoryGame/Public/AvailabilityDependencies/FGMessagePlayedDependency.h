// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGMessagePlayedDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGMessagePlayedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
    void GetMessages( TArray< TSubclassOf< class UFGMessageBase > >& out_messages ) const;

protected:
	/** The messages that should have been played for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGMessageBase > > mMessages;
	
};
