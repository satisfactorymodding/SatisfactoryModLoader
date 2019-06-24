#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GeoThermal_Generator_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.GetFuseVisibility
struct UWidget_GeoThermal_Generator_C_GetFuseVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.OnGetPowerCircuit
struct UWidget_GeoThermal_Generator_C_OnGetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.IsConnected
struct UWidget_GeoThermal_Generator_C_IsConnected_Params
{
	bool                                               IsConnected;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.Cleanup
struct UWidget_GeoThermal_Generator_C_Cleanup_Params
{
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.GetBurnProgressPercent
struct UWidget_GeoThermal_Generator_C_GetBurnProgressPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.Init
struct UWidget_GeoThermal_Generator_C_Init_Params
{
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.Construct
struct UWidget_GeoThermal_Generator_C_Construct_Params
{
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.Destruct
struct UWidget_GeoThermal_Generator_C_Destruct_Params
{
};

// Function Widget_GeoThermal_Generator.Widget_GeoThermal_Generator_C.ExecuteUbergraph_Widget_GeoThermal_Generator
struct UWidget_GeoThermal_Generator_C_ExecuteUbergraph_Widget_GeoThermal_Generator_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
