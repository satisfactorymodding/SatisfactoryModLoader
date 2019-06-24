#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_StackSplitSlider_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.OnPaint
struct UWidget_StackSplitSlider_C_OnPaint_Params
{
	struct FPaintContext                               Context;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.UpdateSliderValue
struct UWidget_StackSplitSlider_C_UpdateSliderValue_Params
{
	struct FGeometry                                   MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetProgressBarPercentage
struct UWidget_StackSplitSlider_C_GetProgressBarPercentage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumInNewStackText
struct UWidget_StackSplitSlider_C_GetNumInNewStackText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumLeftAtSlot
struct UWidget_StackSplitSlider_C_GetNumLeftAtSlot_Params
{
	int                                                NumLeft;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumLeftAtSlotText
struct UWidget_StackSplitSlider_C_GetNumLeftAtSlotText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.SplitResource
struct UWidget_StackSplitSlider_C_SplitResource_Params
{
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.OnMouseButtonUp
struct UWidget_StackSplitSlider_C_OnMouseButtonUp_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.Construct
struct UWidget_StackSplitSlider_C_Construct_Params
{
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.Tick
struct UWidget_StackSplitSlider_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.ExecuteUbergraph_Widget_StackSplitSlider
struct UWidget_StackSplitSlider_C_ExecuteUbergraph_Widget_StackSplitSlider_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
