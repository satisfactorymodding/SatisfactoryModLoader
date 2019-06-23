// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingPointLight_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_BuildingPointLight.BP_BuildingPointLight_C.ReceiveBeginPlay
// ()

void UBP_BuildingPointLight_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingPointLight.BP_BuildingPointLight_C.ReceiveBeginPlay");

	UBP_BuildingPointLight_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildingPointLight.BP_BuildingPointLight_C.HasPowerChanged
// ()
// Parameters:
// bool                           State                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildingPointLight_C::HasPowerChanged(bool State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingPointLight.BP_BuildingPointLight_C.HasPowerChanged");

	UBP_BuildingPointLight_C_HasPowerChanged_Params params;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildingPointLight.BP_BuildingPointLight_C.ExecuteUbergraph_BP_BuildingPointLight
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildingPointLight_C::ExecuteUbergraph_BP_BuildingPointLight(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingPointLight.BP_BuildingPointLight_C.ExecuteUbergraph_BP_BuildingPointLight");

	UBP_BuildingPointLight_C_ExecuteUbergraph_BP_BuildingPointLight_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
