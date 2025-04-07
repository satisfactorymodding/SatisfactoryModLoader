#include "Input/Modifiers/FGInputModifierDeadzoneSetting.h"

FInputActionValue UFGInputModifierDeadzoneSetting::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime){ return Super::ModifyRaw_Implementation(PlayerInput, CurrentValue, DeltaTime); }
FLinearColor UFGInputModifierDeadzoneSetting::GetVisualizationColor_Implementation(FInputActionValue SampleValue, FInputActionValue FinalValue) const{ return Super::GetVisualizationColor_Implementation(SampleValue, FinalValue); }