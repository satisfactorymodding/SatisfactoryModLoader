#include "Equipment/AimAssist/FGAimAssistCameraModifier.h"

UFGAimAssistCameraModifier* UFGAimAssistCameraModifier::FindOrCreate(APlayerController* PlayerController){ return nullptr; }
bool UFGAimAssistCameraModifier::ProcessViewRotation(class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot){ return Super::ProcessViewRotation(ViewTarget, DeltaTime, OutViewRotation, OutDeltaRot); }
void UFGAimAssistCameraModifier::SetClient(TScriptInterface<IFGAimAssistClient> AimAssistClient){ }
void UFGAimAssistCameraModifier::DisplayDebugAimAssist(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos){ }
void UFGAimAssistCameraModifier::OnAimAssistStrengthSettingUpdated(FString cvar){ }
