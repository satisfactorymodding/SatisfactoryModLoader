// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectileVolley_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.UserConstructionScript
// ()

void ABP_SpitterProjectileVolley_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.UserConstructionScript");

	ABP_SpitterProjectileVolley_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.ReceiveBeginPlay
// ()

void ABP_SpitterProjectileVolley_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.ReceiveBeginPlay");

	ABP_SpitterProjectileVolley_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.PlayExplosionEffects
// ()

void ABP_SpitterProjectileVolley_C::PlayExplosionEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.PlayExplosionEffects");

	ABP_SpitterProjectileVolley_C_PlayExplosionEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.ExecuteUbergraph_BP_SpitterProjectileVolley
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectileVolley_C::ExecuteUbergraph_BP_SpitterProjectileVolley(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileVolley.BP_SpitterProjectileVolley_C.ExecuteUbergraph_BP_SpitterProjectileVolley");

	ABP_SpitterProjectileVolley_C_ExecuteUbergraph_BP_SpitterProjectileVolley_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
