#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterMeleeSmall_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.GetNewTarget
struct ABP_SpitterMeleeSmall_C_GetNewTarget_Params
{
};

// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.UserConstructionScript
struct ABP_SpitterMeleeSmall_C_UserConstructionScript_Params
{
};

// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ReceiveBeginPlay
struct ABP_SpitterMeleeSmall_C_ReceiveBeginPlay_Params
{
};

// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ReceiveActorBeginOverlap
struct ABP_SpitterMeleeSmall_C_ReceiveActorBeginOverlap_Params
{
	class AActor**                                     OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.DestroyOnParticleDone
struct ABP_SpitterMeleeSmall_C_DestroyOnParticleDone_Params
{
	class UParticleSystemComponent*                    PSystem;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_SpitterMeleeSmall.BP_SpitterMeleeSmall_C.ExecuteUbergraph_BP_SpitterMeleeSmall
struct ABP_SpitterMeleeSmall_C_ExecuteUbergraph_BP_SpitterMeleeSmall_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
