// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"
#include "FGNavArea_HardNature.generated.h"

/**
 * Intended for rocky areas or other hard materials in nature. Will let animals path intelligently.
 */
UCLASS()
class FACTORYGAME_API UFGNavArea_HardNature : public UNavArea
{
	GENERATED_BODY()

	UFGNavArea_HardNature( const FObjectInitializer& ObjectInitializer );
};
