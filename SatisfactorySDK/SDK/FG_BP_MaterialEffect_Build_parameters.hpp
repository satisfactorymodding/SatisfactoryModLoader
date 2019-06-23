#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_Build_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.PlayThumpSound
struct UBP_MaterialEffect_Build_C_PlayThumpSound_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.InitMaterialParameters
struct UBP_MaterialEffect_Build_C_InitMaterialParameters_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupBounds
struct UBP_MaterialEffect_Build_C_SetupBounds_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.GotoNextStep
struct UBP_MaterialEffect_Build_C_GotoNextStep_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.CalcCostQueueNewLength
struct UBP_MaterialEffect_Build_C_CalcCostQueueNewLength_Params
{
	int                                                NewLength;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.DebugFillCostQueue
struct UBP_MaterialEffect_Build_C_DebugFillCostQueue_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.CalcDisplacementAmount
struct UBP_MaterialEffect_Build_C_CalcDisplacementAmount_Params
{
	float                                              amount;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.UpdateCostQueue
struct UBP_MaterialEffect_Build_C_UpdateCostQueue_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupCostQueue
struct UBP_MaterialEffect_Build_C_SetupCostQueue_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupDuration
struct UBP_MaterialEffect_Build_C_SetupDuration_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupMeshes
struct UBP_MaterialEffect_Build_C_SetupMeshes_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SpawnFootEmitters
struct UBP_MaterialEffect_Build_C_SpawnFootEmitters_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnUpdate
struct UBP_MaterialEffect_Build_C_OnUpdate_Params
{
	float*                                             DeltaTime;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnEnded
struct UBP_MaterialEffect_Build_C_OnEnded_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.PreStarted
struct UBP_MaterialEffect_Build_C_PreStarted_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnStarted
struct UBP_MaterialEffect_Build_C_OnStarted_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnCostActorReachedTarget
struct UBP_MaterialEffect_Build_C_OnCostActorReachedTarget_Params
{
};

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.ExecuteUbergraph_BP_MaterialEffect_Build
struct UBP_MaterialEffect_Build_C_ExecuteUbergraph_BP_MaterialEffect_Build_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
