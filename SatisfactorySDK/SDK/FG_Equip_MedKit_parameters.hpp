#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_MedKit_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_MedKit.Equip_MedKit_C.UserConstructionScript
struct AEquip_MedKit_C_UserConstructionScript_Params
{
};

// Function Equip_MedKit.Equip_MedKit_C.WasEquipped
struct AEquip_MedKit_C_WasEquipped_Params
{
};

// Function Equip_MedKit.Equip_MedKit_C.PlayConsumeEffects
struct AEquip_MedKit_C_PlayConsumeEffects_Params
{
	class UFGConsumableDescriptor**                    consumable;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_MedKit.Equip_MedKit_C.WasUnEquipped
struct AEquip_MedKit_C_WasUnEquipped_Params
{
};

// Function Equip_MedKit.Equip_MedKit_C.ExecuteUbergraph_Equip_MedKit
struct AEquip_MedKit_C_ExecuteUbergraph_Equip_MedKit_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
