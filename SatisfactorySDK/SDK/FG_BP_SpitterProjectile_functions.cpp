// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectile_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.GetNewTarget
// ()

void ABP_SpitterProjectile_C::GetNewTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.GetNewTarget");

	ABP_SpitterProjectile_C_GetNewTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectile.BP_SpitterProjectile_C.UserConstructionScript
// ()

void ABP_SpitterProjectile_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.UserConstructionScript");

	ABP_SpitterProjectile_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectile.BP_SpitterProjectile_C.ReceiveBeginPlay
// ()

void ABP_SpitterProjectile_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.ReceiveBeginPlay");

	ABP_SpitterProjectile_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectile.BP_SpitterProjectile_C.SplitProjectile
// ()

void ABP_SpitterProjectile_C::SplitProjectile()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.SplitProjectile");

	ABP_SpitterProjectile_C_SplitProjectile_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectile.BP_SpitterProjectile_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectile_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.ReceiveTick");

	ABP_SpitterProjectile_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectile.BP_SpitterProjectile_C.BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature
// ()
// Parameters:
// class UActorComponent*         component                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           bReset                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectile_C::BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature(class UActorComponent* component, bool bReset)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature");

	ABP_SpitterProjectile_C_BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature_Params params;
	params.component = component;
	params.bReset = bReset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectile.BP_SpitterProjectile_C.PlayExplosionEffects
// ()

void ABP_SpitterProjectile_C::PlayExplosionEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.PlayExplosionEffects");

	ABP_SpitterProjectile_C_PlayExplosionEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectile.BP_SpitterProjectile_C.ExecuteUbergraph_BP_SpitterProjectile
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectile_C::ExecuteUbergraph_BP_SpitterProjectile(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectile.BP_SpitterProjectile_C.ExecuteUbergraph_BP_SpitterProjectile");

	ABP_SpitterProjectile_C_ExecuteUbergraph_BP_SpitterProjectile_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
