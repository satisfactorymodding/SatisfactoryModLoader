#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_PortableMinerDispenser_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C.UserConstructionScript
struct AEquip_PortableMinerDispenser_C_UserConstructionScript_Params
{
};

// Function Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C.SpawnPortableMiner
struct AEquip_PortableMinerDispenser_C_SpawnPortableMiner_Params
{
	class AFGResourceNode**                            resourceNode;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C.PlaySpawnEffects
struct AEquip_PortableMinerDispenser_C_PlaySpawnEffects_Params
{
	class ABP_PortableMiner_C*                         PortableMiner;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C.WasEquipped
struct AEquip_PortableMinerDispenser_C_WasEquipped_Params
{
};

// Function Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C.WasUnEquipped
struct AEquip_PortableMinerDispenser_C_WasUnEquipped_Params
{
};

// Function Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C.ExecuteUbergraph_Equip_PortableMinerDispenser
struct AEquip_PortableMinerDispenser_C_ExecuteUbergraph_Equip_PortableMinerDispenser_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
