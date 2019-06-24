#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_RotateToTarget_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_RotateToTarget.BTT_RotateToTarget_C.ReceiveExecuteAI
struct UBTT_RotateToTarget_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_RotateToTarget.BTT_RotateToTarget_C.RotationComplete
struct UBTT_RotateToTarget_C_RotationComplete_Params
{
	class APawn*                                       PawnRotated;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_RotateToTarget.BTT_RotateToTarget_C.ReceiveAbortAI
struct UBTT_RotateToTarget_C_ReceiveAbortAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_RotateToTarget.BTT_RotateToTarget_C.ExecuteUbergraph_BTT_RotateToTarget
struct UBTT_RotateToTarget_C_ExecuteUbergraph_BTT_RotateToTarget_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
