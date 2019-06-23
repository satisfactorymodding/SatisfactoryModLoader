// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ItemPickup_Spawnable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.UserConstructionScript
// ()

void ABP_ItemPickup_Spawnable_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.UserConstructionScript");

	ABP_ItemPickup_Spawnable_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.PlayPickupEffect
// ()

void ABP_ItemPickup_Spawnable_C::PlayPickupEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.PlayPickupEffect");

	ABP_ItemPickup_Spawnable_C_PlayPickupEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.PlaySpawnEffect
// ()

void ABP_ItemPickup_Spawnable_C::PlaySpawnEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.PlaySpawnEffect");

	ABP_ItemPickup_Spawnable_C_PlaySpawnEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.ExecuteUbergraph_BP_ItemPickup_Spawnable
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ItemPickup_Spawnable_C::ExecuteUbergraph_BP_ItemPickup_Spawnable(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C.ExecuteUbergraph_BP_ItemPickup_Spawnable");

	ABP_ItemPickup_Spawnable_C_ExecuteUbergraph_BP_ItemPickup_Spawnable_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
