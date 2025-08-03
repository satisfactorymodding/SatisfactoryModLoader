// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "FGInputModifierGamepadAimAssist.generated.h"


// <FL> [MartinC] Input modifier to make aiming and turning with a gamepad more precise
UCLASS( NotBlueprintable, meta = ( DisplayName = "Gamepad Aim Assist" ) )
class FACTORYGAME_API UFGInputModifierGamepadAimAssist : public UInputModifier
{
	GENERATED_BODY()
public:
	UPROPERTY( EditInstanceOnly, BlueprintReadWrite, Category = Settings)
	TObjectPtr< UCurveFloat > AimAssistCurveX;
	UPROPERTY( EditInstanceOnly, BlueprintReadWrite, Category = Settings )
	TObjectPtr< UCurveFloat > AimAssistCurveY;

protected:
	virtual FInputActionValue ModifyRaw_Implementation( const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue,
														float DeltaTime ) override;

};
