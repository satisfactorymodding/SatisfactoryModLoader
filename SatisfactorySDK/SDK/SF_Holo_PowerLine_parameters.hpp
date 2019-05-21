#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Holo_PowerLine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Holo_PowerLine.Holo_PowerLine_C.UserConstructionScript
struct AHolo_PowerLine_C_UserConstructionScript_Params
{
};

// Function Holo_PowerLine.Holo_PowerLine_C.OnAutomaticPoleDisableToggle
struct AHolo_PowerLine_C_OnAutomaticPoleDisableToggle_Params
{
	bool*                                              Disabled;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Holo_PowerLine.Holo_PowerLine_C.ExecuteUbergraph_Holo_PowerLine
struct AHolo_PowerLine_C_ExecuteUbergraph_Holo_PowerLine_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
