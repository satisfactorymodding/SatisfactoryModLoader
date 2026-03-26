#include "Input/Modifiers/FGInputModifierInvertSetting.h"

#if WITH_EDITOR
EDataValidationResult UFGInputModifierInvertSetting::IsDataValid(class FDataValidationContext& Context) const{ return Super::IsDataValid(Context); }
#endif
FInputActionValue UFGInputModifierInvertSetting::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime){ return Super::ModifyRaw_Implementation(PlayerInput, CurrentValue, DeltaTime); }
