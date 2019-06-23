// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Sky_Sphere_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.SetLightAsDominant
// ()
// Parameters:
// class ADirectionalLight*       Light                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           newDominant                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Sky_Sphere_C::SetLightAsDominant(class ADirectionalLight* Light, bool newDominant)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.SetLightAsDominant");

	ABP_Sky_Sphere_C_SetLightAsDominant_Params params;
	params.Light = Light;
	params.newDominant = newDominant;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.newDominantLight
// ()
// Parameters:
// class ADirectionalLight*       oldDominantLight               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class ADirectionalLight*       newDominantLight               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Sky_Sphere_C::newDominantLight(class ADirectionalLight* oldDominantLight, class ADirectionalLight* newDominantLight)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.newDominantLight");

	ABP_Sky_Sphere_C_newDominantLight_Params params;
	params.oldDominantLight = oldDominantLight;
	params.newDominantLight = newDominantLight;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateDominantLight
// ()

void ABP_Sky_Sphere_C::CalculateDominantLight()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateDominantLight");

	ABP_Sky_Sphere_C_CalculateDominantLight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateDiscBrightness
// ()
// Parameters:
// class ALight*                  Light                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FFBrightnessAdjustment  brightnessAdjustment           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          discBrightness                 (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_Sky_Sphere_C::CalculateDiscBrightness(class ALight* Light, const struct FFBrightnessAdjustment& brightnessAdjustment, float* discBrightness)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateDiscBrightness");

	ABP_Sky_Sphere_C_CalculateDiscBrightness_Params params;
	params.Light = Light;
	params.brightnessAdjustment = brightnessAdjustment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (discBrightness != nullptr)
		*discBrightness = params.discBrightness;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateBrightness
// ()
// Parameters:
// float                          Brightness                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_Sky_Sphere_C::CalculateBrightness(float* Brightness)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateBrightness");

	ABP_Sky_Sphere_C_CalculateBrightness_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Brightness != nullptr)
		*Brightness = params.Brightness;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateLightRotation
// ()
// Parameters:
// struct FRotator                OriginalRotation               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FRotator                RotationAxis                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FRuntimeFloatCurve      LightRotationCurve             (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FRotator                NewRotation                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_Sky_Sphere_C::CalculateLightRotation(const struct FRotator& OriginalRotation, const struct FRotator& RotationAxis, const struct FRuntimeFloatCurve& LightRotationCurve, struct FRotator* NewRotation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateLightRotation");

	ABP_Sky_Sphere_C_CalculateLightRotation_Params params;
	params.OriginalRotation = OriginalRotation;
	params.RotationAxis = RotationAxis;
	params.LightRotationCurve = LightRotationCurve;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NewRotation != nullptr)
		*NewRotation = params.NewRotation;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateGlobalParameters
// ()

void ABP_Sky_Sphere_C::UpdateGlobalParameters()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateGlobalParameters");

	ABP_Sky_Sphere_C_UpdateGlobalParameters_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateCurvesFromTime
// ()

void ABP_Sky_Sphere_C::UpdateCurvesFromTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateCurvesFromTime");

	ABP_Sky_Sphere_C_UpdateCurvesFromTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateLightRotation
// ()

void ABP_Sky_Sphere_C::UpdateLightRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateLightRotation");

	ABP_Sky_Sphere_C_UpdateLightRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateMaterialParameters
// ()

void ABP_Sky_Sphere_C::UpdateMaterialParameters()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateMaterialParameters");

	ABP_Sky_Sphere_C_UpdateMaterialParameters_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UserConstructionScript
// ()

void ABP_Sky_Sphere_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.UserConstructionScript");

	ABP_Sky_Sphere_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Sky_Sphere_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.ReceiveTick");

	ABP_Sky_Sphere_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ReceiveBeginPlay
// ()

void ABP_Sky_Sphere_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.ReceiveBeginPlay");

	ABP_Sky_Sphere_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdatePreview
// ()

void ABP_Sky_Sphere_C::UpdatePreview()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdatePreview");

	ABP_Sky_Sphere_C_UpdatePreview_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ApplySkySphereSettings
// ()
// Parameters:
// struct FSkySphereSettings*     Settings                       (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Sky_Sphere_C::ApplySkySphereSettings(struct FSkySphereSettings* Settings)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.ApplySkySphereSettings");

	ABP_Sky_Sphere_C_ApplySkySphereSettings_Params params;
	params.Settings = Settings;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ExecuteUbergraph_BP_Sky_Sphere
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Sky_Sphere_C::ExecuteUbergraph_BP_Sky_Sphere(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Sky_Sphere.BP_Sky_Sphere_C.ExecuteUbergraph_BP_Sky_Sphere");

	ABP_Sky_Sphere_C_ExecuteUbergraph_BP_Sky_Sphere_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
