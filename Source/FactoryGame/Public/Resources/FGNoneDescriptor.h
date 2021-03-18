// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGItemDescriptor.h"
#include "FGNoneDescriptor.generated.h"

/**
 * Not a real resource, used to indicate none in sorting rules.
 */
UCLASS()
class FACTORYGAME_API UFGNoneDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGNoneDescriptor();
};
