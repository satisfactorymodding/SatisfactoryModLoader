// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_WaitAtStop_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_WaitAtStop.BTT_WaitAtStop_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_WaitAtStop_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_WaitAtStop.BTT_WaitAtStop_C.ReceiveExecuteAI");

	UBTT_WaitAtStop_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_WaitAtStop.BTT_WaitAtStop_C.Done
// ()

void UBTT_WaitAtStop_C::Done()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_WaitAtStop.BTT_WaitAtStop_C.Done");

	UBTT_WaitAtStop_C_Done_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_WaitAtStop.BTT_WaitAtStop_C.ExecuteUbergraph_BTT_WaitAtStop
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_WaitAtStop_C::ExecuteUbergraph_BTT_WaitAtStop(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_WaitAtStop.BTT_WaitAtStop_C.ExecuteUbergraph_BTT_WaitAtStop");

	UBTT_WaitAtStop_C_ExecuteUbergraph_BTT_WaitAtStop_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
