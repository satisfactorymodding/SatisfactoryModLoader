#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_Dismantle_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.OnStarted
struct UBP_MaterialEffect_Dismantle_C_OnStarted_Params
{
};

// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.OnUpdate
struct UBP_MaterialEffect_Dismantle_C_OnUpdate_Params
{
	float*                                             DeltaTime;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.PreStarted
struct UBP_MaterialEffect_Dismantle_C_PreStarted_Params
{
};

// Function BP_MaterialEffect_Dismantle.BP_MaterialEffect_Dismantle_C.ExecuteUbergraph_BP_MaterialEffect_Dismantle
struct UBP_MaterialEffect_Dismantle_C_ExecuteUbergraph_BP_MaterialEffect_Dismantle_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
