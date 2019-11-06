#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Turbine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Turbine.Widget_Turbine_C.TurnTurbine
struct UWidget_Turbine_C_TurnTurbine_Params
{
	class UPanelWidget*                                Container;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Turbine.Widget_Turbine_C.TurnEvent
struct UWidget_Turbine_C_TurnEvent_Params
{
};

// Function Widget_Turbine.Widget_Turbine_C.Destruct
struct UWidget_Turbine_C_Destruct_Params
{
};

// Function Widget_Turbine.Widget_Turbine_C.Construct
struct UWidget_Turbine_C_Construct_Params
{
};

// Function Widget_Turbine.Widget_Turbine_C.PreConstruct
struct UWidget_Turbine_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Turbine.Widget_Turbine_C.ExecuteUbergraph_Widget_Turbine
struct UWidget_Turbine_C_ExecuteUbergraph_Widget_Turbine_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
