// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGAvailabilityDependency.generated.h"

/**
 * Base class for generic dependency system to put dependency on availability of certain objects in the game
 * for example a schematic may be dependent on another schematic being purchased, a research tree may be dependent on that you have picked up an item of a certain class
 */
UCLASS( DefaultToInstanced, abstract, editinlinenew, Meta = ( AutoJSON = true ) )
class FACTORYGAME_API UFGAvailabilityDependency : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintPure )
	virtual bool AreDependenciesMet( UObject* worldContext ) const;

public:
	FORCEINLINE ~UFGAvailabilityDependency() = default;
};
