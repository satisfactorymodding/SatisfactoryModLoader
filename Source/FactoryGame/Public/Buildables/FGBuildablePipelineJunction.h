// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildablePipelineAttachment.h"
#include "FGBuildablePipelineJunction.generated.h"

/**
 *	Junction class for creating splits in a pipeline network.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipelineJunction : public AFGBuildablePipelineAttachment
{
	GENERATED_BODY()
public:

	AFGBuildablePipelineJunction();
};
