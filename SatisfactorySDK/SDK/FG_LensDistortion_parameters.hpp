#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_LensDistortion_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function LensDistortion.LensDistortionBlueprintLibrary.NotEqual_CompareLensDistortionModels
struct ULensDistortionBlueprintLibrary_NotEqual_CompareLensDistortionModels_Params
{
	struct FLensDistortionCameraModel                  A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FLensDistortionCameraModel                  B;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function LensDistortion.LensDistortionBlueprintLibrary.GetUndistortOverscanFactor
struct ULensDistortionBlueprintLibrary_GetUndistortOverscanFactor_Params
{
	struct FLensDistortionCameraModel                  CameraModel;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              DistortedHorizontalFOV;                                   // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DistortedAspectRatio;                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              UndistortOverscanFactor;                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function LensDistortion.LensDistortionBlueprintLibrary.EqualEqual_CompareLensDistortionModels
struct ULensDistortionBlueprintLibrary_EqualEqual_CompareLensDistortionModels_Params
{
	struct FLensDistortionCameraModel                  A;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FLensDistortionCameraModel                  B;                                                        // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function LensDistortion.LensDistortionBlueprintLibrary.DrawUVDisplacementToRenderTarget
struct ULensDistortionBlueprintLibrary_DrawUVDisplacementToRenderTarget_Params
{
	class UObject*                                     WorldContextObject;                                       // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
	struct FLensDistortionCameraModel                  CameraModel;                                              // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              DistortedHorizontalFOV;                                   // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              DistortedAspectRatio;                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              UndistortOverscanFactor;                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UTextureRenderTarget2D*                      OutputRenderTarget;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              OutputMultiply;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              OutputAdd;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
