// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

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

public:
	FORCEINLINE ~UFGNoneDescriptor() = default;
};
