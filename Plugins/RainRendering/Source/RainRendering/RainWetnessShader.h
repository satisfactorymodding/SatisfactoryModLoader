#pragma once
#include "GlobalShader.h"
#include "ShaderParameterStruct.h"
#include "RenderGraphUtils.h"
#include "RHIDefinitions.h"
#include "ScenePrivate.h"
#include "Engine/TextureRenderTarget2D.h"

class FInjectIntoGBufferPS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FInjectIntoGBufferPS);
	SHADER_USE_PARAMETER_STRUCT(FInjectIntoGBufferPS, FGlobalShader);
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, SourceTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, SourceSampler)
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};

class FRainWetnessInjectionCS : public FGlobalShader
{
	DECLARE_GLOBAL_SHADER(FRainWetnessInjectionCS);
	SHADER_USE_PARAMETER_STRUCT(FRainWetnessInjectionCS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, GBufferA_Ref)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, GBufferB_Ref)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, GBufferC_Ref)
	
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, GBufferA)
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, GBufferB)
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, GBufferC)

		/* SM5 only copy to target. */
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, GBufferCopy_Ref)
	
		// Scene depth.
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneDepthTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, SceneDepthSampler)

		// Rain occlusion capture mask
		SHADER_PARAMETER_TEXTURE(Texture2D, RainOcclusionTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, RainOcclusionSampler)

		// Static world occlusion mask.
		SHADER_PARAMETER_TEXTURE(Texture2D, WorldOcclusionDepth)
		SHADER_PARAMETER_SAMPLER(SamplerState, WorldOcclusionDepthSampler)
	
		// Dither texture
		SHADER_PARAMETER_TEXTURE(Texture2D, DitherTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, DitherTextureSampler)

		// Wetness intensity.
		SHADER_PARAMETER(float, WetnessIntensity )
		SHADER_PARAMETER(FVector3f, CaptureLocationFactory)
		SHADER_PARAMETER(FVector3f, StaticOcclusionCaptureLocation)
	
		// View param.
		SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)

	END_SHADER_PARAMETER_STRUCT()

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
#if PLATFORM_PS5
		return false;
#else
		return true;
#endif
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		OutEnvironment.CompilerFlags.Add(CFLAG_AllowTypedUAVLoads);

		const bool ShouldSupportUAV = 	IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM6) && 
										!FDataDrivenShaderPlatformInfo::GetIsLanguageSony(Parameters.Platform);

		if( ShouldSupportUAV )
		{
			OutEnvironment.SetDefine(TEXT("USE_UAV"), 1);
		}
		else
		{
			// Force SM5 implementation for sony platform due to RW restrictions.
			OutEnvironment.SetDefine(TEXT("USE_UAV"), 0);
		}
	}

	static void RunRainShader(FRDGBuilder& GraphBuilder,
		FSceneView& InView,
		const FRenderTargetBindingSlots& RenderTargets,
		UTextureRenderTarget2D* FactoryOcclusionRenderTarget,
		UTexture2D* DitherTexture,
		UTexture2D* StaticWorldTexture,
		float Intensity,
		const FVector& FactoryDepthCaptureLocation,
		const FVector& StaticOcclusionCaptureLocation);
};