// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterMelee_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpitterMelee.BP_SpitterMelee_C.GetNewTarget
// ()

void ABP_SpitterMelee_C::GetNewTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.GetNewTarget");

	ABP_SpitterMelee_C_GetNewTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMelee.BP_SpitterMelee_C.UserConstructionScript
// ()

void ABP_SpitterMelee_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.UserConstructionScript");

	ABP_SpitterMelee_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMelee.BP_SpitterMelee_C.ReceiveActorBeginOverlap
// ()
// Parameters:
// class AActor**                 OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterMelee_C::ReceiveActorBeginOverlap(class AActor** OtherActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.ReceiveActorBeginOverlap");

	ABP_SpitterMelee_C_ReceiveActorBeginOverlap_Params params;
	params.OtherActor = OtherActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyOnParticleDone
// ()
// Parameters:
// class UParticleSystemComponent* PSystem                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_SpitterMelee_C::DestroyOnParticleDone(class UParticleSystemComponent* PSystem)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyOnParticleDone");

	ABP_SpitterMelee_C_DestroyOnParticleDone_Params params;
	params.PSystem = PSystem;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyWithRagdoll
// ()
// Parameters:
// class UParticleSystemComponent* PSystem                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_SpitterMelee_C::DestroyWithRagdoll(class UParticleSystemComponent* PSystem)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyWithRagdoll");

	ABP_SpitterMelee_C_DestroyWithRagdoll_Params params;
	params.PSystem = PSystem;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyWithAirC
// ()
// Parameters:
// class UParticleSystemComponent* PSystem                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_SpitterMelee_C::DestroyWithAirC(class UParticleSystemComponent* PSystem)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyWithAirC");

	ABP_SpitterMelee_C_DestroyWithAirC_Params params;
	params.PSystem = PSystem;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMelee.BP_SpitterMelee_C.ReceiveBeginPlay
// ()

void ABP_SpitterMelee_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.ReceiveBeginPlay");

	ABP_SpitterMelee_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMelee.BP_SpitterMelee_C.ExecuteUbergraph_BP_SpitterMelee
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterMelee_C::ExecuteUbergraph_BP_SpitterMelee(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMelee.BP_SpitterMelee_C.ExecuteUbergraph_BP_SpitterMelee");

	ABP_SpitterMelee_C_ExecuteUbergraph_BP_SpitterMelee_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
