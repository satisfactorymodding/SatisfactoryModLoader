// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Composure_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Composure.ComposureBlueprintLibrary.SetUVMapSettingsToMaterialParameters
// ()
// Parameters:
// struct FComposureUVMapSettings UVMapSettings                  (ConstParm, Parm, OutParm, ReferenceParm)
// class UMaterialInstanceDynamic* Material                       (Parm, ZeroConstructor, IsPlainOldData)

void UComposureBlueprintLibrary::SetUVMapSettingsToMaterialParameters(const struct FComposureUVMapSettings& UVMapSettings, class UMaterialInstanceDynamic* Material)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureBlueprintLibrary.SetUVMapSettingsToMaterialParameters");

	UComposureBlueprintLibrary_SetUVMapSettingsToMaterialParameters_Params params;
	params.UVMapSettings = UVMapSettings;
	params.Material = Material;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Composure.ComposureBlueprintLibrary.InvertUVDisplacementMapEncodingParameters
// ()
// Parameters:
// struct FVector2D               In                             (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector2D               Out                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UComposureBlueprintLibrary::InvertUVDisplacementMapEncodingParameters(const struct FVector2D& In, struct FVector2D* Out)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureBlueprintLibrary.InvertUVDisplacementMapEncodingParameters");

	UComposureBlueprintLibrary_InvertUVDisplacementMapEncodingParameters_Params params;
	params.In = In;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Out != nullptr)
		*Out = params.Out;
}


// Function Composure.ComposureBlueprintLibrary.GetRedGreenUVFactorsFromChromaticAberration
// ()
// Parameters:
// float                          ChromaticAberrationAmount      (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               RedGreenUVFactors              (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UComposureBlueprintLibrary::GetRedGreenUVFactorsFromChromaticAberration(float ChromaticAberrationAmount, struct FVector2D* RedGreenUVFactors)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureBlueprintLibrary.GetRedGreenUVFactorsFromChromaticAberration");

	UComposureBlueprintLibrary_GetRedGreenUVFactorsFromChromaticAberration_Params params;
	params.ChromaticAberrationAmount = ChromaticAberrationAmount;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (RedGreenUVFactors != nullptr)
		*RedGreenUVFactors = params.RedGreenUVFactors;
}


// Function Composure.ComposureBlueprintLibrary.GetProjectionMatrixFromPostMoveSettings
// ()
// Parameters:
// struct FComposurePostMoveSettings PostMoveSettings               (ConstParm, Parm, OutParm, ReferenceParm)
// float                          HorizontalFOVAngle             (Parm, ZeroConstructor, IsPlainOldData)
// float                          AspectRatio                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FMatrix                 ProjectionMatrix               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UComposureBlueprintLibrary::GetProjectionMatrixFromPostMoveSettings(const struct FComposurePostMoveSettings& PostMoveSettings, float HorizontalFOVAngle, float AspectRatio, struct FMatrix* ProjectionMatrix)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureBlueprintLibrary.GetProjectionMatrixFromPostMoveSettings");

	UComposureBlueprintLibrary_GetProjectionMatrixFromPostMoveSettings_Params params;
	params.PostMoveSettings = PostMoveSettings;
	params.HorizontalFOVAngle = HorizontalFOVAngle;
	params.AspectRatio = AspectRatio;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ProjectionMatrix != nullptr)
		*ProjectionMatrix = params.ProjectionMatrix;
}


// Function Composure.ComposureBlueprintLibrary.GetPlayerDisplayGamma
// ()
// Parameters:
// class APlayerCameraManager*    PlayerCameraManager            (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// float                          DisplayGamma                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UComposureBlueprintLibrary::GetPlayerDisplayGamma(class APlayerCameraManager* PlayerCameraManager, float* DisplayGamma)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureBlueprintLibrary.GetPlayerDisplayGamma");

	UComposureBlueprintLibrary_GetPlayerDisplayGamma_Params params;
	params.PlayerCameraManager = PlayerCameraManager;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (DisplayGamma != nullptr)
		*DisplayGamma = params.DisplayGamma;
}


// Function Composure.ComposureBlueprintLibrary.GetCroppingUVTransformationMatrixFromPostMoveSettings
// ()
// Parameters:
// struct FComposurePostMoveSettings PostMoveSettings               (ConstParm, Parm, OutParm, ReferenceParm)
// float                          AspectRatio                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FMatrix                 CropingUVTransformationMatrix  (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FMatrix                 UncropingUVTransformationMatrix (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UComposureBlueprintLibrary::GetCroppingUVTransformationMatrixFromPostMoveSettings(const struct FComposurePostMoveSettings& PostMoveSettings, float AspectRatio, struct FMatrix* CropingUVTransformationMatrix, struct FMatrix* UncropingUVTransformationMatrix)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureBlueprintLibrary.GetCroppingUVTransformationMatrixFromPostMoveSettings");

	UComposureBlueprintLibrary_GetCroppingUVTransformationMatrixFromPostMoveSettings_Params params;
	params.PostMoveSettings = PostMoveSettings;
	params.AspectRatio = AspectRatio;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (CropingUVTransformationMatrix != nullptr)
		*CropingUVTransformationMatrix = params.CropingUVTransformationMatrix;
	if (UncropingUVTransformationMatrix != nullptr)
		*UncropingUVTransformationMatrix = params.UncropingUVTransformationMatrix;
}


// Function Composure.ComposureBlueprintLibrary.CreatePlayerCompositingTarget
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// class UComposurePlayerCompositingTarget* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UComposurePlayerCompositingTarget* UComposureBlueprintLibrary::CreatePlayerCompositingTarget(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureBlueprintLibrary.CreatePlayerCompositingTarget");

	UComposureBlueprintLibrary_CreatePlayerCompositingTarget_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Composure.ComposurePostProcessPass.SetSetupMaterial
// ()
// Parameters:
// class UMaterialInterface*      Material                       (Parm, ZeroConstructor, IsPlainOldData)

void UComposurePostProcessPass::SetSetupMaterial(class UMaterialInterface* Material)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposurePostProcessPass.SetSetupMaterial");

	UComposurePostProcessPass_SetSetupMaterial_Params params;
	params.Material = Material;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Composure.ComposurePostProcessPass.SetOutputRenderTarget
// ()
// Parameters:
// class UTextureRenderTarget2D*  RenderTarget                   (Parm, ZeroConstructor, IsPlainOldData)

void UComposurePostProcessPass::SetOutputRenderTarget(class UTextureRenderTarget2D* RenderTarget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposurePostProcessPass.SetOutputRenderTarget");

	UComposurePostProcessPass_SetOutputRenderTarget_Params params;
	params.RenderTarget = RenderTarget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Composure.ComposurePostProcessPass.GetSetupMaterial
// ()
// Parameters:
// class UMaterialInterface*      ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInterface* UComposurePostProcessPass::GetSetupMaterial()
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposurePostProcessPass.GetSetupMaterial");

	UComposurePostProcessPass_GetSetupMaterial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Composure.ComposurePostProcessPass.GetOutputRenderTarget
// ()
// Parameters:
// class UTextureRenderTarget2D*  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTextureRenderTarget2D* UComposurePostProcessPass::GetOutputRenderTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposurePostProcessPass.GetOutputRenderTarget");

	UComposurePostProcessPass_GetOutputRenderTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Composure.ComposureLensBloomPass.SetTonemapperReplacingMaterial
// ()
// Parameters:
// class UMaterialInstanceDynamic* Material                       (Parm, ZeroConstructor, IsPlainOldData)

void UComposureLensBloomPass::SetTonemapperReplacingMaterial(class UMaterialInstanceDynamic* Material)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureLensBloomPass.SetTonemapperReplacingMaterial");

	UComposureLensBloomPass_SetTonemapperReplacingMaterial_Params params;
	params.Material = Material;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Composure.ComposureLensBloomPass.BloomToRenderTarget
// ()

void UComposureLensBloomPass::BloomToRenderTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureLensBloomPass.BloomToRenderTarget");

	UComposureLensBloomPass_BloomToRenderTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Composure.ComposurePlayerCompositingTarget.SetRenderTarget
// ()
// Parameters:
// class UTextureRenderTarget2D*  RenderTarget                   (Parm, ZeroConstructor, IsPlainOldData)

void UComposurePlayerCompositingTarget::SetRenderTarget(class UTextureRenderTarget2D* RenderTarget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposurePlayerCompositingTarget.SetRenderTarget");

	UComposurePlayerCompositingTarget_SetRenderTarget_Params params;
	params.RenderTarget = RenderTarget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Composure.ComposurePlayerCompositingTarget.SetPlayerCameraManager
// ()
// Parameters:
// class APlayerCameraManager*    PlayerCameraManager            (Parm, ZeroConstructor, IsPlainOldData)
// class APlayerCameraManager*    ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class APlayerCameraManager* UComposurePlayerCompositingTarget::SetPlayerCameraManager(class APlayerCameraManager* PlayerCameraManager)
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposurePlayerCompositingTarget.SetPlayerCameraManager");

	UComposurePlayerCompositingTarget_SetPlayerCameraManager_Params params;
	params.PlayerCameraManager = PlayerCameraManager;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Composure.ComposurePlayerCompositingTarget.GetPlayerCameraManager
// ()
// Parameters:
// class APlayerCameraManager*    ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class APlayerCameraManager* UComposurePlayerCompositingTarget::GetPlayerCameraManager()
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposurePlayerCompositingTarget.GetPlayerCameraManager");

	UComposurePlayerCompositingTarget_GetPlayerCameraManager_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Composure.ComposureTonemapperPass.TonemapToRenderTarget
// ()

void UComposureTonemapperPass::TonemapToRenderTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Composure.ComposureTonemapperPass.TonemapToRenderTarget");

	UComposureTonemapperPass_TonemapToRenderTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
