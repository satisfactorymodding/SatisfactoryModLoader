#include "RainRendering.h"

void FRainRenderingModule::StartupModule(){ IModuleInterface::StartupModule(); }
void FRainRenderingModule::ShutdownModule(){ IModuleInterface::ShutdownModule(); }

void UFGRainRenderingSubsystem::SetWetnessIntensity(UObject* WorldContextObject, float NewValue){ }
bool UFGRainRenderingSubsystem::ShouldRunRainPass(const UWorld* World, float& OutIntensity){ return false; }
void UFGRainRenderingSubsystem::GetDepthCaptureInformation(const UWorld* World, FVector& FactoryCaptureLocation, FVector& StaticOcclusionCaptureLocation){ }
void UFGRainRenderingSubsystem::GetTextures(const UWorld* World, UTexture2D*& OutDitherTexture, UTexture2D*& OutStaticWorldTexture, UTextureRenderTarget2D*& OutFactoryOcclusionRenderTarget){ }
void UFGRainRenderingSubsystem::UpdateFactoryOcclusionCaptureLocation(const UWorld* World, const FVector& NewLocation){ }
void UFGRainRenderingSubsystem::UpdateStaticOcclusionDepthTextureAndLocation(const UWorld* World, const FVector& NewCaptureLocation, UTexture2D* NewTexture){ }
void UFGRainRenderingSubsystem::Initialize(FSubsystemCollectionBase& Collection){ Super::Initialize(Collection); }
void UFGRainRenderingSubsystem::Deinitialize(){ Super::Deinitialize(); }

IMPLEMENT_GAME_MODULE(FRainRenderingModule, RainRendering);