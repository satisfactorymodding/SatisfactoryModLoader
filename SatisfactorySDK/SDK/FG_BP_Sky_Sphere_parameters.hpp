#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Sky_Sphere_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.SetLightAsDominant
struct ABP_Sky_Sphere_C_SetLightAsDominant_Params
{
	class ADirectionalLight*                           Light;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               newDominant;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.newDominantLight
struct ABP_Sky_Sphere_C_newDominantLight_Params
{
	class ADirectionalLight*                           oldDominantLight;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class ADirectionalLight*                           newDominantLight;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateDominantLight
struct ABP_Sky_Sphere_C_CalculateDominantLight_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateDiscBrightness
struct ABP_Sky_Sphere_C_CalculateDiscBrightness_Params
{
	class ALight*                                      Light;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FFBrightnessAdjustment                      brightnessAdjustment;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              discBrightness;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateBrightness
struct ABP_Sky_Sphere_C_CalculateBrightness_Params
{
	float                                              Brightness;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.CalculateLightRotation
struct ABP_Sky_Sphere_C_CalculateLightRotation_Params
{
	struct FRotator                                    OriginalRotation;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    RotationAxis;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FRuntimeFloatCurve                          LightRotationCurve;                                       // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FRotator                                    NewRotation;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateGlobalParameters
struct ABP_Sky_Sphere_C_UpdateGlobalParameters_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateCurvesFromTime
struct ABP_Sky_Sphere_C_UpdateCurvesFromTime_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateLightRotation
struct ABP_Sky_Sphere_C_UpdateLightRotation_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdateMaterialParameters
struct ABP_Sky_Sphere_C_UpdateMaterialParameters_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UserConstructionScript
struct ABP_Sky_Sphere_C_UserConstructionScript_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ReceiveTick
struct ABP_Sky_Sphere_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ReceiveBeginPlay
struct ABP_Sky_Sphere_C_ReceiveBeginPlay_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.UpdatePreview
struct ABP_Sky_Sphere_C_UpdatePreview_Params
{
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ApplySkySphereSettings
struct ABP_Sky_Sphere_C_ApplySkySphereSettings_Params
{
	struct FSkySphereSettings*                         Settings;                                                 // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Sky_Sphere.BP_Sky_Sphere_C.ExecuteUbergraph_BP_Sky_Sphere
struct ABP_Sky_Sphere_C_ExecuteUbergraph_BP_Sky_Sphere_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
