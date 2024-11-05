// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGItemDescriptor.h"
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
protected:
	FORCEINLINE virtual bool Internal_CanItemBePickedup() const override { return false; }
};
