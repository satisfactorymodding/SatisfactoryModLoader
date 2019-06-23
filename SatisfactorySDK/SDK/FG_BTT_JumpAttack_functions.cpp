// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_JumpAttack_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_JumpAttack.BTT_JumpAttack_C.mOnJumpAttackFailed_2B6962824822751FCAD482A8789ABE88
// ()

void UBTT_JumpAttack_C::mOnJumpAttackFailed_2B6962824822751FCAD482A8789ABE88()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAttack.BTT_JumpAttack_C.mOnJumpAttackFailed_2B6962824822751FCAD482A8789ABE88");

	UBTT_JumpAttack_C_mOnJumpAttackFailed_2B6962824822751FCAD482A8789ABE88_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_JumpAttack.BTT_JumpAttack_C.mOnJumpAttackFinished_2B6962824822751FCAD482A8789ABE88
// ()

void UBTT_JumpAttack_C::mOnJumpAttackFinished_2B6962824822751FCAD482A8789ABE88()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAttack.BTT_JumpAttack_C.mOnJumpAttackFinished_2B6962824822751FCAD482A8789ABE88");

	UBTT_JumpAttack_C_mOnJumpAttackFinished_2B6962824822751FCAD482A8789ABE88_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_JumpAttack.BTT_JumpAttack_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_JumpAttack_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAttack.BTT_JumpAttack_C.ReceiveExecuteAI");

	UBTT_JumpAttack_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_JumpAttack.BTT_JumpAttack_C.ReceiveAbortAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_JumpAttack_C::ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAttack.BTT_JumpAttack_C.ReceiveAbortAI");

	UBTT_JumpAttack_C_ReceiveAbortAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_JumpAttack.BTT_JumpAttack_C.ExecuteUbergraph_BTT_JumpAttack
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_JumpAttack_C::ExecuteUbergraph_BTT_JumpAttack(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAttack.BTT_JumpAttack_C.ExecuteUbergraph_BTT_JumpAttack");

	UBTT_JumpAttack_C_ExecuteUbergraph_BTT_JumpAttack_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
