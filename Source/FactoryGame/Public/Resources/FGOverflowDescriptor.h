// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
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

public:
	FORCEINLINE ~UFGOverflowDescriptor() = default;
};
