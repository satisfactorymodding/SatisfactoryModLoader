#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_HazmatSuit_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.EnablePostProcessing
struct AEquip_HazmatSuit_C_EnablePostProcessing_Params
{
	bool                                               Enabled;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.AdjustDamage
struct AEquip_HazmatSuit_C_AdjustDamage_Params
{
	float*                                             damageAmount;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType**                                DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController**                                instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor**                                     damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.UserConstructionScript
struct AEquip_HazmatSuit_C_UserConstructionScript_Params
{
};

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.WasUnEquipped
struct AEquip_HazmatSuit_C_WasUnEquipped_Params
{
};

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.ReceiveTick
struct AEquip_HazmatSuit_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.WasEquipped
struct AEquip_HazmatSuit_C_WasEquipped_Params
{
};

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.ExecuteUbergraph_Equip_HazmatSuit
struct AEquip_HazmatSuit_C_ExecuteUbergraph_Equip_HazmatSuit_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
