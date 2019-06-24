// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Edible_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Edible.BP_Edible_C.UpdateVisiblityState
// ()

void ABP_Edible_C::UpdateVisiblityState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Edible.BP_Edible_C.UpdateVisiblityState");

	ABP_Edible_C_UpdateVisiblityState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Edible.BP_Edible_C.UserConstructionScript
// ()

void ABP_Edible_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Edible.BP_Edible_C.UserConstructionScript");

	ABP_Edible_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Edible.BP_Edible_C.PlayPickupEffect
// ()

void ABP_Edible_C::PlayPickupEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Edible.BP_Edible_C.PlayPickupEffect");

	ABP_Edible_C_PlayPickupEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Edible.BP_Edible_C.ReceiveBeginPlay
// ()

void ABP_Edible_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Edible.BP_Edible_C.ReceiveBeginPlay");

	ABP_Edible_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Edible.BP_Edible_C.ExecuteUbergraph_BP_Edible
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Edible_C::ExecuteUbergraph_BP_Edible(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Edible.BP_Edible_C.ExecuteUbergraph_BP_Edible");

	ABP_Edible_C_ExecuteUbergraph_BP_Edible_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
