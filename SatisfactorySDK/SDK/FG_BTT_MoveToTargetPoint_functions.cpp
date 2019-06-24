// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_MoveToTargetPoint_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.OnLocationReached
// ()

void UBTT_MoveToTargetPoint_C::OnLocationReached()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.OnLocationReached");

	UBTT_MoveToTargetPoint_C_OnLocationReached_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveToTargetPoint_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ReceiveExecuteAI");

	UBTT_MoveToTargetPoint_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ReceiveAbortAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveToTargetPoint_C::ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ReceiveAbortAI");

	UBTT_MoveToTargetPoint_C_ReceiveAbortAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ExecuteUbergraph_BTT_MoveToTargetPoint
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_MoveToTargetPoint_C::ExecuteUbergraph_BTT_MoveToTargetPoint(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_MoveToTargetPoint.BTT_MoveToTargetPoint_C.ExecuteUbergraph_BTT_MoveToTargetPoint");

	UBTT_MoveToTargetPoint_C_ExecuteUbergraph_BTT_MoveToTargetPoint_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
