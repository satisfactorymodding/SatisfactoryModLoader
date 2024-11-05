// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAvailabilityDependency.h"
#include "FGGamePhaseManager.h"
#include "FGGamePhaseReachedDependency.generated.h"

/**
 * Dependency that's met if we have reached or surpassed the given game phase. Tutorial need to be completed for this to ever return true.
 * If you need to check for tutorial steps you can use UFGCurrentTutorialStepDependency
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGGamePhaseReachedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	EGamePhase GetGamePhase() const{ return mGamePhase; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The game phase that should have been reached for this dependency to be met. NOTE: This dependency will never be met until tutorial is completed no matter what target phase you select */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TEnumAsByte< EGamePhase > mGamePhase;
	
	/** Only consider this dependency be met if we are currently in the selected phase. If true and we have surpassed the selected phase this dependency will not be considered met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	bool mOnlyAllowInSelectedPhase;
};
