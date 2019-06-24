#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CostSlot_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CostSlot.Widget_CostSlot_C.GetDividerTopVisibility
struct UWidget_CostSlot_C_GetDividerTopVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CostSlot.Widget_CostSlot_C.GetItemName
struct UWidget_CostSlot_C_GetItemName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CostSlot.Widget_CostSlot_C.SetCostSlot
struct UWidget_CostSlot_C_SetCostSlot_Params
{
	int                                                SlotIdx;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CostSlot.Widget_CostSlot_C.Tick
struct UWidget_CostSlot_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CostSlot.Widget_CostSlot_C.ExecuteUbergraph_Widget_CostSlot
struct UWidget_CostSlot_C_ExecuteUbergraph_Widget_CostSlot_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
