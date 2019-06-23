#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectileBig_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.GetNewTarget
struct ABP_SpitterProjectileBig_C_GetNewTarget_Params
{
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.GetNewTargetLocation
struct ABP_SpitterProjectileBig_C_GetNewTargetLocation_Params
{
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.UserConstructionScript
struct ABP_SpitterProjectileBig_C_UserConstructionScript_Params
{
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.ReceiveBeginPlay
struct ABP_SpitterProjectileBig_C_ReceiveBeginPlay_Params
{
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.SplitProjectile
struct ABP_SpitterProjectileBig_C_SplitProjectile_Params
{
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.ReceiveTick
struct ABP_SpitterProjectileBig_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature
struct ABP_SpitterProjectileBig_C_BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature_Params
{
	class UActorComponent*                             component;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               bReset;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.PlayExplosionEffects
struct ABP_SpitterProjectileBig_C_PlayExplosionEffects_Params
{
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.OnTakeAnyDamage_Event_1
struct ABP_SpitterProjectileBig_C_OnTakeAnyDamage_Event_1_Params
{
	class AActor*                                      damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.SpitterDied
struct ABP_SpitterProjectileBig_C_SpitterDied_Params
{
	class AActor*                                      DeadActor;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.DestroySelf
struct ABP_SpitterProjectileBig_C_DestroySelf_Params
{
};

// Function BP_SpitterProjectileBig.BP_SpitterProjectileBig_C.ExecuteUbergraph_BP_SpitterProjectileBig
struct ABP_SpitterProjectileBig_C_ExecuteUbergraph_BP_SpitterProjectileBig_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
