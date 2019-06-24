// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_StopVehicle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_StopVehicle.BTT_StopVehicle_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_StopVehicle_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_StopVehicle.BTT_StopVehicle_C.ReceiveExecuteAI");

	UBTT_StopVehicle_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_StopVehicle.BTT_StopVehicle_C.ReceiveTickAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_StopVehicle_C::ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_StopVehicle.BTT_StopVehicle_C.ReceiveTickAI");

	UBTT_StopVehicle_C_ReceiveTickAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_StopVehicle.BTT_StopVehicle_C.ExecuteUbergraph_BTT_StopVehicle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_StopVehicle_C::ExecuteUbergraph_BTT_StopVehicle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_StopVehicle.BTT_StopVehicle_C.ExecuteUbergraph_BTT_StopVehicle");

	UBTT_StopVehicle_C_ExecuteUbergraph_BTT_StopVehicle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
