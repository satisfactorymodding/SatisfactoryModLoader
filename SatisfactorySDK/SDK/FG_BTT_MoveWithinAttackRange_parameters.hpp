#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveWithinAttackRange_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnFail_FB4697D6429DCDB2C971F1AA11DB20A1
struct UBTT_MoveWithinAttackRange_C_OnFail_FB4697D6429DCDB2C971F1AA11DB20A1_Params
{
	TEnumAsByte<EPathFollowingResult>                  MovementResult;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnSuccess_FB4697D6429DCDB2C971F1AA11DB20A1
struct UBTT_MoveWithinAttackRange_C_OnSuccess_FB4697D6429DCDB2C971F1AA11DB20A1_Params
{
	TEnumAsByte<EPathFollowingResult>                  MovementResult;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnFail_2F8CAD6F41C7875D308D88AD97B454B9
struct UBTT_MoveWithinAttackRange_C_OnFail_2F8CAD6F41C7875D308D88AD97B454B9_Params
{
	TEnumAsByte<EPathFollowingResult>                  MovementResult;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnSuccess_2F8CAD6F41C7875D308D88AD97B454B9
struct UBTT_MoveWithinAttackRange_C_OnSuccess_2F8CAD6F41C7875D308D88AD97B454B9_Params
{
	TEnumAsByte<EPathFollowingResult>                  MovementResult;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.ReceiveExecuteAI
struct UBTT_MoveWithinAttackRange_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.ExecuteUbergraph_BTT_MoveWithinAttackRange
struct UBTT_MoveWithinAttackRange_C_ExecuteUbergraph_BTT_MoveWithinAttackRange_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
