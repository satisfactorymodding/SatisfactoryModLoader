#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FoilagePickup_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_FoilagePickup.BP_FoilagePickup_C.UserConstructionScript
struct ABP_FoilagePickup_C_UserConstructionScript_Params
{
};

// Function BP_FoilagePickup.BP_FoilagePickup_C.PlayPickupEffect
struct ABP_FoilagePickup_C_PlayPickupEffect_Params
{
	class UFGFoliageResourceUserData**                 foliageUserData;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector*                                    atLocation;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FoilagePickup.BP_FoilagePickup_C.ExecuteUbergraph_BP_FoilagePickup
struct ABP_FoilagePickup_C_ExecuteUbergraph_BP_FoilagePickup_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
