// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "FGInputModifierDeadzoneSetting.generated.h"

class UFGUserSetting;

UCLASS(NotBlueprintable, meta = (DisplayName = "Deadzone From UserSetting"))
class FACTORYGAME_API UFGInputModifierDeadzoneSetting : public UInputModifier
{
	GENERATED_BODY()
public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings,  meta = (ToolTip = "Get value from this UserSetting for Lower Threshold. When empty uses default value."))
	TObjectPtr<UFGUserSetting> LowerThresholdSetting;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Settings,  meta = (ToolTip = "Get value from this UserSetting for Upper Threshold. When empty uses default value."))
	TObjectPtr<UFGUserSetting> UpperThresholdSetting;

	// Threshold below which input is ignored
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=Settings, Config, meta=(ClampMin=0, ClampMax=1))
	float LowerThreshold = 0.2f;

	// Threshold above which input is clamped to 1
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=Settings, Config, meta=(ClampMin=0, ClampMax=1))
	float UpperThreshold = 1.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=Settings, Config)
	EDeadZoneType Type = EDeadZoneType::Radial;
protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;

	virtual FLinearColor GetVisualizationColor_Implementation(FInputActionValue SampleValue, FInputActionValue FinalValue) const override;
};
