// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGWildCardDescriptor.generated.h"

/**
 * Not a real resource, used to indicate a wild card in sorting rules.
 */
UCLASS()
class FACTORYGAME_API UFGWildCardDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGWildCardDescriptor();
};
