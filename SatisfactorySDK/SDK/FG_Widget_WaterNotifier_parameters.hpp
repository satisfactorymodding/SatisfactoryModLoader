#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_WaterNotifier_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_WaterNotifier.Widget_WaterNotifier_C.SetTitleText
struct UWidget_WaterNotifier_C_SetTitleText_Params
{
	struct FText                                       messageText;                                              // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_WaterNotifier.Widget_WaterNotifier_C.SetMessageText
struct UWidget_WaterNotifier_C_SetMessageText_Params
{
	struct FText                                       messageText;                                              // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_WaterNotifier.Widget_WaterNotifier_C.Construct
struct UWidget_WaterNotifier_C_Construct_Params
{
};

// Function Widget_WaterNotifier.Widget_WaterNotifier_C.RemoveNotifier
struct UWidget_WaterNotifier_C_RemoveNotifier_Params
{
};

// Function Widget_WaterNotifier.Widget_WaterNotifier_C.ExecuteUbergraph_Widget_WaterNotifier
struct UWidget_WaterNotifier_C_ExecuteUbergraph_Widget_WaterNotifier_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
