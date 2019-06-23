#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_MinerMk2_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_MinerMk2.Build_MinerMk2_C.GetMiningParticles
struct ABuild_MinerMk2_C_GetMiningParticles_Params
{
	class UParticleSystem*                             FirstParticle;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UParticleSystem*                             SecondParticle;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               foundParticle;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Build_MinerMk2.Build_MinerMk2_C.GetExtractedResource
struct ABuild_MinerMk2_C_GetExtractedResource_Params
{
	class UClass*                                      Resource;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Build_MinerMk2.Build_MinerMk2_C.SetDisplayText
struct ABuild_MinerMk2_C_SetDisplayText_Params
{
	struct FText                                       newText;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Build_MinerMk2.Build_MinerMk2_C.UserConstructionScript
struct ABuild_MinerMk2_C_UserConstructionScript_Params
{
};

// Function Build_MinerMk2.Build_MinerMk2_C.GainedSignificance
struct ABuild_MinerMk2_C_GainedSignificance_Params
{
};

// Function Build_MinerMk2.Build_MinerMk2_C.LostSignificance
struct ABuild_MinerMk2_C_LostSignificance_Params
{
};

// Function Build_MinerMk2.Build_MinerMk2_C.StartProductionLoopEffects
struct ABuild_MinerMk2_C_StartProductionLoopEffects_Params
{
};

// Function Build_MinerMk2.Build_MinerMk2_C.StopProductionLoopEffects
struct ABuild_MinerMk2_C_StopProductionLoopEffects_Params
{
};

// Function Build_MinerMk2.Build_MinerMk2_C.ReceiveDestroyed
struct ABuild_MinerMk2_C_ReceiveDestroyed_Params
{
};

// Function Build_MinerMk2.Build_MinerMk2_C.ExecuteUbergraph_Build_MinerMk2
struct ABuild_MinerMk2_C_ExecuteUbergraph_Build_MinerMk2_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
