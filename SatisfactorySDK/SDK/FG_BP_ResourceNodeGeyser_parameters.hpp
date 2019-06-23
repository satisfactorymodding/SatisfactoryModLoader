#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceNodeGeyser_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.UserConstructionScript
struct ABP_ResourceNodeGeyser_C_UserConstructionScript_Params
{
};

// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.OnIsOccupiedChanged
struct ABP_ResourceNodeGeyser_C_OnIsOccupiedChanged_Params
{
	bool*                                              newIsOccupied;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.GainedSignificance
struct ABP_ResourceNodeGeyser_C_GainedSignificance_Params
{
};

// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.LostSignificance
struct ABP_ResourceNodeGeyser_C_LostSignificance_Params
{
};

// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.EruptLoop
struct ABP_ResourceNodeGeyser_C_EruptLoop_Params
{
};

// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.ExecuteUbergraph_BP_ResourceNodeGeyser
struct ABP_ResourceNodeGeyser_C_ExecuteUbergraph_BP_ResourceNodeGeyser_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
