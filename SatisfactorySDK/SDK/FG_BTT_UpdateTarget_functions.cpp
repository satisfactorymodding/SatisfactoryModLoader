// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_UpdateTarget_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_UpdateTarget.BTT_UpdateTarget_C.ReceiveExecute
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_UpdateTarget_C::ReceiveExecute(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_UpdateTarget.BTT_UpdateTarget_C.ReceiveExecute");

	UBTT_UpdateTarget_C_ReceiveExecute_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_UpdateTarget.BTT_UpdateTarget_C.ExecuteUbergraph_BTT_UpdateTarget
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_UpdateTarget_C::ExecuteUbergraph_BTT_UpdateTarget(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_UpdateTarget.BTT_UpdateTarget_C.ExecuteUbergraph_BTT_UpdateTarget");

	UBTT_UpdateTarget_C_ExecuteUbergraph_BTT_UpdateTarget_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
