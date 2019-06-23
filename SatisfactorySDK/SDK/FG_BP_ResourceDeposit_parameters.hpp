#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceDeposit_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_ResourceDeposit.BP_ResourceDeposit_C.UserConstructionScript
struct ABP_ResourceDeposit_C_UserConstructionScript_Params
{
};

// Function BP_ResourceDeposit.BP_ResourceDeposit_C.ReceiveBeginPlay
struct ABP_ResourceDeposit_C_ReceiveBeginPlay_Params
{
};

// Function BP_ResourceDeposit.BP_ResourceDeposit_C.PlayDepletedEffect
struct ABP_ResourceDeposit_C_PlayDepletedEffect_Params
{
	class UClass**                                     Descriptor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ResourceDeposit.BP_ResourceDeposit_C.ExecuteUbergraph_BP_ResourceDeposit
struct ABP_ResourceDeposit_C_ExecuteUbergraph_BP_ResourceDeposit_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
