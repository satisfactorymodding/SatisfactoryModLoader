// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGMessageInterruptedDependency.generated.h"

/**
 * This a special trigger for messages that should be played when one message interrupts another message
 * This doesn't override any base functions and cant really be checked against. This is more a tag than a dependency
 * but since the message triggers are based on UFGAvailabilityDependency derived classes I continued with the same approach here
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGMessageInterruptedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

#if WITH_EDITOR
	virtual FString ToString() const override;
#endif
	
};
