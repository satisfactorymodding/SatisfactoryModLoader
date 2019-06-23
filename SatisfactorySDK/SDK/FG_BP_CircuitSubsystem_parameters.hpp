#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CircuitSubsystem_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_CircuitSubsystem.BP_CircuitSubsystem_C.UserConstructionScript
struct ABP_CircuitSubsystem_C_UserConstructionScript_Params
{
};

// Function BP_CircuitSubsystem.BP_CircuitSubsystem_C.PowerCircuit_OnFuseSet
struct ABP_CircuitSubsystem_C_PowerCircuit_OnFuseSet_Params
{
};

// Function BP_CircuitSubsystem.BP_CircuitSubsystem_C.Multicast_PlayFuseSetSound
struct ABP_CircuitSubsystem_C_Multicast_PlayFuseSetSound_Params
{
};

// Function BP_CircuitSubsystem.BP_CircuitSubsystem_C.ExecuteUbergraph_BP_CircuitSubsystem
struct ABP_CircuitSubsystem_C_ExecuteUbergraph_BP_CircuitSubsystem_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
