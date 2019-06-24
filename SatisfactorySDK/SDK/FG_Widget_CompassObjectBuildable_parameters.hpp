#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CompassObjectBuildable_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.Construct
struct UWidget_CompassObjectBuildable_C_Construct_Params
{
};

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.OnCompassObjectUpdated
struct UWidget_CompassObjectBuildable_C_OnCompassObjectUpdated_Params
{
};

// Function Widget_CompassObjectBuildable.Widget_CompassObjectBuildable_C.OnObjectCentered
struct UWidget_CompassObjectBuildable_C_OnObjectCentered_Params
{
	bool*                                              centered;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
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
