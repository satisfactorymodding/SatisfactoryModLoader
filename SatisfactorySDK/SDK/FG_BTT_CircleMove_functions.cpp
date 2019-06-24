// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_CircleMove_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_CircleMove.BTT_CircleMove_C.ReceiveExecute
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_CircleMove_C::ReceiveExecute(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_CircleMove.BTT_CircleMove_C.ReceiveExecute");

	UBTT_CircleMove_C_ReceiveExecute_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_CircleMove.BTT_CircleMove_C.FinishCircleMove
// ()

void UBTT_CircleMove_C::FinishCircleMove()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_CircleMove.BTT_CircleMove_C.FinishCircleMove");

	UBTT_CircleMove_C_FinishCircleMove_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_CircleMove.BTT_CircleMove_C.ExecuteUbergraph_BTT_CircleMove
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_CircleMove_C::ExecuteUbergraph_BTT_CircleMove(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_CircleMove.BTT_CircleMove_C.ExecuteUbergraph_BTT_CircleMove");

	UBTT_CircleMove_C_ExecuteUbergraph_BTT_CircleMove_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
