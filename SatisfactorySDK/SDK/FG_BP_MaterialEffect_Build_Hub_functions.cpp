// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_Build_Hub_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MaterialEffect_Build_Hub.BP_MaterialEffect_Build_Hub_C.PlayThumpSound
// ()

void UBP_MaterialEffect_Build_Hub_C::PlayThumpSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build_Hub.BP_MaterialEffect_Build_Hub_C.PlayThumpSound");

	UBP_MaterialEffect_Build_Hub_C_PlayThumpSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build_Hub.BP_MaterialEffect_Build_Hub_C.ExecuteUbergraph_BP_MaterialEffect_Build_Hub
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_Build_Hub_C::ExecuteUbergraph_BP_MaterialEffect_Build_Hub(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build_Hub.BP_MaterialEffect_Build_Hub_C.ExecuteUbergraph_BP_MaterialEffect_Build_Hub");

	UBP_MaterialEffect_Build_Hub_C_ExecuteUbergraph_BP_MaterialEffect_Build_Hub_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
