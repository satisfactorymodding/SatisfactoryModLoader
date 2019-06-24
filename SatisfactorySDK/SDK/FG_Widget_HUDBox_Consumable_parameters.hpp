#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_Consumable_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.Construct
struct UWidget_HUDBox_Consumable_C_Construct_Params
{
};

// Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.Tick
struct UWidget_HUDBox_Consumable_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.ExecuteUbergraph_Widget_HUDBox_Consumable
struct UWidget_HUDBox_Consumable_C_ExecuteUbergraph_Widget_HUDBox_Consumable_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
