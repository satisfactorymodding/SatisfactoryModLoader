#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Build_RailroadSwitchControl_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_RailroadSwitchControl.Build_RailroadSwitchControl_C.UserConstructionScript
struct ABuild_RailroadSwitchControl_C_UserConstructionScript_Params
{
};

// Function Build_RailroadSwitchControl.Build_RailroadSwitchControl_C.ReceiveTick
struct ABuild_RailroadSwitchControl_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_RailroadSwitchControl.Build_RailroadSwitchControl_C.ExecuteUbergraph_Build_RailroadSwitchControl
struct ABuild_RailroadSwitchControl_C_ExecuteUbergraph_Build_RailroadSwitchControl_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
