#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerEquipmentInventory_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.SetActiveSlot
struct UWidget_PlayerEquipmentInventory_C_SetActiveSlot_Params
{
	int                                                mActiveSlotIndex;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.ArmSelectionVisibility
struct UWidget_PlayerEquipmentInventory_C_ArmSelectionVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Construct
struct UWidget_PlayerEquipmentInventory_C_Construct_Params
{
};

// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Tick
struct UWidget_PlayerEquipmentInventory_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.Destruct
struct UWidget_PlayerEquipmentInventory_C_Destruct_Params
{
};

// Function Widget_PlayerEquipmentInventory.Widget_PlayerEquipmentInventory_C.ExecuteUbergraph_Widget_PlayerEquipmentInventory
struct UWidget_PlayerEquipmentInventory_C_ExecuteUbergraph_Widget_PlayerEquipmentInventory_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
