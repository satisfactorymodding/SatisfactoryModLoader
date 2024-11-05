// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AISystem.h"
#include "FGAISystem.generated.h"

/**
 * TODO: Tobias 2022-02-09: All the functionality of this class was moved to FGCreatureSubsystem.
 */
UCLASS(Blueprintable)
class FACTORYGAME_API UFGAISystem : public UAISystem
{
	GENERATED_BODY()
public:
	UFGAISystem( const FObjectInitializer& ObjectInitializer );
};
