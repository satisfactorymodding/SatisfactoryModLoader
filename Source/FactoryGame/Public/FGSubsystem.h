// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "FGSubsystem.generated.h"

/**
 * Base for all subsystems we use in the game.
 */
UCLASS( Abstract, hidecategories = ( Actor, Input, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGSubsystem : public AInfo
{
	GENERATED_BODY()
public:
	AFGSubsystem();
};
