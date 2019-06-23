// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_Dismantle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.OnStarted
// ()

void UBP_MaterialEffect_Dismantle_C::OnStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.OnStarted");

	UBP_MaterialEffect_Dismantle_C_OnStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.OnUpdate
// ()
// Parameters:
// float*                         DeltaTime                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_Dismantle_C::OnUpdate(float* DeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.OnUpdate");

	UBP_MaterialEffect_Dismantle_C_OnUpdate_Params params;
	params.DeltaTime = DeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.PreStarted
// ()

void UBP_MaterialEffect_Dismantle_C::PreStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.PreStarted");

	UBP_MaterialEffect_Dismantle_C_PreStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.ExecuteUbergraph_BP_MaterialEffect_Dismantle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_Dismantle_C::ExecuteUbergraph_BP_MaterialEffect_Dismantle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.ExecuteUbergraph_BP_MaterialEffect_Dismantle");

	UBP_MaterialEffect_Dismantle_C_ExecuteUbergraph_BP_MaterialEffect_Dismantle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
