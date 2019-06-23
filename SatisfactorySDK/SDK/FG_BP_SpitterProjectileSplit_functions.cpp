// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectileSplit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.UserConstructionScript
// ()

void ABP_SpitterProjectileSplit_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.UserConstructionScript");

	ABP_SpitterProjectileSplit_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.ReceiveBeginPlay
// ()

void ABP_SpitterProjectileSplit_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.ReceiveBeginPlay");

	ABP_SpitterProjectileSplit_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.PlayExplosionEffects
// ()

void ABP_SpitterProjectileSplit_C::PlayExplosionEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.PlayExplosionEffects");

	ABP_SpitterProjectileSplit_C_PlayExplosionEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.ExecuteUbergraph_BP_SpitterProjectileSplit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectileSplit_C::ExecuteUbergraph_BP_SpitterProjectileSplit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplit.BP_SpitterProjectileSplit_C.ExecuteUbergraph_BP_SpitterProjectileSplit");

	ABP_SpitterProjectileSplit_C_ExecuteUbergraph_BP_SpitterProjectileSplit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
