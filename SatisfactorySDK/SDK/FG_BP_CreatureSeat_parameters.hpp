#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CreatureSeat_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_CreatureSeat.BP_CreatureSeat_C.UserConstructionScript
struct ABP_CreatureSeat_C_UserConstructionScript_Params
{
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.InpActEvt_Use_K2Node_InputActionEvent_2
struct ABP_CreatureSeat_C_InpActEvt_Use_K2Node_InputActionEvent_2_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_1
struct ABP_CreatureSeat_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1
struct ABP_CreatureSeat_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1_Params
{
	float                                              AxisValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.UpdateCamera
struct ABP_CreatureSeat_C_UpdateCamera_Params
{
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.ReceiveTick
struct ABP_CreatureSeat_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.ReceivePossessed
struct ABP_CreatureSeat_C_ReceivePossessed_Params
{
	class AController**                                NewController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.ClientSetupHUD
struct ABP_CreatureSeat_C_ClientSetupHUD_Params
{
	class AFGPlayerController*                         Controller;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.Server_Leave
struct ABP_CreatureSeat_C_Server_Leave_Params
{
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.Server_DoAction
struct ABP_CreatureSeat_C_Server_DoAction_Params
{
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.Multicast_PlayClap
struct ABP_CreatureSeat_C_Multicast_PlayClap_Params
{
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.Server_PlayClap
struct ABP_CreatureSeat_C_Server_PlayClap_Params
{
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.PlayClap
struct ABP_CreatureSeat_C_PlayClap_Params
{
};

// Function BP_CreatureSeat.BP_CreatureSeat_C.ExecuteUbergraph_BP_CreatureSeat
struct ABP_CreatureSeat_C_ExecuteUbergraph_BP_CreatureSeat_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
