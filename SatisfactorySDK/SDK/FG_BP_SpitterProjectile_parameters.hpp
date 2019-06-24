#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectile_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.GetNewTarget
struct ABP_SpitterProjectile_C_GetNewTarget_Params
{
};

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.UserConstructionScript
struct ABP_SpitterProjectile_C_UserConstructionScript_Params
{
};

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.ReceiveBeginPlay
struct ABP_SpitterProjectile_C_ReceiveBeginPlay_Params
{
};

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.SplitProjectile
struct ABP_SpitterProjectile_C_SplitProjectile_Params
{
};

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.ReceiveTick
struct ABP_SpitterProjectile_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature
struct ABP_SpitterProjectile_C_BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature_Params
{
	class UActorComponent*                             component;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               bReset;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.PlayExplosionEffects
struct ABP_SpitterProjectile_C_PlayExplosionEffects_Params
{
};

// Function BP_SpitterProjectile.BP_SpitterProjectile_C.ExecuteUbergraph_BP_SpitterProjectile
struct ABP_SpitterProjectile_C_ExecuteUbergraph_BP_SpitterProjectile_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
