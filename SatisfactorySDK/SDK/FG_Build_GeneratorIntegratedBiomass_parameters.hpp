#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_GeneratorIntegratedBiomass_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.CanDismantle
struct ABuild_GeneratorIntegratedBiomass_C_CanDismantle_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.UserConstructionScript
struct ABuild_GeneratorIntegratedBiomass_C_UserConstructionScript_Params
{
};

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.GainedSignificance
struct ABuild_GeneratorIntegratedBiomass_C_GainedSignificance_Params
{
};

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.StartProductionLoopEffects
struct ABuild_GeneratorIntegratedBiomass_C_StartProductionLoopEffects_Params
{
};

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.StopProductionLoopEffects
struct ABuild_GeneratorIntegratedBiomass_C_StopProductionLoopEffects_Params
{
};

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.LostSignificance
struct ABuild_GeneratorIntegratedBiomass_C_LostSignificance_Params
{
};

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.ReceiveUpdateEffects
struct ABuild_GeneratorIntegratedBiomass_C_ReceiveUpdateEffects_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_GeneratorIntegratedBiomass.Build_GeneratorIntegratedBiomass_C.ExecuteUbergraph_Build_GeneratorIntegratedBiomass
struct ABuild_GeneratorIntegratedBiomass_C_ExecuteUbergraph_Build_GeneratorIntegratedBiomass_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
