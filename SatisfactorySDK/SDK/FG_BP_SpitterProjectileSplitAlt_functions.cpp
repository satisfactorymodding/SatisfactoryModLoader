// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectileSplitAlt_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.UserConstructionScript
// ()

void ABP_SpitterProjectileSplitAlt_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.UserConstructionScript");

	ABP_SpitterProjectileSplitAlt_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.ReceiveBeginPlay
// ()

void ABP_SpitterProjectileSplitAlt_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.ReceiveBeginPlay");

	ABP_SpitterProjectileSplitAlt_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.PlayExplosionEffects
// ()

void ABP_SpitterProjectileSplitAlt_C::PlayExplosionEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.PlayExplosionEffects");

	ABP_SpitterProjectileSplitAlt_C_PlayExplosionEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.ExecuteUbergraph_BP_SpitterProjectileSplitAlt
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectileSplitAlt_C::ExecuteUbergraph_BP_SpitterProjectileSplitAlt(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSplitAlt.BP_SpitterProjectileSplitAlt_C.ExecuteUbergraph_BP_SpitterProjectileSplitAlt");

	ABP_SpitterProjectileSplitAlt_C_ExecuteUbergraph_BP_SpitterProjectileSplitAlt_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
