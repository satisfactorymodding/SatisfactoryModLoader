#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Locomotive_HUD_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.CheckHasPower
struct UWidget_Locomotive_HUD_C_CheckHasPower_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.SetSpeedometerPosition
struct UWidget_Locomotive_HUD_C_SetSpeedometerPosition_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.GetPowerConsumptionText
struct UWidget_Locomotive_HUD_C_GetPowerConsumptionText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.GetSpeedInKMHText
struct UWidget_Locomotive_HUD_C_GetSpeedInKMHText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.Tick
struct UWidget_Locomotive_HUD_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.StartBrakeIndicatorAnim
struct UWidget_Locomotive_HUD_C_StartBrakeIndicatorAnim_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.StopBrakeIndicatorAnim
struct UWidget_Locomotive_HUD_C_StopBrakeIndicatorAnim_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.Construct
struct UWidget_Locomotive_HUD_C_Construct_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.CheckIsDocked
struct UWidget_Locomotive_HUD_C_CheckIsDocked_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.Destruct
struct UWidget_Locomotive_HUD_C_Destruct_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.UpdateStats
struct UWidget_Locomotive_HUD_C_UpdateStats_Params
{
};

// Function Widget_Locomotive_HUD.Widget_Locomotive_HUD_C.ExecuteUbergraph_Widget_Locomotive_HUD
struct UWidget_Locomotive_HUD_C_ExecuteUbergraph_Widget_Locomotive_HUD_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
