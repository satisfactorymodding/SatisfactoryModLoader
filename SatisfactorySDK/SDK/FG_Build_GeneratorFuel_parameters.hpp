#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_GeneratorFuel_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.UserConstructionScript
struct ABuild_GeneratorFuel_C_UserConstructionScript_Params
{
};

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.ReceiveUpdateEffects
struct ABuild_GeneratorFuel_C_ReceiveUpdateEffects_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.GainedSignificance
struct ABuild_GeneratorFuel_C_GainedSignificance_Params
{
};

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.StartProductionLoopEffects
struct ABuild_GeneratorFuel_C_StartProductionLoopEffects_Params
{
};

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.StopProductionLoopEffects
struct ABuild_GeneratorFuel_C_StopProductionLoopEffects_Params
{
};

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.LostSignificance
struct ABuild_GeneratorFuel_C_LostSignificance_Params
{
};

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.ExecuteUbergraph_Build_GeneratorFuel
struct ABuild_GeneratorFuel_C_ExecuteUbergraph_Build_GeneratorFuel_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
