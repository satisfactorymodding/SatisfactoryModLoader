#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterMeleeAlt_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SpitterMeleeAlt.BP_SpitterMeleeAlt_C.GetNewTarget
struct ABP_SpitterMeleeAlt_C_GetNewTarget_Params
{
};

// Function BP_SpitterMeleeAlt.BP_SpitterMeleeAlt_C.UserConstructionScript
struct ABP_SpitterMeleeAlt_C_UserConstructionScript_Params
{
};

// Function BP_SpitterMeleeAlt.BP_SpitterMeleeAlt_C.ReceiveBeginPlay
struct ABP_SpitterMeleeAlt_C_ReceiveBeginPlay_Params
{
};

// Function BP_SpitterMeleeAlt.BP_SpitterMeleeAlt_C.ReceiveActorBeginOverlap
struct ABP_SpitterMeleeAlt_C_ReceiveActorBeginOverlap_Params
{
	class AActor**                                     OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterMeleeAlt.BP_SpitterMeleeAlt_C.DestroyOnParticleDone
struct ABP_SpitterMeleeAlt_C_DestroyOnParticleDone_Params
{
	class UParticleSystemComponent*                    PSystem;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_SpitterMeleeAlt.BP_SpitterMeleeAlt_C.ExecuteUbergraph_BP_SpitterMeleeAlt
struct ABP_SpitterMeleeAlt_C_ExecuteUbergraph_BP_SpitterMeleeAlt_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
