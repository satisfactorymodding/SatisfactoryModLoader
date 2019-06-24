#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Shroom_01_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Shroom_01.BP_Shroom_01_C.GetDestroyAudioEvent
struct ABP_Shroom_01_C_GetDestroyAudioEvent_Params
{
	class UAkAudioEvent*                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Shroom_01.BP_Shroom_01_C.GetDestroyEffect
struct ABP_Shroom_01_C_GetDestroyEffect_Params
{
	class UParticleSystem*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Shroom_01.BP_Shroom_01_C.GetForceThreshold
struct ABP_Shroom_01_C_GetForceThreshold_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Shroom_01.BP_Shroom_01_C.UserConstructionScript
struct ABP_Shroom_01_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
