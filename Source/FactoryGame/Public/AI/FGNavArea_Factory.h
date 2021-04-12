// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea.h"
#include "FGNavArea_Factory.generated.h"

/**
 * Intended for all man made surfaces. Player created or in the world.
 */
UCLASS()
class FACTORYGAME_API UFGNavArea_Factory : public UNavArea
{
	GENERATED_BODY()

	UFGNavArea_Factory( const FObjectInitializer& ObjectInitializer );
};
