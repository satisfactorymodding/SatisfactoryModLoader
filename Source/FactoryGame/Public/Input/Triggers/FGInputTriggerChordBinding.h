// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "FGInputTriggerChordBinding.generated.h"

/**
 * Class used to inject as a "Chord Action" trigger in runtime, for the player when binding keys as chords (Ctrl + C, Ctrl + V, etc)
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "FG Chord Binding", NotInputConfigurable = "true"))
class FACTORYGAME_API UFGInputTriggerChordBinding : public UInputTriggerChordAction
{
	GENERATED_BODY()
public:
};