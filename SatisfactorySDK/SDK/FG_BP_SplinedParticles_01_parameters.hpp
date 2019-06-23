#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SplinedParticles_01_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.SpawnAnts
struct ABP_SplinedParticles_01_C_SpawnAnts_Params
{
};

// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.UserConstructionScript
struct ABP_SplinedParticles_01_C_UserConstructionScript_Params
{
};

// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ReceiveBeginPlay
struct ABP_SplinedParticles_01_C_ReceiveBeginPlay_Params
{
};

// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ReceiveTick
struct ABP_SplinedParticles_01_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ExecuteUbergraph_BP_SplinedParticles_01
struct ABP_SplinedParticles_01_C_ExecuteUbergraph_BP_SplinedParticles_01_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
