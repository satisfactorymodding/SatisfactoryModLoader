#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingSpotLight_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.ReceiveBeginPlay
struct UBP_BuildingSpotLight_C_ReceiveBeginPlay_Params
{
};

// Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.HasPowerChanged
struct UBP_BuildingSpotLight_C_HasPowerChanged_Params
{
	bool                                               State;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BuildingSpotLight.BP_BuildingSpotLight_C.ExecuteUbergraph_BP_BuildingSpotLight
struct UBP_BuildingSpotLight_C_ExecuteUbergraph_BP_BuildingSpotLight_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
