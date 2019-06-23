#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_EnemyAttackChoice_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.mOnAttackFailed_5A0EFF09427D5915F9D3B18E5D81C9BC
struct UBTT_EnemyAttackChoice_C_mOnAttackFailed_5A0EFF09427D5915F9D3B18E5D81C9BC_Params
{
};

// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.mOnAttackFinished_5A0EFF09427D5915F9D3B18E5D81C9BC
struct UBTT_EnemyAttackChoice_C_mOnAttackFinished_5A0EFF09427D5915F9D3B18E5D81C9BC_Params
{
};

// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveAbort
struct UBTT_EnemyAttackChoice_C_ReceiveAbort_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveExecuteAI
struct UBTT_EnemyAttackChoice_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveAbortAI
struct UBTT_EnemyAttackChoice_C_ReceiveAbortAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ExecuteUbergraph_BTT_EnemyAttackChoice
struct UBTT_EnemyAttackChoice_C_ExecuteUbergraph_BTT_EnemyAttackChoice_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
