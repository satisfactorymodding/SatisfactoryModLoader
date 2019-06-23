#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildEffect_ConveyorBelt_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.GetSplineData
struct ABP_BuildEffect_ConveyorBelt_C_GetSplineData_Params
{
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.SpawnSplineSegment
struct ABP_BuildEffect_ConveyorBelt_C_SpawnSplineSegment_Params
{
	int                                                LoopIndex;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                SplineLength;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.InitiateSpline
struct ABP_BuildEffect_ConveyorBelt_C_InitiateSpline_Params
{
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.UserConstructionScript
struct ABP_BuildEffect_ConveyorBelt_C_UserConstructionScript_Params
{
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.MoveParticleEffect__FinishedFunc
struct ABP_BuildEffect_ConveyorBelt_C_MoveParticleEffect__FinishedFunc_Params
{
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.MoveParticleEffect__UpdateFunc
struct ABP_BuildEffect_ConveyorBelt_C_MoveParticleEffect__UpdateFunc_Params
{
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.ReceiveBeginPlay
struct ABP_BuildEffect_ConveyorBelt_C_ReceiveBeginPlay_Params
{
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.BeginEffect
struct ABP_BuildEffect_ConveyorBelt_C_BeginEffect_Params
{
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.ReceiveTick
struct ABP_BuildEffect_ConveyorBelt_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BuildEffect_ConveyorBelt.BP_BuildEffect_ConveyorBelt_C.ExecuteUbergraph_BP_BuildEffect_ConveyorBelt
struct ABP_BuildEffect_ConveyorBelt_C_ExecuteUbergraph_BP_BuildEffect_ConveyorBelt_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
