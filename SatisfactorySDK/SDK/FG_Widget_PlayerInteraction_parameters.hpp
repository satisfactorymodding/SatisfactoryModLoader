#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerInteraction_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.GetInteractionText
struct UWidget_PlayerInteraction_C_GetInteractionText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.Construct
struct UWidget_PlayerInteraction_C_Construct_Params
{
};

// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.Tick
struct UWidget_PlayerInteraction_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.ExecuteUbergraph_Widget_PlayerInteraction
struct UWidget_PlayerInteraction_C_ExecuteUbergraph_Widget_PlayerInteraction_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
