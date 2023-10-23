// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGResearchTreeUnlockedDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGResearchTreeUnlockedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	void GetResearchTrees( TArray< TSubclassOf< class UFGResearchTree > >& out_researchTrees ) const;

#if WITH_EDITOR
	void Init( TArray< TSubclassOf< class UFGResearchTree > > researchTrees, bool requireAllTreesToBeUnlocked );
#endif

protected:
	/** The research trees that should have been purchased for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSoftClassPtr< class UFGResearchTree > > mResearchTrees;

	/** Do we need to have unlocked all of the trees to met the dependency or is it enough with just one of them */
	UPROPERTY( EditDefaultsOnly )
	bool mRequireAllTreesToBeUnlocked;
	
};
