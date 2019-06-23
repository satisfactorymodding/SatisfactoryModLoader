#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingPreview_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_BuildingPreview.BP_BuildingPreview_C.UserConstructionScript
struct ABP_BuildingPreview_C_UserConstructionScript_Params
{
};

// Function BP_BuildingPreview.BP_BuildingPreview_C.ReceiveTick
struct ABP_BuildingPreview_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BuildingPreview.BP_BuildingPreview_C.ExecuteUbergraph_BP_BuildingPreview
struct ABP_BuildingPreview_C_ExecuteUbergraph_BP_BuildingPreview_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
