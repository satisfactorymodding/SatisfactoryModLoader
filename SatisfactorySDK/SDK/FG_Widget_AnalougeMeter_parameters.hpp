#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AnalougeMeter_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_AnalougeMeter.Widget_AnalougeMeter_C.SetValue
struct UWidget_AnalougeMeter_C_SetValue_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AnalougeMeter.Widget_AnalougeMeter_C.PreConstruct
struct UWidget_AnalougeMeter_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AnalougeMeter.Widget_AnalougeMeter_C.LerpMeter
struct UWidget_AnalougeMeter_C_LerpMeter_Params
{
};

// Function Widget_AnalougeMeter.Widget_AnalougeMeter_C.Wobble
struct UWidget_AnalougeMeter_C_Wobble_Params
{
};

// Function Widget_AnalougeMeter.Widget_AnalougeMeter_C.Destruct
struct UWidget_AnalougeMeter_C_Destruct_Params
{
};

// Function Widget_AnalougeMeter.Widget_AnalougeMeter_C.ExecuteUbergraph_Widget_AnalougeMeter
struct UWidget_AnalougeMeter_C_ExecuteUbergraph_Widget_AnalougeMeter_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
