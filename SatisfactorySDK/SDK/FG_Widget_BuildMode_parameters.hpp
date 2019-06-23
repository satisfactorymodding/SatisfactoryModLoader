#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMode_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_BuildMode.Widget_BuildMode_C.CheckHologramState
struct UWidget_BuildMode_C_CheckHologramState_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_BuildMode.Widget_BuildMode_C.GetBuildDisqualifiersVisibility
struct UWidget_BuildMode_C_GetBuildDisqualifiersVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_BuildMode.Widget_BuildMode_C.GetBuildDisqualifiersText
struct UWidget_BuildMode_C_GetBuildDisqualifiersText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMode.Widget_BuildMode_C.UpdateCost
struct UWidget_BuildMode_C_UpdateCost_Params
{
};

// Function Widget_BuildMode.Widget_BuildMode_C.CreateCostSlots
struct UWidget_BuildMode_C_CreateCostSlots_Params
{
};

// Function Widget_BuildMode.Widget_BuildMode_C.GetTextColor
struct UWidget_BuildMode_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMode.Widget_BuildMode_C.OnEscapePressed
struct UWidget_BuildMode_C_OnEscapePressed_Params
{
};

// Function Widget_BuildMode.Widget_BuildMode_C.Construct
struct UWidget_BuildMode_C_Construct_Params
{
};

// Function Widget_BuildMode.Widget_BuildMode_C.Tick
struct UWidget_BuildMode_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMode.Widget_BuildMode_C.PlayDismantleAnimation
struct UWidget_BuildMode_C_PlayDismantleAnimation_Params
{
};

// Function Widget_BuildMode.Widget_BuildMode_C.StopDismantleAnimation
struct UWidget_BuildMode_C_StopDismantleAnimation_Params
{
};

// Function Widget_BuildMode.Widget_BuildMode_C.ExecuteUbergraph_Widget_BuildMode
struct UWidget_BuildMode_C_ExecuteUbergraph_Widget_BuildMode_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
