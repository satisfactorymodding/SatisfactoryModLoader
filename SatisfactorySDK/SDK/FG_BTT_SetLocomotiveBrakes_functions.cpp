// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_SetLocomotiveBrakes_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_SetLocomotiveBrakes.BTT_SetLocomotiveBrakes_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_SetLocomotiveBrakes_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_SetLocomotiveBrakes.BTT_SetLocomotiveBrakes_C.ReceiveExecuteAI");

	UBTT_SetLocomotiveBrakes_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_SetLocomotiveBrakes.BTT_SetLocomotiveBrakes_C.ExecuteUbergraph_BTT_SetLocomotiveBrakes
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_SetLocomotiveBrakes_C::ExecuteUbergraph_BTT_SetLocomotiveBrakes(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_SetLocomotiveBrakes.BTT_SetLocomotiveBrakes_C.ExecuteUbergraph_BTT_SetLocomotiveBrakes");

	UBTT_SetLocomotiveBrakes_C_ExecuteUbergraph_BTT_SetLocomotiveBrakes_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
