#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BerryBush_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_BerryBush.BP_BerryBush_C.GetDestroyAudioEvent
struct ABP_BerryBush_C_GetDestroyAudioEvent_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_BerryBush.BP_BerryBush_C.GetDestroyEffect
struct ABP_BerryBush_C_GetDestroyEffect_Params
{
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_BerryBush.BP_BerryBush_C.GetForceThreshold
struct ABP_BerryBush_C_GetForceThreshold_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_BerryBush.BP_BerryBush_C.GetMeshComponent
struct ABP_BerryBush_C_GetMeshComponent_Params
{
	class UStaticMeshComponent*                        ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function BP_BerryBush.BP_BerryBush_C.IsChainsawable
struct ABP_BerryBush_C_IsChainsawable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_BerryBush.BP_BerryBush_C.UserConstructionScript
struct ABP_BerryBush_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
