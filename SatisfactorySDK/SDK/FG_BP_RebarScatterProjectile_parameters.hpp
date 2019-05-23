#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_RebarScatterProjectile_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.UserConstructionScript
struct ABP_RebarScatterProjectile_C_UserConstructionScript_Params
{
};

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveBeginPlay
struct ABP_RebarScatterProjectile_C_ReceiveBeginPlay_Params
{
};

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.PlayAttachEffect
struct ABP_RebarScatterProjectile_C_PlayAttachEffect_Params
{
};

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveTick
struct ABP_RebarScatterProjectile_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveDestroyed
struct ABP_RebarScatterProjectile_C_ReceiveDestroyed_Params
{
};

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveHit
struct ABP_RebarScatterProjectile_C_ReceiveHit_Params
{
	class UPrimitiveComponent**                        MyComp;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor**                                     Other;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent**                        OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool*                                              bSelfMoved;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    HitLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FVector*                                    HitNormal;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FVector*                                    NormalImpulse;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FHitResult*                                 Hit;                                                      // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.Shot Player
struct ABP_RebarScatterProjectile_C_Shot_Player_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitNormal;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ExecuteUbergraph_BP_RebarScatterProjectile
struct ABP_RebarScatterProjectile_C_ExecuteUbergraph_BP_RebarScatterProjectile_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
