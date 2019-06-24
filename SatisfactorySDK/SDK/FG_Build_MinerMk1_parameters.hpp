#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_MinerMk1_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_MinerMk1.Build_MinerMk1_C.GetExtractedResource
struct ABuild_MinerMk1_C_GetExtractedResource_Params
{
	class UClass*                                      Resource;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Build_MinerMk1.Build_MinerMk1_C.GetMiningParticles
struct ABuild_MinerMk1_C_GetMiningParticles_Params
{
	class UParticleSystem*                             FirstParticle;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UParticleSystem*                             SecondParticle;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               foundParticle;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Build_MinerMk1.Build_MinerMk1_C.UserConstructionScript
struct ABuild_MinerMk1_C_UserConstructionScript_Params
{
};

// Function Build_MinerMk1.Build_MinerMk1_C.GainedSignificance
struct ABuild_MinerMk1_C_GainedSignificance_Params
{
};

// Function Build_MinerMk1.Build_MinerMk1_C.StartProductionLoopEffects
struct ABuild_MinerMk1_C_StartProductionLoopEffects_Params
{
};

// Function Build_MinerMk1.Build_MinerMk1_C.StopProductionLoopEffects
struct ABuild_MinerMk1_C_StopProductionLoopEffects_Params
{
};

// Function Build_MinerMk1.Build_MinerMk1_C.LostSignificance
struct ABuild_MinerMk1_C_LostSignificance_Params
{
};

// Function Build_MinerMk1.Build_MinerMk1_C.ReceiveDestroyed
struct ABuild_MinerMk1_C_ReceiveDestroyed_Params
{
};

// Function Build_MinerMk1.Build_MinerMk1_C.ExecuteUbergraph_Build_MinerMk1
struct ABuild_MinerMk1_C_ExecuteUbergraph_Build_MinerMk1_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
