// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_AttentionPingActor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_AttentionPingActor.BP_AttentionPingActor_C.UserConstructionScript
// ()

void ABP_AttentionPingActor_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_AttentionPingActor.BP_AttentionPingActor_C.UserConstructionScript");

	ABP_AttentionPingActor_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_AttentionPingActor.BP_AttentionPingActor_C.SpawnAttentionPingEffects
// ()

void ABP_AttentionPingActor_C::SpawnAttentionPingEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_AttentionPingActor.BP_AttentionPingActor_C.SpawnAttentionPingEffects");

	ABP_AttentionPingActor_C_SpawnAttentionPingEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_AttentionPingActor.BP_AttentionPingActor_C.ExecuteUbergraph_BP_AttentionPingActor
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_AttentionPingActor_C::ExecuteUbergraph_BP_AttentionPingActor(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_AttentionPingActor.BP_AttentionPingActor_C.ExecuteUbergraph_BP_AttentionPingActor");

	ABP_AttentionPingActor_C_ExecuteUbergraph_BP_AttentionPingActor_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
