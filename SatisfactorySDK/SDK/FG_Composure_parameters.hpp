#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Composure_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Composure.ComposureBlueprintLibrary.SetUVMapSettingsToMaterialParameters
struct UComposureBlueprintLibrary_SetUVMapSettingsToMaterialParameters_Params
{
	struct FComposureUVMapSettings                     UVMapSettings;                                            // (ConstParm, Parm, OutParm, ReferenceParm)
	class UMaterialInstanceDynamic*                    Material;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposureBlueprintLibrary.InvertUVDisplacementMapEncodingParameters
struct UComposureBlueprintLibrary_InvertUVDisplacementMapEncodingParameters_Params
{
	struct FVector2D                                   In;                                                       // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	struct FVector2D                                   Out;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposureBlueprintLibrary.GetRedGreenUVFactorsFromChromaticAberration
struct UComposureBlueprintLibrary_GetRedGreenUVFactorsFromChromaticAberration_Params
{
	float                                              ChromaticAberrationAmount;                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   RedGreenUVFactors;                                        // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposureBlueprintLibrary.GetProjectionMatrixFromPostMoveSettings
struct UComposureBlueprintLibrary_GetProjectionMatrixFromPostMoveSettings_Params
{
	struct FComposurePostMoveSettings                  PostMoveSettings;                                         // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              HorizontalFOVAngle;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              AspectRatio;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FMatrix                                     ProjectionMatrix;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposureBlueprintLibrary.GetPlayerDisplayGamma
struct UComposureBlueprintLibrary_GetPlayerDisplayGamma_Params
{
	class APlayerCameraManager*                        PlayerCameraManager;                                      // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	float                                              DisplayGamma;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposureBlueprintLibrary.GetCroppingUVTransformationMatrixFromPostMoveSettings
struct UComposureBlueprintLibrary_GetCroppingUVTransformationMatrixFromPostMoveSettings_Params
{
	struct FComposurePostMoveSettings                  PostMoveSettings;                                         // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              AspectRatio;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FMatrix                                     CropingUVTransformationMatrix;                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FMatrix                                     UncropingUVTransformationMatrix;                          // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposureBlueprintLibrary.CreatePlayerCompositingTarget
struct UComposureBlueprintLibrary_CreatePlayerCompositingTarget_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UComposurePlayerCompositingTarget*           ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Composure.ComposurePostProcessPass.SetSetupMaterial
struct UComposurePostProcessPass_SetSetupMaterial_Params
{
	class UMaterialInterface*                          Material;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposurePostProcessPass.SetOutputRenderTarget
struct UComposurePostProcessPass_SetOutputRenderTarget_Params
{
	class UTextureRenderTarget2D*                      RenderTarget;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposurePostProcessPass.GetSetupMaterial
struct UComposurePostProcessPass_GetSetupMaterial_Params
{
	class UMaterialInterface*                          ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Composure.ComposurePostProcessPass.GetOutputRenderTarget
struct UComposurePostProcessPass_GetOutputRenderTarget_Params
{
	class UTextureRenderTarget2D*                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Composure.ComposureLensBloomPass.SetTonemapperReplacingMaterial
struct UComposureLensBloomPass_SetTonemapperReplacingMaterial_Params
{
	class UMaterialInstanceDynamic*                    Material;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposureLensBloomPass.BloomToRenderTarget
struct UComposureLensBloomPass_BloomToRenderTarget_Params
{
};

// Function Composure.ComposurePlayerCompositingTarget.SetRenderTarget
struct UComposurePlayerCompositingTarget_SetRenderTarget_Params
{
	class UTextureRenderTarget2D*                      RenderTarget;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function Composure.ComposurePlayerCompositingTarget.SetPlayerCameraManager
struct UComposurePlayerCompositingTarget_SetPlayerCameraManager_Params
{
	class APlayerCameraManager*                        PlayerCameraManager;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	class APlayerCameraManager*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Composure.ComposurePlayerCompositingTarget.GetPlayerCameraManager
struct UComposurePlayerCompositingTarget_GetPlayerCameraManager_Params
{
	class APlayerCameraManager*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Composure.ComposureTonemapperPass.TonemapToRenderTarget
struct UComposureTonemapperPass_TonemapToRenderTarget_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
