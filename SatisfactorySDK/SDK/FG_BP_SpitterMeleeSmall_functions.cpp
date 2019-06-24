// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterMeleeSmall_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.GetNewTarget
// ()

void ABP_SpitterMeleeSmall_C::GetNewTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.GetNewTarget");

	ABP_SpitterMeleeSmall_C_GetNewTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.UserConstructionScript
// ()

void ABP_SpitterMeleeSmall_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.UserConstructionScript");

	ABP_SpitterMeleeSmall_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ReceiveBeginPlay
// ()

void ABP_SpitterMeleeSmall_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ReceiveBeginPlay");

	ABP_SpitterMeleeSmall_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ReceiveActorBeginOverlap
// ()
// Parameters:
// class AActor**                 OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterMeleeSmall_C::ReceiveActorBeginOverlap(class AActor** OtherActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ReceiveActorBeginOverlap");

	ABP_SpitterMeleeSmall_C_ReceiveActorBeginOverlap_Params params;
	params.OtherActor = OtherActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.DestroyOnParticleDone
// ()
// Parameters:
// class UParticleSystemComponent* PSystem                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_SpitterMeleeSmall_C::DestroyOnParticleDone(class UParticleSystemComponent* PSystem)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.DestroyOnParticleDone");

	ABP_SpitterMeleeSmall_C_DestroyOnParticleDone_Params params;
	params.PSystem = PSystem;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ExecuteUbergraph_BP_SpitterMeleeSmall
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SpitterMeleeSmall_C::ExecuteUbergraph_BP_SpitterMeleeSmall(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ExecuteUbergraph_BP_SpitterMeleeSmall");

	ABP_SpitterMeleeSmall_C_ExecuteUbergraph_BP_SpitterMeleeSmall_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
