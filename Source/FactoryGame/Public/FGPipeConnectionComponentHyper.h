// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGPipeConnectionComponent.h"
#include "FGPipeConnectionComponentHyper.generated.h"

/**
 * Connection used for hyper tubes.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGPipeConnectionComponentHyper : public UFGPipeConnectionComponentBase
{
	GENERATED_BODY()
public:
	UFGPipeConnectionComponentHyper();
};
