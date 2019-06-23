#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TakeDamageIndicator_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.SetRotation
struct UWidget_TakeDamageIndicator_C_SetRotation_Params
{
};

// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.DestroySelf
struct UWidget_TakeDamageIndicator_C_DestroySelf_Params
{
};

// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.Construct
struct UWidget_TakeDamageIndicator_C_Construct_Params
{
};

// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.Tick
struct UWidget_TakeDamageIndicator_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.ExecuteUbergraph_Widget_TakeDamageIndicator
struct UWidget_TakeDamageIndicator_C_ExecuteUbergraph_Widget_TakeDamageIndicator_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
