#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_NobeliskExplosive_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ShouldSave
struct ABP_NobeliskExplosive_C_ShouldSave_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.GatherDependencies
struct ABP_NobeliskExplosive_C_GatherDependencies_Params
{
	TArray<class UObject*>                             out_dependentObjects;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.NeedTransform
struct ABP_NobeliskExplosive_C_NeedTransform_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.UserConstructionScript
struct ABP_NobeliskExplosive_C_UserConstructionScript_Params
{
};

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.PlayExplosionEffects
struct ABP_NobeliskExplosive_C_PlayExplosionEffects_Params
{
};

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ReceiveHit
struct ABP_NobeliskExplosive_C_ReceiveHit_Params
{
	class UPrimitiveComponent**                        MyComp;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor**                                     Other;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent**                        OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool*                                              bSelfMoved;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    HitLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    HitNormal;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    NormalImpulse;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult*                                 Hit;                                                      // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ExecuteUbergraph_BP_NobeliskExplosive
struct ABP_NobeliskExplosive_C_ExecuteUbergraph_BP_NobeliskExplosive_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
