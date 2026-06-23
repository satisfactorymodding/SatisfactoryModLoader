#include "RainWetnessShader.h"

// MODDING: We don't have the shader sources
// IMPLEMENT_GLOBAL_SHADER(FInjectIntoGBufferPS, "/Plugin/RainRendering/CopyToGBuffer.usf", "MainPS", SF_Pixel);
// IMPLEMENT_GLOBAL_SHADER(FRainWetnessInjectionCS, "/Plugin/RainRendering/RainWetnessInjection.usf", "MainCS", SF_Compute);

void FRainWetnessInjectionCS::RunRainShader(FRDGBuilder& GraphBuilder,
		FSceneView& InView,
		const FRenderTargetBindingSlots& RenderTargets,
		UTextureRenderTarget2D* FactoryOcclusionRenderTarget,
		UTexture2D* DitherTexture,
		UTexture2D* StaticWorldTexture,
		float Intensity,
		const FVector& FactoryDepthCaptureLocation,
		const FVector& StaticOcclusionCaptureLocation){ }