#include "FGPlatformFunctions.h"

void UFGPlatformFunctionsSubsystem::Initialize(FSubsystemCollectionBase& Collection){ Super::Initialize(Collection); }
void UFGPlatformFunctionsSubsystem::Deinitialize(){ Super::Deinitialize(); }
void UFGPlatformFunctionsSubsystem::CreatePlatformScreenshot(bool bHiRes, FFGPlatformScreenshotDone DoneDelegate){  }
float UFGPlatformFunctionsSubsystem::GetPlatformScreenshotCooldown(){ return float(); }
bool UFGPlatformFunctionsSubsystem::PlatformHasFeature(EFGPlatformFeature Feature){ return bool(); }
int UFGPlatformFunctionsSubsystem::GetPlatformMaxSavegames(){ return int(); }
bool UFGPlatformFunctionsSubsystem::PlatformSupportsCommunityTranslations(){ return bool(); }
bool UFGPlatformFunctionsSubsystem::HasPlatform120HzEnabled(int32& RefreshRate){ return bool(); }