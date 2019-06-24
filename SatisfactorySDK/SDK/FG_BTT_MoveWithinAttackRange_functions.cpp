// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveWithinAttackRange_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnFail_FB4697D6429DCDB2C971F1AA11DB20A1
// ()
// Parameters:
// TEnumAsByte<EPathFollowingResult> MovementResult                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveWithinAttackRange_C::OnFail_FB4697D6429DCDB2C971F1AA11DB20A1(TEnumAsByte<EPathFollowingResult> MovementResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnFail_FB4697D6429DCDB2C971F1AA11DB20A1");

	UBTT_MoveWithinAttackRange_C_OnFail_FB4697D6429DCDB2C971F1AA11DB20A1_Params params;
	params.MovementResult = MovementResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnSuccess_FB4697D6429DCDB2C971F1AA11DB20A1
// ()
// Parameters:
// TEnumAsByte<EPathFollowingResult> MovementResult                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveWithinAttackRange_C::OnSuccess_FB4697D6429DCDB2C971F1AA11DB20A1(TEnumAsByte<EPathFollowingResult> MovementResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnSuccess_FB4697D6429DCDB2C971F1AA11DB20A1");

	UBTT_MoveWithinAttackRange_C_OnSuccess_FB4697D6429DCDB2C971F1AA11DB20A1_Params params;
	params.MovementResult = MovementResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnFail_2F8CAD6F41C7875D308D88AD97B454B9
// ()
// Parameters:
// TEnumAsByte<EPathFollowingResult> MovementResult                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveWithinAttackRange_C::OnFail_2F8CAD6F41C7875D308D88AD97B454B9(TEnumAsByte<EPathFollowingResult> MovementResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnFail_2F8CAD6F41C7875D308D88AD97B454B9");

	UBTT_MoveWithinAttackRange_C_OnFail_2F8CAD6F41C7875D308D88AD97B454B9_Params params;
	params.MovementResult = MovementResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnSuccess_2F8CAD6F41C7875D308D88AD97B454B9
// ()
// Parameters:
// TEnumAsByte<EPathFollowingResult> MovementResult                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveWithinAttackRange_C::OnSuccess_2F8CAD6F41C7875D308D88AD97B454B9(TEnumAsByte<EPathFollowingResult> MovementResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.OnSuccess_2F8CAD6F41C7875D308D88AD97B454B9");

	UBTT_MoveWithinAttackRange_C_OnSuccess_2F8CAD6F41C7875D308D88AD97B454B9_Params params;
	params.MovementResult = MovementResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveWithinAttackRange_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.ReceiveExecuteAI");

	UBTT_MoveWithinAttackRange_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.ExecuteUbergraph_BTT_MoveWithinAttackRange
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveWithinAttackRange_C::ExecuteUbergraph_BTT_MoveWithinAttackRange(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveWithinAttackRange.BTT_MoveWithinAttackRange_C.ExecuteUbergraph_BTT_MoveWithinAttackRange");

	UBTT_MoveWithinAttackRange_C_ExecuteUbergraph_BTT_MoveWithinAttackRange_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
