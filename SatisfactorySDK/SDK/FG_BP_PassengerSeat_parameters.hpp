#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PassengerSeat_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_PassengerSeat.BP_PassengerSeat_C.UserConstructionScript
struct ABP_PassengerSeat_C_UserConstructionScript_Params
{
};

// Function BP_PassengerSeat.BP_PassengerSeat_C.InpActEvt_Use_K2Node_InputActionEvent_1
struct ABP_PassengerSeat_C_InpActEvt_Use_K2Node_InputActionEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_PassengerSeat.BP_PassengerSeat_C.UpdateCamera
struct ABP_PassengerSeat_C_UpdateCamera_Params
{
};

// Function BP_PassengerSeat.BP_PassengerSeat_C.ReceivePossessed
struct ABP_PassengerSeat_C_ReceivePossessed_Params
{
	class AController**                                NewController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PassengerSeat.BP_PassengerSeat_C.ReceiveUnpossessed
struct ABP_PassengerSeat_C_ReceiveUnpossessed_Params
{
	class AController**                                OldController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PassengerSeat.BP_PassengerSeat_C.Server_Leave
struct ABP_PassengerSeat_C_Server_Leave_Params
{
};

// Function BP_PassengerSeat.BP_PassengerSeat_C.ExecuteUbergraph_BP_PassengerSeat
struct ABP_PassengerSeat_C_ExecuteUbergraph_BP_PassengerSeat_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
