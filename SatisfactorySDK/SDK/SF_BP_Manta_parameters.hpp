#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_Manta_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Manta.BP_Manta_C.UpdateMesh
struct ABP_Manta_C_UpdateMesh_Params
{
	float                                              Position;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class USkeletalMeshComponent*                      Mesh;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_Manta.BP_Manta_C.UserConstructionScript
struct ABP_Manta_C_UserConstructionScript_Params
{
};

// Function BP_Manta.BP_Manta_C.Timeline_1__FinishedFunc
struct ABP_Manta_C_Timeline_1__FinishedFunc_Params
{
};

// Function BP_Manta.BP_Manta_C.Timeline_1__UpdateFunc
struct ABP_Manta_C_Timeline_1__UpdateFunc_Params
{
};

// Function BP_Manta.BP_Manta_C.Timeline_0__FinishedFunc
struct ABP_Manta_C_Timeline_0__FinishedFunc_Params
{
};

// Function BP_Manta.BP_Manta_C.Timeline_0__UpdateFunc
struct ABP_Manta_C_Timeline_0__UpdateFunc_Params
{
};

// Function BP_Manta.BP_Manta_C.Reset
struct ABP_Manta_C_Reset_Params
{
};

// Function BP_Manta.BP_Manta_C.ReceiveTick
struct ABP_Manta_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Manta.BP_Manta_C.ReceiveBeginPlay
struct ABP_Manta_C_ReceiveBeginPlay_Params
{
};

// Function BP_Manta.BP_Manta_C.Recheck
struct ABP_Manta_C_Recheck_Params
{
};

// Function BP_Manta.BP_Manta_C.ExecuteUbergraph_BP_Manta
struct ABP_Manta_C_ExecuteUbergraph_BP_Manta_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
