#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_GameState_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_GameState.BP_GameState_C.DumpVisistedMapAreas
struct ABP_GameState_C_DumpVisistedMapAreas_Params
{
};

// Function BP_GameState.BP_GameState_C.DumpActorRepresentations
struct ABP_GameState_C_DumpActorRepresentations_Params
{
};

// Function BP_GameState.BP_GameState_C.UserConstructionScript
struct ABP_GameState_C_UserConstructionScript_Params
{
};

// Function BP_GameState.BP_GameState_C.ReceiveTick
struct ABP_GameState_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameState.BP_GameState_C.ExecuteUbergraph_BP_GameState
struct ABP_GameState_C_ExecuteUbergraph_BP_GameState_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
