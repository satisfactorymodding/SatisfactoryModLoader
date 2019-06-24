// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_WireBuild_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MaterialEffect_WireBuild.BP_MaterialEffect_WireBuild_C.OnStarted
// ()

void UBP_MaterialEffect_WireBuild_C::OnStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_WireBuild.BP_MaterialEffect_WireBuild_C.OnStarted");

	UBP_MaterialEffect_WireBuild_C_OnStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_WireBuild.BP_MaterialEffect_WireBuild_C.ExecuteUbergraph_BP_MaterialEffect_WireBuild
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_WireBuild_C::ExecuteUbergraph_BP_MaterialEffect_WireBuild(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_WireBuild.BP_MaterialEffect_WireBuild_C.ExecuteUbergraph_BP_MaterialEffect_WireBuild");

	UBP_MaterialEffect_WireBuild_C_ExecuteUbergraph_BP_MaterialEffect_WireBuild_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
