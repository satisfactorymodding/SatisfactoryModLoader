#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PowerPole_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PowerPole.Widget_PowerPole_C.UpdateHeaderText
struct UWidget_PowerPole_C_UpdateHeaderText_Params
{
};

// Function Widget_PowerPole.Widget_PowerPole_C.GetFuseVisibility
struct UWidget_PowerPole_C_GetFuseVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PowerPole.Widget_PowerPole_C.OnGetPowerCircuit
struct UWidget_PowerPole_C_OnGetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PowerPole.Widget_PowerPole_C.IsConnected
struct UWidget_PowerPole_C_IsConnected_Params
{
	bool                                               IsConnected;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PowerPole.Widget_PowerPole_C.Cleanup
struct UWidget_PowerPole_C_Cleanup_Params
{
};

// Function Widget_PowerPole.Widget_PowerPole_C.GetPowerCircuitGraphVisibility
struct UWidget_PowerPole_C_GetPowerCircuitGraphVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PowerPole.Widget_PowerPole_C.Init
struct UWidget_PowerPole_C_Init_Params
{
};

// Function Widget_PowerPole.Widget_PowerPole_C.Construct
struct UWidget_PowerPole_C_Construct_Params
{
};

// Function Widget_PowerPole.Widget_PowerPole_C.Destruct
struct UWidget_PowerPole_C_Destruct_Params
{
};

// Function Widget_PowerPole.Widget_PowerPole_C.ResetFuse
struct UWidget_PowerPole_C_ResetFuse_Params
{
};

// Function Widget_PowerPole.Widget_PowerPole_C.ExecuteUbergraph_Widget_PowerPole
struct UWidget_PowerPole_C_ExecuteUbergraph_Widget_PowerPole_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
