// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_WalkBackSlowly_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ReceiveExecute
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_WalkBackSlowly_C::ReceiveExecute(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ReceiveExecute");

	UBTT_WalkBackSlowly_C_ReceiveExecute_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.WalkBackComplete
// ()

void UBTT_WalkBackSlowly_C::WalkBackComplete()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.WalkBackComplete");

	UBTT_WalkBackSlowly_C_WalkBackComplete_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ReceiveAbort
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_WalkBackSlowly_C::ReceiveAbort(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ReceiveAbort");

	UBTT_WalkBackSlowly_C_ReceiveAbort_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ExecuteUbergraph_BTT_WalkBackSlowly
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_WalkBackSlowly_C::ExecuteUbergraph_BTT_WalkBackSlowly(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ExecuteUbergraph_BTT_WalkBackSlowly");

	UBTT_WalkBackSlowly_C_ExecuteUbergraph_BTT_WalkBackSlowly_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
