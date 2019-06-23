#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_Weapon_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.UpdateAmmoSlot
struct UWidget_HUDBox_Weapon_C_UpdateAmmoSlot_Params
{
};

// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.UpdateContent
struct UWidget_HUDBox_Weapon_C_UpdateContent_Params
{
};

// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.Tick
struct UWidget_HUDBox_Weapon_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.Construct
struct UWidget_HUDBox_Weapon_C_Construct_Params
{
};

// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.ExecuteUbergraph_Widget_HUDBox_Weapon
struct UWidget_HUDBox_Weapon_C_ExecuteUbergraph_Widget_HUDBox_Weapon_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
