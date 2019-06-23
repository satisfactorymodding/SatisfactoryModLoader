#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectileBig_Alternative_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.GetNewTarget
struct ABP_SpitterProjectileBig_Alternative_C_GetNewTarget_Params
{
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.GetNewTargetLocation
struct ABP_SpitterProjectileBig_Alternative_C_GetNewTargetLocation_Params
{
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.UserConstructionScript
struct ABP_SpitterProjectileBig_Alternative_C_UserConstructionScript_Params
{
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.ReceiveBeginPlay
struct ABP_SpitterProjectileBig_Alternative_C_ReceiveBeginPlay_Params
{
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.SplitProjectile
struct ABP_SpitterProjectileBig_Alternative_C_SplitProjectile_Params
{
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.ReceiveTick
struct ABP_SpitterProjectileBig_Alternative_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature
struct ABP_SpitterProjectileBig_Alternative_C_BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature_Params
{
	class UActorComponent*                             component;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               bReset;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.PlayExplosionEffects
struct ABP_SpitterProjectileBig_Alternative_C_PlayExplosionEffects_Params
{
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.OnTakeAnyDamage_Event_1
struct ABP_SpitterProjectileBig_Alternative_C_OnTakeAnyDamage_Event_1_Params
{
	class AActor*                                      damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SpitterProjectileBig_Alternative.BP_SpitterProjectileBig_Alternative_C.ExecuteUbergraph_BP_SpitterProjectileBig_Alternative
struct ABP_SpitterProjectileBig_Alternative_C_ExecuteUbergraph_BP_SpitterProjectileBig_Alternative_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
