// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectileSingle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.UserConstructionScript
// ()

void ABP_SpitterProjectileSingle_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.UserConstructionScript");

	ABP_SpitterProjectileSingle_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.Gravity Scale over Time__FinishedFunc
// ()

void ABP_SpitterProjectileSingle_C::Gravity_Scale_over_Time__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.Gravity Scale over Time__FinishedFunc");

	ABP_SpitterProjectileSingle_C_Gravity_Scale_over_Time__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.Gravity Scale over Time__UpdateFunc
// ()

void ABP_SpitterProjectileSingle_C::Gravity_Scale_over_Time__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.Gravity Scale over Time__UpdateFunc");

	ABP_SpitterProjectileSingle_C_Gravity_Scale_over_Time__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.ReceiveBeginPlay
// ()

void ABP_SpitterProjectileSingle_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.ReceiveBeginPlay");

	ABP_SpitterProjectileSingle_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature
// ()
// Parameters:
// class UActorComponent*         component                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           bReset                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectileSingle_C::BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature(class UActorComponent* component, bool bReset)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature");

	ABP_SpitterProjectileSingle_C_BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature_Params params;
	params.component = component;
	params.bReset = bReset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.PlayExplosionEffects
// ()

void ABP_SpitterProjectileSingle_C::PlayExplosionEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.PlayExplosionEffects");

	ABP_SpitterProjectileSingle_C_PlayExplosionEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.ExecuteUbergraph_BP_SpitterProjectileSingle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterProjectileSingle_C::ExecuteUbergraph_BP_SpitterProjectileSingle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C.ExecuteUbergraph_BP_SpitterProjectileSingle");

	ABP_SpitterProjectileSingle_C_ExecuteUbergraph_BP_SpitterProjectileSingle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
