#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceNode_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_ResourceNode.BP_ResourceNode_C.UserConstructionScript
struct ABP_ResourceNode_C_UserConstructionScript_Params
{
};

// Function BP_ResourceNode.BP_ResourceNode_C.GainedSignificance
struct ABP_ResourceNode_C_GainedSignificance_Params
{
};

// Function BP_ResourceNode.BP_ResourceNode_C.LostSignificance
struct ABP_ResourceNode_C_LostSignificance_Params
{
};

// Function BP_ResourceNode.BP_ResourceNode_C.ExecuteUbergraph_BP_ResourceNode
struct ABP_ResourceNode_C_ExecuteUbergraph_BP_ResourceNode_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
