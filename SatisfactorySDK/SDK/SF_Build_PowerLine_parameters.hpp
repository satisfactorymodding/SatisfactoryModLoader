#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Build_PowerLine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_PowerLine.Build_PowerLine_C.UserConstructionScript
struct ABuild_PowerLine_C_UserConstructionScript_Params
{
};

// Function Build_PowerLine.Build_PowerLine_C.ReceiveBeginPlay
struct ABuild_PowerLine_C_ReceiveBeginPlay_Params
{
};

// Function Build_PowerLine.Build_PowerLine_C.ExecuteUbergraph_Build_PowerLine
struct ABuild_PowerLine_C_ExecuteUbergraph_Build_PowerLine_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
