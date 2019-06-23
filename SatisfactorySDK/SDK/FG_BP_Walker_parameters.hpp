#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Walker_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Walker.BP_Walker_C.UserConstructionScript
struct ABP_Walker_C_UserConstructionScript_Params
{
};

// Function BP_Walker.BP_Walker_C.PlayConsumeItemEffect
struct ABP_Walker_C_PlayConsumeItemEffect_Params
{
	class UClass**                                     itemDescriptor;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int*                                               amount;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Walker.BP_Walker_C.ExecuteUbergraph_BP_Walker
struct ABP_Walker_C_ExecuteUbergraph_BP_Walker_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
