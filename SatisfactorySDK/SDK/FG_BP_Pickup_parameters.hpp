#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Pickup_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Pickup.BP_Pickup_C.UserConstructionScript
struct ABP_Pickup_C_UserConstructionScript_Params
{
};

// Function BP_Pickup.BP_Pickup_C.StartIsLookedAt
struct ABP_Pickup_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Pickup.BP_Pickup_C.StopIsLookedAt
struct ABP_Pickup_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Pickup.BP_Pickup_C.ReceiveBeginPlay
struct ABP_Pickup_C_ReceiveBeginPlay_Params
{
};

// Function BP_Pickup.BP_Pickup_C.GainedSignificance
struct ABP_Pickup_C_GainedSignificance_Params
{
};

// Function BP_Pickup.BP_Pickup_C.LostSignificance
struct ABP_Pickup_C_LostSignificance_Params
{
};

// Function BP_Pickup.BP_Pickup_C.PlayPickupEffect
struct ABP_Pickup_C_PlayPickupEffect_Params
{
};

// Function BP_Pickup.BP_Pickup_C.ReceiveEndPlay
struct ABP_Pickup_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Pickup.BP_Pickup_C.ExecuteUbergraph_BP_Pickup
struct ABP_Pickup_C_ExecuteUbergraph_BP_Pickup_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
