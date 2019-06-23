#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Tooltip_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Tooltip.Widget_Tooltip_C.GetColorAndOpacity_1
struct UWidget_Tooltip_C_GetColorAndOpacity_1_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Tooltip.Widget_Tooltip_C.GetItemDescription
struct UWidget_Tooltip_C_GetItemDescription_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Tooltip.Widget_Tooltip_C.GetItemName
struct UWidget_Tooltip_C_GetItemName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Tooltip.Widget_Tooltip_C.Construct
struct UWidget_Tooltip_C_Construct_Params
{
};

// Function Widget_Tooltip.Widget_Tooltip_C.ExecuteUbergraph_Widget_Tooltip
struct UWidget_Tooltip_C_ExecuteUbergraph_Widget_Tooltip_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
