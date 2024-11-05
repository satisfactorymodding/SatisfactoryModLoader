// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGSpaceElevatorFullyBuiltDependency.generated.h"

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGSpaceElevatorFullyBuiltDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

#if WITH_EDITOR
	virtual FString ToString() const override;
#endif
	
};
