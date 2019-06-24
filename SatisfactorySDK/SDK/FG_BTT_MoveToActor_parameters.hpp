#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveToActor_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_MoveToActor.BTT_MoveToActor_C.OnFail_A86C15A64D326131272CCA93E74F5421
struct UBTT_MoveToActor_C_OnFail_A86C15A64D326131272CCA93E74F5421_Params
{
	TEnumAsByte<EPathFollowingResult>                  MovementResult;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveToActor.BTT_MoveToActor_C.OnSuccess_A86C15A64D326131272CCA93E74F5421
struct UBTT_MoveToActor_C_OnSuccess_A86C15A64D326131272CCA93E74F5421_Params
{
	TEnumAsByte<EPathFollowingResult>                  MovementResult;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveToActor.BTT_MoveToActor_C.ReceiveExecuteAI
struct UBTT_MoveToActor_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveToActor.BTT_MoveToActor_C.ExecuteUbergraph_BTT_MoveToActor
struct UBTT_MoveToActor_C_ExecuteUbergraph_BTT_MoveToActor_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
