// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FoilagePickup_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_FoilagePickup.BP_FoilagePickup_C.UserConstructionScript
// ()

void ABP_FoilagePickup_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FoilagePickup.BP_FoilagePickup_C.UserConstructionScript");

	ABP_FoilagePickup_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FoilagePickup.BP_FoilagePickup_C.PlayPickupEffect
// ()
// Parameters:
// class UFGFoliageResourceUserData** foliageUserData                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FVector*                atLocation                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_FoilagePickup_C::PlayPickupEffect(class UFGFoliageResourceUserData** foliageUserData, struct FVector* atLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FoilagePickup.BP_FoilagePickup_C.PlayPickupEffect");

	ABP_FoilagePickup_C_PlayPickupEffect_Params params;
	params.foliageUserData = foliageUserData;
	params.atLocation = atLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FoilagePickup.BP_FoilagePickup_C.ExecuteUbergraph_BP_FoilagePickup
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_FoilagePickup_C::ExecuteUbergraph_BP_FoilagePickup(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FoilagePickup.BP_FoilagePickup_C.ExecuteUbergraph_BP_FoilagePickup");

	ABP_FoilagePickup_C_ExecuteUbergraph_BP_FoilagePickup_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
