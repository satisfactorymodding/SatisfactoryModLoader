#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveToTargetPoint_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.OnLocationReached
struct UBTT_MoveToTargetPoint_C_OnLocationReached_Params
{
};

// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ReceiveExecuteAI
struct UBTT_MoveToTargetPoint_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ReceiveAbortAI
struct UBTT_MoveToTargetPoint_C_ReceiveAbortAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ExecuteUbergraph_BTT_MoveToTargetPoint
struct UBTT_MoveToTargetPoint_C_ExecuteUbergraph_BTT_MoveToTargetPoint_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
