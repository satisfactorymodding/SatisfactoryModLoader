// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGRecipeCategoryBuiltDependency.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGRecipeCategoryBuiltDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
public:
	const TArray< TSubclassOf< class UFGBuildCategory > >& GetCategories() const { return mCategories; }
	
#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The types of categories an actor has to belong to in order to trigger this dependency. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	TArray< TSubclassOf< class UFGBuildCategory > > mCategories;
};
