#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerInventory_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.SetupArmInventoryResize
struct UWidget_PlayerInventory_C_SetupArmInventoryResize_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.CheckInventorySizes
struct UWidget_PlayerInventory_C_CheckInventorySizes_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.IsArmEquipmentInventoryOutdated
struct UWidget_PlayerInventory_C_IsArmEquipmentInventoryOutdated_Params
{
	bool                                               isOutdated;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.OnPreviewKeyDown
struct UWidget_PlayerInventory_C_OnPreviewKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.OnDrop
struct UWidget_PlayerInventory_C_OnDrop_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.TryGetCentralStorages
struct UWidget_PlayerInventory_C_TryGetCentralStorages_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.OnKeyDown
struct UWidget_PlayerInventory_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.Cleanup
struct UWidget_PlayerInventory_C_Cleanup_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.SetInventoryComponents
struct UWidget_PlayerInventory_C_SetInventoryComponents_Params
{
	class UFGInventoryComponent*                       InventoryComponent;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       arms;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       Back;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       head;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGInventoryComponent*                       Trash;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.Init
struct UWidget_PlayerInventory_C_Init_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.CloseInventory
struct UWidget_PlayerInventory_C_CloseInventory_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.Destruct
struct UWidget_PlayerInventory_C_Destruct_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.Construct
struct UWidget_PlayerInventory_C_Construct_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.CentralStorageButtonClicked
struct UWidget_PlayerInventory_C_CentralStorageButtonClicked_Params
{
	class UWidget_Button_C*                            ClickedButton;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.OnCentralStorageAddedOrRemoved
struct UWidget_PlayerInventory_C_OnCentralStorageAddedOrRemoved_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_PlayerInventory_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_PlayerInventory.Widget_PlayerInventory_C.ExecuteUbergraph_Widget_PlayerInventory
struct UWidget_PlayerInventory_C_ExecuteUbergraph_Widget_PlayerInventory_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
