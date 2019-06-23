#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBOX_Jetpack_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.StopPulse
struct UWidget_HUDBox_Jetpack_C_StopPulse_Params
{
};

// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.StartPulse
struct UWidget_HUDBox_Jetpack_C_StartPulse_Params
{
};

// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.Construct
struct UWidget_HUDBox_Jetpack_C_Construct_Params
{
};

// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.Tick
struct UWidget_HUDBox_Jetpack_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.BarPulse
struct UWidget_HUDBox_Jetpack_C_BarPulse_Params
{
};

// Function Widget_HUDBOX_Jetpack.Widget_HUDBox_Jetpack_C.ExecuteUbergraph_Widget_HUDBox_Jetpack
struct UWidget_HUDBox_Jetpack_C_ExecuteUbergraph_Widget_HUDBox_Jetpack_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
