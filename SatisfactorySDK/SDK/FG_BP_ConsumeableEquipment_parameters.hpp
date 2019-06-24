#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ConsumeableEquipment_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.UserConstructionScript
struct ABP_ConsumeableEquipment_C_UserConstructionScript_Params
{
};

// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.PlayConsumeEffects
struct ABP_ConsumeableEquipment_C_PlayConsumeEffects_Params
{
	class UFGConsumableDescriptor**                    consumable;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.WasEquipped
struct ABP_ConsumeableEquipment_C_WasEquipped_Params
{
};

// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.ReceiveTick
struct ABP_ConsumeableEquipment_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ConsumeableEquipment.BP_ConsumeableEquipment_C.ExecuteUbergraph_BP_ConsumeableEquipment
struct ABP_ConsumeableEquipment_C_ExecuteUbergraph_BP_ConsumeableEquipment_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
