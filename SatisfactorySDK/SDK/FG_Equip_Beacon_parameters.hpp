#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_Beacon_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_Beacon.Equip_Beacon_C.SpawnBeacon
struct AEquip_Beacon_C_SpawnBeacon_Params
{
};

// Function Equip_Beacon.Equip_Beacon_C.UserConstructionScript
struct AEquip_Beacon_C_UserConstructionScript_Params
{
};

// Function Equip_Beacon.Equip_Beacon_C.WasEquipped
struct AEquip_Beacon_C_WasEquipped_Params
{
};

// Function Equip_Beacon.Equip_Beacon_C.WasUnEquipped
struct AEquip_Beacon_C_WasUnEquipped_Params
{
};

// Function Equip_Beacon.Equip_Beacon_C.ExecuteUbergraph_Equip_Beacon
struct AEquip_Beacon_C_ExecuteUbergraph_Equip_Beacon_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
