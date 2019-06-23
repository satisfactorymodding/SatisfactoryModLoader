#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Spline_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Spline.BP_Spline_C.GetNextSplineIndex
struct ABP_Spline_C_GetNextSplineIndex_Params
{
	int                                                currentIndex;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                nextIndex;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Spline.BP_Spline_C.UserConstructionScript
struct ABP_Spline_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
