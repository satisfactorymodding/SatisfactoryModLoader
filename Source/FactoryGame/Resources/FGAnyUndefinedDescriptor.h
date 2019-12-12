// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.
#pragma once
#include "UObject/Class.h"

#include "Resources/FGItemDescriptor.h"
#include "FGAnyUndefinedDescriptor.generated.h"

/**
 * Descriptor Rule. Will consider all items but those specified. Used on splitters to exclude items that have other rules set
 * Ex: Splitter with rules: Left -> Aluminum | Center -> AnyUndefined	Splitter will only send aluminum to left, never to Center
 */
UCLASS()
class FACTORYGAME_API UFGAnyUndefinedDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()
public:
	UFGAnyUndefinedDescriptor();
};
