#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_EnemyAttack_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_EnemyAttack.BTT_EnemyAttack_C.mOnAttackFailed_8426540B4FC18260A20A279426BD39C8
struct UBTT_EnemyAttack_C_mOnAttackFailed_8426540B4FC18260A20A279426BD39C8_Params
{
};

// Function BTT_EnemyAttack.BTT_EnemyAttack_C.mOnAttackFinished_8426540B4FC18260A20A279426BD39C8
struct UBTT_EnemyAttack_C_mOnAttackFinished_8426540B4FC18260A20A279426BD39C8_Params
{
};

// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveAbort
struct UBTT_EnemyAttack_C_ReceiveAbort_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveExecuteAI
struct UBTT_EnemyAttack_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveAbortAI
struct UBTT_EnemyAttack_C_ReceiveAbortAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ExecuteUbergraph_BTT_EnemyAttack
struct UBTT_EnemyAttack_C_ExecuteUbergraph_BTT_EnemyAttack_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
