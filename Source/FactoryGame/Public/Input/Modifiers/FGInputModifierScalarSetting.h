// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "FGInputModifierScalarSetting.generated.h"

class UFGUserSetting;


UCLASS(NotBlueprintable, meta = (DisplayName = "Scalar From UserSetting"))
class FACTORYGAME_API UFGInputModifierScalarSetting : public UInputModifier
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings,  meta = (ToolTip = "Get value from this UserSetting for X. When empty uses default value."))
	TObjectPtr<UFGUserSetting> XOptionSetting;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings,  meta = (ToolTip = "Get value from this UserSetting for Y. When empty uses default value."))
	TObjectPtr<UFGUserSetting> YOptionSetting;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings,  meta = (ToolTip = "Get value from this UserSetting for Z. When empty uses default value."))
	TObjectPtr<UFGUserSetting> ZOptionSetting;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=Settings)
	FVector Scalar = FVector::OneVector;

protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;
};