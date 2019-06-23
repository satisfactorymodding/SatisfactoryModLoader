#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildGunDelay_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.GetWidgetVisibility
struct UWidget_BuildGunDelay_C_GetWidgetVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.Tick
struct UWidget_BuildGunDelay_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.Construct
struct UWidget_BuildGunDelay_C_Construct_Params
{
};

// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.ExecuteUbergraph_Widget_BuildGunDelay
struct UWidget_BuildGunDelay_C_ExecuteUbergraph_Widget_BuildGunDelay_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
