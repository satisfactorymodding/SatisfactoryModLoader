// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerInput.h"
#include "FGPlayerInput.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPlayerInput : public UPlayerInput
{
	GENERATED_BODY()
public:
	virtual float SmoothMouse( float aMouse, uint8& SampleCount, int32 Index ) override;
};
