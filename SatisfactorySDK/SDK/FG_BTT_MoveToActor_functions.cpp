// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveToActor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_MoveToActor.BTT_MoveToActor_C.OnFail_A86C15A64D326131272CCA93E74F5421
// ()
// Parameters:
// TEnumAsByte<EPathFollowingResult> MovementResult                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveToActor_C::OnFail_A86C15A64D326131272CCA93E74F5421(TEnumAsByte<EPathFollowingResult> MovementResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToActor.BTT_MoveToActor_C.OnFail_A86C15A64D326131272CCA93E74F5421");

	UBTT_MoveToActor_C_OnFail_A86C15A64D326131272CCA93E74F5421_Params params;
	params.MovementResult = MovementResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveToActor.BTT_MoveToActor_C.OnSuccess_A86C15A64D326131272CCA93E74F5421
// ()
// Parameters:
// TEnumAsByte<EPathFollowingResult> MovementResult                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveToActor_C::OnSuccess_A86C15A64D326131272CCA93E74F5421(TEnumAsByte<EPathFollowingResult> MovementResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToActor.BTT_MoveToActor_C.OnSuccess_A86C15A64D326131272CCA93E74F5421");

	UBTT_MoveToActor_C_OnSuccess_A86C15A64D326131272CCA93E74F5421_Params params;
	params.MovementResult = MovementResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveToActor.BTT_MoveToActor_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveToActor_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToActor.BTT_MoveToActor_C.ReceiveExecuteAI");

	UBTT_MoveToActor_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveToActor.BTT_MoveToActor_C.ExecuteUbergraph_BTT_MoveToActor
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveToActor_C::ExecuteUbergraph_BTT_MoveToActor(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToActor.BTT_MoveToActor_C.ExecuteUbergraph_BTT_MoveToActor");

	UBTT_MoveToActor_C_ExecuteUbergraph_BTT_MoveToActor_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
