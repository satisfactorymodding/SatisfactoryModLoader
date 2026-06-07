// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "FGInputModifierInvertSetting.generated.h"

/**
 * 
 */
class UFGUserSetting;


UCLASS(NotBlueprintable, meta = (DisplayName = "Invert From UserSetting"))
class FACTORYGAME_API UFGInputModifierInvertSetting : public UInputModifier
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings,  meta = (ToolTip = "Get value from this UserSetting for X. When empty does nothing"))
	TObjectPtr<UFGUserSetting> XOptionSetting;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings,  meta = (ToolTip = "Get value from this UserSetting for Y. When empty does nothing"))
	TObjectPtr<UFGUserSetting> YOptionSetting;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;
};
