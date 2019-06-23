#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PortableMiner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_PortableMiner.BP_PortableMiner_C.UserConstructionScript
struct ABP_PortableMiner_C_UserConstructionScript_Params
{
};

// Function BP_PortableMiner.BP_PortableMiner_C.ReceiveDestroyed
struct ABP_PortableMiner_C_ReceiveDestroyed_Params
{
};

// Function BP_PortableMiner.BP_PortableMiner_C.StartIsLookedAt
struct ABP_PortableMiner_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_PortableMiner.BP_PortableMiner_C.StopIsLookedAt
struct ABP_PortableMiner_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_PortableMiner.BP_PortableMiner_C.ReceiveBeginPlay
struct ABP_PortableMiner_C_ReceiveBeginPlay_Params
{
};

// Function BP_PortableMiner.BP_PortableMiner_C.ExecuteUbergraph_BP_PortableMiner
struct ABP_PortableMiner_C_ExecuteUbergraph_BP_PortableMiner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
