#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerInventoryAddon_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayerInventoryAddon.Widget_PlayerInventoryAddon_C.OnInventorySlotMoveStack
struct UWidget_PlayerInventoryAddon_C_OnInventorySlotMoveStack_Params
{
	class UWidget_InventorySlot_C*                     InventorySlotSender;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayerInventoryAddon.Widget_PlayerInventoryAddon_C.SetInventoryComponents
struct UWidget_PlayerInventoryAddon_C_SetInventoryComponents_Params
{
	class UFGInventoryComponent*                       InventoryComponent;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       Trash;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayerInventoryAddon.Widget_PlayerInventoryAddon_C.Construct
struct UWidget_PlayerInventoryAddon_C_Construct_Params
{
};

// Function Widget_PlayerInventoryAddon.Widget_PlayerInventoryAddon_C.SubscribeToParentWindow
struct UWidget_PlayerInventoryAddon_C_SubscribeToParentWindow_Params
{
	class UWidget_Window_C*                            ParentWindow;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayerInventoryAddon.Widget_PlayerInventoryAddon_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_PlayerInventoryAddon_C_BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_PlayerInventoryAddon.Widget_PlayerInventoryAddon_C.ExecuteUbergraph_Widget_PlayerInventoryAddon
struct UWidget_PlayerInventoryAddon_C_ExecuteUbergraph_Widget_PlayerInventoryAddon_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerInventoryAddon.Widget_PlayerInventoryAddon_C.SlotStackMoveEvent__DelegateSignature
struct UWidget_PlayerInventoryAddon_C_SlotStackMoveEvent__DelegateSignature_Params
{
	class UWidget_InventorySlot_C*                     InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	TEnumAsByte<EInteractionDirection>                 Direction;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
