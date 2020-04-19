// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "../FGGamePhaseManager.h"
#include "FGGamePhaseReachedDependency.generated.h"

/**
 * Dependency that's met if we have reached the given game phase
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
	/** The game phase that should have been reached for this dependency to be met */
	UPROPERTY( EditDefaultsOnly )
	TEnumAsByte< EGamePhase > mGamePhase;


public:
	FORCEINLINE ~UFGGamePhaseReachedDependency() = default;
};
