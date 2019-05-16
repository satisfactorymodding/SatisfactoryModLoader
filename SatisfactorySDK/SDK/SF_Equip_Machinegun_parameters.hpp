#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Equip_Machinegun_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_Machinegun.Equip_Machinegun_C.UserConstructionScript
struct AEquip_Machinegun_C_UserConstructionScript_Params
{
};

// Function Equip_Machinegun.Equip_Machinegun_C.ReceiveBeginPlay
struct AEquip_Machinegun_C_ReceiveBeginPlay_Params
{
};

// Function Equip_Machinegun.Equip_Machinegun_C.PlayReloadEffects
struct AEquip_Machinegun_C_PlayReloadEffects_Params
{
};

// Function Equip_Machinegun.Equip_Machinegun_C.ReceiveTick
struct AEquip_Machinegun_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_Machinegun.Equip_Machinegun_C.SwitchHUD
struct AEquip_Machinegun_C_SwitchHUD_Params
{
	bool                                               ShowHUD;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_Machinegun.Equip_Machinegun_C.WasUnEquipped
struct AEquip_Machinegun_C_WasUnEquipped_Params
{
};

// Function Equip_Machinegun.Equip_Machinegun_C.WasEquipped
struct AEquip_Machinegun_C_WasEquipped_Params
{
};

// Function Equip_Machinegun.Equip_Machinegun_C.PlayFireEffect
struct AEquip_Machinegun_C_PlayFireEffect_Params
{
};

// Function Equip_Machinegun.Equip_Machinegun_C.ExecuteUbergraph_Equip_Machinegun
struct AEquip_Machinegun_C_ExecuteUbergraph_Equip_Machinegun_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_Machinegun.Equip_Machinegun_C.Fire__DelegateSignature
struct AEquip_Machinegun_C_Fire__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
