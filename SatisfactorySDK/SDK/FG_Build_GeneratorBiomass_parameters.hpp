#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_GeneratorBiomass_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_GeneratorBiomass.Build_GeneratorBiomass_C.UserConstructionScript
struct ABuild_GeneratorBiomass_C_UserConstructionScript_Params
{
};

// Function Build_GeneratorBiomass.Build_GeneratorBiomass_C.GainedSignificance
struct ABuild_GeneratorBiomass_C_GainedSignificance_Params
{
};

// Function Build_GeneratorBiomass.Build_GeneratorBiomass_C.StartProductionLoopEffects
struct ABuild_GeneratorBiomass_C_StartProductionLoopEffects_Params
{
};

// Function Build_GeneratorBiomass.Build_GeneratorBiomass_C.StopProductionLoopEffects
struct ABuild_GeneratorBiomass_C_StopProductionLoopEffects_Params
{
};

// Function Build_GeneratorBiomass.Build_GeneratorBiomass_C.LostSignificance
struct ABuild_GeneratorBiomass_C_LostSignificance_Params
{
};

// Function Build_GeneratorBiomass.Build_GeneratorBiomass_C.ReceiveUpdateEffects
struct ABuild_GeneratorBiomass_C_ReceiveUpdateEffects_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_GeneratorBiomass.Build_GeneratorBiomass_C.ExecuteUbergraph_Build_GeneratorBiomass
struct ABuild_GeneratorBiomass_C_ExecuteUbergraph_Build_GeneratorBiomass_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
