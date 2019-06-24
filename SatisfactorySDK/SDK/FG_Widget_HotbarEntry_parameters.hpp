#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HotbarEntry_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetIconVisibility
struct UWidget_HotbarEntry_C_GetIconVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotTextColor
struct UWidget_HotbarEntry_C_GetSlotTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotBrush
struct UWidget_HotbarEntry_C_GetSlotBrush_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotText
struct UWidget_HotbarEntry_C_GetSlotText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetIcon
struct UWidget_HotbarEntry_C_GetIcon_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.OnHotbarUpdated
struct UWidget_HotbarEntry_C_OnHotbarUpdated_Params
{
};

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.ExecuteUbergraph_Widget_HotbarEntry
struct UWidget_HotbarEntry_C_ExecuteUbergraph_Widget_HotbarEntry_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
