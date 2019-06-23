// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_ChargeMove_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_ChargeMove.BTT_ChargeMove_C.ReceiveExecute
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_ChargeMove_C::ReceiveExecute(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_ChargeMove.BTT_ChargeMove_C.ReceiveExecute");

	UBTT_ChargeMove_C_ReceiveExecute_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_ChargeMove.BTT_ChargeMove_C.ChargeComplete
// ()

void UBTT_ChargeMove_C::ChargeComplete()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_ChargeMove.BTT_ChargeMove_C.ChargeComplete");

	UBTT_ChargeMove_C_ChargeComplete_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_ChargeMove.BTT_ChargeMove_C.ReceiveAbortAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_ChargeMove_C::ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_ChargeMove.BTT_ChargeMove_C.ReceiveAbortAI");

	UBTT_ChargeMove_C_ReceiveAbortAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_ChargeMove.BTT_ChargeMove_C.ExecuteUbergraph_BTT_ChargeMove
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_ChargeMove_C::ExecuteUbergraph_BTT_ChargeMove(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_ChargeMove.BTT_ChargeMove_C.ExecuteUbergraph_BTT_ChargeMove");

	UBTT_ChargeMove_C_ExecuteUbergraph_BTT_ChargeMove_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
