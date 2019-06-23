#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterMelee_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SpitterMelee.BP_SpitterMelee_C.GetNewTarget
struct ABP_SpitterMelee_C_GetNewTarget_Params
{
};

// Function BP_SpitterMelee.BP_SpitterMelee_C.UserConstructionScript
struct ABP_SpitterMelee_C_UserConstructionScript_Params
{
};

// Function BP_SpitterMelee.BP_SpitterMelee_C.ReceiveActorBeginOverlap
struct ABP_SpitterMelee_C_ReceiveActorBeginOverlap_Params
{
	class AActor**                                     OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyOnParticleDone
struct ABP_SpitterMelee_C_DestroyOnParticleDone_Params
{
	class UParticleSystemComponent*                    PSystem;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyWithRagdoll
struct ABP_SpitterMelee_C_DestroyWithRagdoll_Params
{
	class UParticleSystemComponent*                    PSystem;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_SpitterMelee.BP_SpitterMelee_C.DestroyWithAirC
struct ABP_SpitterMelee_C_DestroyWithAirC_Params
{
	class UParticleSystemComponent*                    PSystem;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_SpitterMelee.BP_SpitterMelee_C.ReceiveBeginPlay
struct ABP_SpitterMelee_C_ReceiveBeginPlay_Params
{
};

// Function BP_SpitterMelee.BP_SpitterMelee_C.ExecuteUbergraph_BP_SpitterMelee
struct ABP_SpitterMelee_C_ExecuteUbergraph_BP_SpitterMelee_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
