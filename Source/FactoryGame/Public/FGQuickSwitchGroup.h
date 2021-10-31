// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGQuickSwitchGroup.generated.h"

/**
 * Just an empty class so we can create derived BP classes and handle them natively
 * Used for sorting buildings in quick switch groups that can be switched between quickly with a key press
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGQuickSwitchGroup : public UObject
{
	GENERATED_BODY()
};
