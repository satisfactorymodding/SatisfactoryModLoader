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
