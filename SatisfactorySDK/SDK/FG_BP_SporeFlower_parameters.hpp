#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SporeFlower_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SporeFlower.BP_SporeFlower_C.SetTickStatus
struct ABP_SporeFlower_C_SetTickStatus_Params
{
	bool                                               doTick;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mReplicatedAnimPosition
struct ABP_SporeFlower_C_OnRep_mReplicatedAnimPosition_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mState
struct ABP_SporeFlower_C_OnRep_mState_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mGasState
struct ABP_SporeFlower_C_OnRep_mGasState_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.StopSporeAnimation
struct ABP_SporeFlower_C_StopSporeAnimation_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.UpdateAnimationFromState
struct ABP_SporeFlower_C_UpdateAnimationFromState_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.StartSporeAnimation
struct ABP_SporeFlower_C_StartSporeAnimation_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.GetStatePlayRate
struct ABP_SporeFlower_C_GetStatePlayRate_Params
{
	float                                              PlayRate;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SporeFlower.BP_SporeFlower_C.GetOffCooldown
struct ABP_SporeFlower_C_GetOffCooldown_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.StartReleasingGas
struct ABP_SporeFlower_C_StartReleasingGas_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.StopExpanding
struct ABP_SporeFlower_C_StopExpanding_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.StopReleasingGas
struct ABP_SporeFlower_C_StopReleasingGas_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.CondintionallyReverseExpanding
struct ABP_SporeFlower_C_CondintionallyReverseExpanding_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.ConditionallyStartExpanding
struct ABP_SporeFlower_C_ConditionallyStartExpanding_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.UserConstructionScript
struct ABP_SporeFlower_C_UserConstructionScript_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.ActivateDamage
struct ABP_SporeFlower_C_ActivateDamage_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct ABP_SporeFlower_C_BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function BP_SporeFlower.BP_SporeFlower_C.BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
struct ABP_SporeFlower_C_BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SporeFlower.BP_SporeFlower_C.SpawnGasParticles
struct ABP_SporeFlower_C_SpawnGasParticles_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.ReceiveBeginPlay
struct ABP_SporeFlower_C_ReceiveBeginPlay_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.UpdateAnimPosition
struct ABP_SporeFlower_C_UpdateAnimPosition_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.ReceiveEndPlay
struct ABP_SporeFlower_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SporeFlower.BP_SporeFlower_C.GainedSignificance
struct ABP_SporeFlower_C_GainedSignificance_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.LostSignificance
struct ABP_SporeFlower_C_LostSignificance_Params
{
};

// Function BP_SporeFlower.BP_SporeFlower_C.ExecuteUbergraph_BP_SporeFlower
struct ABP_SporeFlower_C_ExecuteUbergraph_BP_SporeFlower_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
