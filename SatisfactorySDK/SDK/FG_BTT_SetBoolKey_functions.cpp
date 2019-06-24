// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_SetBoolKey_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_SetBoolKey.BTT_SetBoolKey_C.ReceiveExecute
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_SetBoolKey_C::ReceiveExecute(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_SetBoolKey.BTT_SetBoolKey_C.ReceiveExecute");

	UBTT_SetBoolKey_C_ReceiveExecute_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_SetBoolKey.BTT_SetBoolKey_C.ExecuteUbergraph_BTT_SetBoolKey
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_SetBoolKey_C::ExecuteUbergraph_BTT_SetBoolKey(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_SetBoolKey.BTT_SetBoolKey_C.ExecuteUbergraph_BTT_SetBoolKey");

	UBTT_SetBoolKey_C_ExecuteUbergraph_BTT_SetBoolKey_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
