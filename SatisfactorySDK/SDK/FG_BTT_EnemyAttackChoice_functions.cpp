// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_EnemyAttackChoice_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.mOnAttackFailed_5A0EFF09427D5915F9D3B18E5D81C9BC
// ()

void UBTT_EnemyAttackChoice_C::mOnAttackFailed_5A0EFF09427D5915F9D3B18E5D81C9BC()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.mOnAttackFailed_5A0EFF09427D5915F9D3B18E5D81C9BC");

	UBTT_EnemyAttackChoice_C_mOnAttackFailed_5A0EFF09427D5915F9D3B18E5D81C9BC_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.mOnAttackFinished_5A0EFF09427D5915F9D3B18E5D81C9BC
// ()

void UBTT_EnemyAttackChoice_C::mOnAttackFinished_5A0EFF09427D5915F9D3B18E5D81C9BC()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.mOnAttackFinished_5A0EFF09427D5915F9D3B18E5D81C9BC");

	UBTT_EnemyAttackChoice_C_mOnAttackFinished_5A0EFF09427D5915F9D3B18E5D81C9BC_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveAbort
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttackChoice_C::ReceiveAbort(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveAbort");

	UBTT_EnemyAttackChoice_C_ReceiveAbort_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttackChoice_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveExecuteAI");

	UBTT_EnemyAttackChoice_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveAbortAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttackChoice_C::ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ReceiveAbortAI");

	UBTT_EnemyAttackChoice_C_ReceiveAbortAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ExecuteUbergraph_BTT_EnemyAttackChoice
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_EnemyAttackChoice_C::ExecuteUbergraph_BTT_EnemyAttackChoice(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_EnemyAttackChoice.BTT_EnemyAttackChoice_C.ExecuteUbergraph_BTT_EnemyAttackChoice");

	UBTT_EnemyAttackChoice_C_ExecuteUbergraph_BTT_EnemyAttackChoice_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
