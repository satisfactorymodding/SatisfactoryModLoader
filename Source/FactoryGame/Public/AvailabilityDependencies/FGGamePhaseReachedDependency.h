// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGGamePhaseManager.h"
#include "FGGamePhaseReachedDependency.generated.h"

/**
 * Dependency that's met if we have reached the given game phase tutorial is completed because there is no phase for tutorial
 * so checking for the first game phase "Establishing Phase" without the tutorial check is like checking if we started the game
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGGamePhaseReachedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()
	
public:
	bool AreDependenciesMet( UObject* worldContext ) const override;

	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	EGamePhase GetGamePhase() const{ return mGamePhase; }

protected:
	/** The game phase that should have been reached for this dependency to be met. NOTE: This dependency will never be met until tutorial is completed no matter what target phase you select */
	UPROPERTY( EditDefaultsOnly )
	TEnumAsByte< EGamePhase > mGamePhase;

};
