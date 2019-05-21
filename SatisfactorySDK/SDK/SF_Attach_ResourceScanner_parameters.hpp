#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attach_ResourceScanner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_ResourceScanner.Attach_ResourceScanner_C.UserConstructionScript
struct AAttach_ResourceScanner_C_UserConstructionScript_Params
{
};

// Function Attach_ResourceScanner.Attach_ResourceScanner_C.CustomEvent_1
struct AAttach_ResourceScanner_C_CustomEvent_1_Params
{
};

// Function Attach_ResourceScanner.Attach_ResourceScanner_C.PlayUseEffect
struct AAttach_ResourceScanner_C_PlayUseEffect_Params
{
	struct FVector*                                    UseLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Attach_ResourceScanner.Attach_ResourceScanner_C.ExecuteUbergraph_Attach_ResourceScanner
struct AAttach_ResourceScanner_C_ExecuteUbergraph_Attach_ResourceScanner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
