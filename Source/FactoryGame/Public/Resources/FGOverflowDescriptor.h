// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGItemDescriptor.h"
#include "FGOverflowDescriptor.generated.h"

/**
 * Descriptor Rule. Will consider all items that cannot be placed for a given tick on their specified output.
 */
UCLASS()
class FACTORYGAME_API UFGOverflowDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGOverflowDescriptor();
protected:
	FORCEINLINE virtual bool Internal_CanItemBePickedup() const override { return false; }
};
