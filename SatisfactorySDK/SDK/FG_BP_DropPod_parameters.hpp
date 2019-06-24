#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DropPod_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_DropPod.BP_DropPod_C.Repair
struct ABP_DropPod_C_Repair_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DropPod.BP_DropPod_C.GetRepairAmount
struct ABP_DropPod_C_GetRepairAmount_Params
{
	struct FItemAmount                                 amount;                                                   // (Parm, OutParm)
};

// Function BP_DropPod.BP_DropPod_C.GetPowerConsumption
struct ABP_DropPod_C_GetPowerConsumption_Params
{
	float                                              POWER;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DropPod.BP_DropPod_C.NeedsPower
struct ABP_DropPod_C_NeedsPower_Params
{
	bool                                               NeedsPower;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DropPod.BP_DropPod_C.NeedsRepair
struct ABP_DropPod_C_NeedsRepair_Params
{
	bool                                               NeedsRepair;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DropPod.BP_DropPod_C.UserConstructionScript
struct ABP_DropPod_C_UserConstructionScript_Params
{
};

// Function BP_DropPod.BP_DropPod_C.RollLoot
struct ABP_DropPod_C_RollLoot_Params
{
};

// Function BP_DropPod.BP_DropPod_C.OnOpened
struct ABP_DropPod_C_OnOpened_Params
{
};

// Function BP_DropPod.BP_DropPod_C.StopIsLookedAt
struct ABP_DropPod_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_DropPod.BP_DropPod_C.StartIsLookedAt
struct ABP_DropPod_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_DropPod.BP_DropPod_C.ReceiveBeginPlay
struct ABP_DropPod_C_ReceiveBeginPlay_Params
{
};

// Function BP_DropPod.BP_DropPod_C.OnUse
struct ABP_DropPod_C_OnUse_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_DropPod.BP_DropPod_C.ExecuteUbergraph_BP_DropPod
struct ABP_DropPod_C_ExecuteUbergraph_BP_DropPod_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
