#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CompassObjectBuildable_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.HideDescription
struct UWidget_CompassObjectBuildable_C_HideDescription_Params
{
};

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.GetAngleFromCompassCenter
struct UWidget_CompassObjectBuildable_C_GetAngleFromCompassCenter_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.Construct
struct UWidget_CompassObjectBuildable_C_Construct_Params
{
};

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.Tick
struct UWidget_CompassObjectBuildable_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.OnCompassObjectUpdated
struct UWidget_CompassObjectBuildable_C_OnCompassObjectUpdated_Params
{
};

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.ExecuteUbergraph_Widget_CompassObjectBuildable
struct UWidget_CompassObjectBuildable_C_ExecuteUbergraph_Widget_CompassObjectBuildable_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
