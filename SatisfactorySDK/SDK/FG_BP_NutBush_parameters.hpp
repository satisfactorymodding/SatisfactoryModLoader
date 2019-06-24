#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_NutBush_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_NutBush.BP_NutBush_C.GetDestroyAudioEvent
struct ABP_NutBush_C_GetDestroyAudioEvent_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_NutBush.BP_NutBush_C.GetDestroyEffect
struct ABP_NutBush_C_GetDestroyEffect_Params
{
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_NutBush.BP_NutBush_C.GetForceThreshold
struct ABP_NutBush_C_GetForceThreshold_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_NutBush.BP_NutBush_C.GetMeshComponent
struct ABP_NutBush_C_GetMeshComponent_Params
{
	class UStaticMeshComponent*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function BP_NutBush.BP_NutBush_C.IsChainsawable
struct ABP_NutBush_C_IsChainsawable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_NutBush.BP_NutBush_C.UserConstructionScript
struct ABP_NutBush_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
