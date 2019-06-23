#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_OilPump_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_OilPump.Build_OilPump_C.GetExtractedResource
struct ABuild_OilPump_C_GetExtractedResource_Params
{
	class UClass*                                      Resource;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Build_OilPump.Build_OilPump_C.SetDisplayText
struct ABuild_OilPump_C_SetDisplayText_Params
{
	struct FText                                       newText;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Build_OilPump.Build_OilPump_C.UserConstructionScript
struct ABuild_OilPump_C_UserConstructionScript_Params
{
};

// Function Build_OilPump.Build_OilPump_C.StopIdlingLoopEffects
struct ABuild_OilPump_C_StopIdlingLoopEffects_Params
{
};

// Function Build_OilPump.Build_OilPump_C.StopProductionLoopEffects
struct ABuild_OilPump_C_StopProductionLoopEffects_Params
{
};

// Function Build_OilPump.Build_OilPump_C.LostSignificance
struct ABuild_OilPump_C_LostSignificance_Params
{
};

// Function Build_OilPump.Build_OilPump_C.GainedSignificance
struct ABuild_OilPump_C_GainedSignificance_Params
{
};

// Function Build_OilPump.Build_OilPump_C.StartIdlingLoopEffects
struct ABuild_OilPump_C_StartIdlingLoopEffects_Params
{
};

// Function Build_OilPump.Build_OilPump_C.StartProductionLoopEffects
struct ABuild_OilPump_C_StartProductionLoopEffects_Params
{
};

// Function Build_OilPump.Build_OilPump_C.ExecuteUbergraph_Build_OilPump
struct ABuild_OilPump_C_ExecuteUbergraph_Build_OilPump_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
