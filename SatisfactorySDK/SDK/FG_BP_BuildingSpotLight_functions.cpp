// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingSpotLight_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.ReceiveBeginPlay
// ()

void UBP_BuildingSpotLight_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.ReceiveBeginPlay");

	UBP_BuildingSpotLight_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.HasPowerChanged
// ()
// Parameters:
// bool                           State                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildingSpotLight_C::HasPowerChanged(bool State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.HasPowerChanged");

	UBP_BuildingSpotLight_C_HasPowerChanged_Params params;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.ExecuteUbergraph_BP_BuildingSpotLight
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildingSpotLight_C::ExecuteUbergraph_BP_BuildingSpotLight(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.ExecuteUbergraph_BP_BuildingSpotLight");

	UBP_BuildingSpotLight_C_ExecuteUbergraph_BP_BuildingSpotLight_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
