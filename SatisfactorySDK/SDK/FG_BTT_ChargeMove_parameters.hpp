#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_ChargeMove_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_ChargeMove.BTT_ChargeMove_C.ReceiveExecute
struct UBTT_ChargeMove_C_ReceiveExecute_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_ChargeMove.BTT_ChargeMove_C.ChargeComplete
struct UBTT_ChargeMove_C_ChargeComplete_Params
{
};

// Function BTT_ChargeMove.BTT_ChargeMove_C.ReceiveAbortAI
struct UBTT_ChargeMove_C_ReceiveAbortAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_ChargeMove.BTT_ChargeMove_C.ExecuteUbergraph_BTT_ChargeMove
struct UBTT_ChargeMove_C_ExecuteUbergraph_BTT_ChargeMove_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
