// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGGamePhaseManager.h"
#include "FGLockSpaceElevatorShipmentDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGLockSpaceElevatorShipmentDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Dependency" )
	EGamePhase GetGamePhase() const{ return mGamePhase; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** The game phase that should have been locked for this dependency to be met */
	UPROPERTY( EditDefaultsOnly, Category="Dependency" )
	TEnumAsByte< EGamePhase > mGamePhase;
	
};
