#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDCameraShake_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Get Cam and View Position Difference
struct UWidget_HUDCameraShake_C_Get_Cam_and_View_Position_Difference_Params
{
	float                                              Scale;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Get Cam and View Rotation Difference
struct UWidget_HUDCameraShake_C_Get_Cam_and_View_Rotation_Difference_Params
{
	float                                              X;                                                        // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	float                                              Y;                                                        // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.HUD Lerp
struct UWidget_HUDCameraShake_C_HUD_Lerp_Params
{
};

// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.Tick
struct UWidget_HUDCameraShake_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDCameraShake.Widget_HUDCameraShake_C.ExecuteUbergraph_Widget_HUDCameraShake
struct UWidget_HUDCameraShake_C_ExecuteUbergraph_Widget_HUDCameraShake_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
