// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGResearchTree.h"
#include "FGResearchTreeProgressionDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGResearchTreeProgressionDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	TMap< TSubclassOf< class UFGResearchTree >, TEnumAsByte<EResearchTreeStatus> > GetResearchTreeData() const { return mResearchTrees; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The research trees and the status they should be in for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TMap< TSubclassOf< class UFGResearchTree >, TEnumAsByte<EResearchTreeStatus> > mResearchTrees;

	/** Do we need to match all tree with the given status to met the dependency or is it enough with just one of them */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	bool mRequireAllTreesToBeMatched;
	
};
