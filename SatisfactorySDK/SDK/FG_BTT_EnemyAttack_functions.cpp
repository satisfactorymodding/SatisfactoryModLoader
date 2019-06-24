// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_EnemyAttack_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_EnemyAttack.BTT_EnemyAttack_C.mOnAttackFailed_8426540B4FC18260A20A279426BD39C8
// ()

void UBTT_EnemyAttack_C::mOnAttackFailed_8426540B4FC18260A20A279426BD39C8()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttack.BTT_EnemyAttack_C.mOnAttackFailed_8426540B4FC18260A20A279426BD39C8");

	UBTT_EnemyAttack_C_mOnAttackFailed_8426540B4FC18260A20A279426BD39C8_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttack.BTT_EnemyAttack_C.mOnAttackFinished_8426540B4FC18260A20A279426BD39C8
// ()

void UBTT_EnemyAttack_C::mOnAttackFinished_8426540B4FC18260A20A279426BD39C8()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttack.BTT_EnemyAttack_C.mOnAttackFinished_8426540B4FC18260A20A279426BD39C8");

	UBTT_EnemyAttack_C_mOnAttackFinished_8426540B4FC18260A20A279426BD39C8_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveAbort
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttack_C::ReceiveAbort(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveAbort");

	UBTT_EnemyAttack_C_ReceiveAbort_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttack_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveExecuteAI");

	UBTT_EnemyAttack_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveAbortAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttack_C::ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttack.BTT_EnemyAttack_C.ReceiveAbortAI");

	UBTT_EnemyAttack_C_ReceiveAbortAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttack.BTT_EnemyAttack_C.ExecuteUbergraph_BTT_EnemyAttack
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttack_C::ExecuteUbergraph_BTT_EnemyAttack(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttack.BTT_EnemyAttack_C.ExecuteUbergraph_BTT_EnemyAttack");

	UBTT_EnemyAttack_C_ExecuteUbergraph_BTT_EnemyAttack_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
