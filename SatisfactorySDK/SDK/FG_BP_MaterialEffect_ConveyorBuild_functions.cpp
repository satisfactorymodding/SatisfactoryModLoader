// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_ConveyorBuild_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C.PreStarted
// ()

void UBP_MaterialEffect_ConveyorBuild_C::PreStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C.PreStarted");

	UBP_MaterialEffect_ConveyorBuild_C_PreStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C.OnStarted
// ()

void UBP_MaterialEffect_ConveyorBuild_C::OnStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C.OnStarted");

	UBP_MaterialEffect_ConveyorBuild_C_OnStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C.ExecuteUbergraph_BP_MaterialEffect_ConveyorBuild
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_ConveyorBuild_C::ExecuteUbergraph_BP_MaterialEffect_ConveyorBuild(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_ConveyorBuild.BP_MaterialEffect_ConveyorBuild_C.ExecuteUbergraph_BP_MaterialEffect_ConveyorBuild");

	UBP_MaterialEffect_ConveyorBuild_C_ExecuteUbergraph_BP_MaterialEffect_ConveyorBuild_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
