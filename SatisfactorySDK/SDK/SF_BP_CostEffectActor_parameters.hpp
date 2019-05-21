#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_CostEffectActor_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_CostEffectActor.BP_CostEffectActor_C.UserConstructionScript
struct ABP_CostEffectActor_C_UserConstructionScript_Params
{
};

// Function BP_CostEffectActor.BP_CostEffectActor_C.ReceiveBeginPlay
struct ABP_CostEffectActor_C_ReceiveBeginPlay_Params
{
};

// Function BP_CostEffectActor.BP_CostEffectActor_C.ReceiveTick
struct ABP_CostEffectActor_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CostEffectActor.BP_CostEffectActor_C.ExecuteUbergraph_BP_CostEffectActor
struct ABP_CostEffectActor_C_ExecuteUbergraph_BP_CostEffectActor_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CostEffectActor.BP_CostEffectActor_C.OnReachedTarget__DelegateSignature
struct ABP_CostEffectActor_C_OnReachedTarget__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
