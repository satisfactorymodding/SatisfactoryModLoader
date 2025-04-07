#include "Input/Modifiers/FGInputModifierScalarSetting.h"

#if WITH_EDITOR
EDataValidationResult UFGInputModifierScalarSetting::IsDataValid(class FDataValidationContext& Context) const{ return Super::IsDataValid(Context); }
#endif
FInputActionValue UFGInputModifierScalarSetting::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime){ return Super::ModifyRaw_Implementation(PlayerInput, CurrentValue, DeltaTime); }