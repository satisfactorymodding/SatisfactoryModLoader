// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildablePipelineAttachment.h"
#include "FGBuildablePipelineJunction.generated.h"

/**
 *	Junction class for creating splits in a pipeline network.
 *  @todo-Pipes - This class turned out to be super not needed. At least not at the moment with just the one pipe junction type. So consider for removal
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipelineJunction : public AFGBuildablePipelineAttachment
{
	GENERATED_BODY()
public:
};
