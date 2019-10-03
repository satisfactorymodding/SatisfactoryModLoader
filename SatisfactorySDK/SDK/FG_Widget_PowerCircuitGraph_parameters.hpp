#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PowerCircuitGraph_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.UpdateStats
struct UWidget_PowerCircuitGraph_C_UpdateStats_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.OnMouseMove
struct UWidget_PowerCircuitGraph_C_OnMouseMove_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.SetHoverStyle
struct UWidget_PowerCircuitGraph_C_SetHoverStyle_Params
{
	class UTextBlock*                                  TextObject;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UImage*                                      BackgroundObject;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               IsHovered;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCurrentlyUsingText
struct UWidget_PowerCircuitGraph_C_GetCurrentlyUsingText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetResetFuseButtonEnabled
struct UWidget_PowerCircuitGraph_C_GetResetFuseButtonEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCapacityText
struct UWidget_PowerCircuitGraph_C_GetCapacityText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.UpdatePoints
struct UWidget_PowerCircuitGraph_C_UpdatePoints_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCapacityColorAndOpacity
struct UWidget_PowerCircuitGraph_C_GetCapacityColorAndOpacity_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetProductionColorAndOpacity
struct UWidget_PowerCircuitGraph_C_GetProductionColorAndOpacity_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetConsumptionColorAndOpacity
struct UWidget_PowerCircuitGraph_C_GetConsumptionColorAndOpacity_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_PowerCircuitGraph_C_BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mProductionButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_PowerCircuitGraph_C_BndEvt__mProductionButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_PowerCircuitGraph_C_BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature
struct UWidget_PowerCircuitGraph_C_BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mProductionButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
struct UWidget_PowerCircuitGraph_C_BndEvt__mProductionButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature
struct UWidget_PowerCircuitGraph_C_BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.Construct
struct UWidget_PowerCircuitGraph_C_Construct_Params
{
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.Tick
struct UWidget_PowerCircuitGraph_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.ExecuteUbergraph_Widget_PowerCircuitGraph
struct UWidget_PowerCircuitGraph_C_ExecuteUbergraph_Widget_PowerCircuitGraph_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
