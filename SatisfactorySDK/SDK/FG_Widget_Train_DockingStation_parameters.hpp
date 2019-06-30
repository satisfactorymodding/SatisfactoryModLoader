#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Train_DockingStation_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.DropInventorySlotStack
struct UWidget_Train_DockingStation_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.SetHeaderText
struct UWidget_Train_DockingStation_C_SetHeaderText_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.GetLoadingModeButton
struct UWidget_Train_DockingStation_C_GetLoadingModeButton_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.DumpAllToInventory
struct UWidget_Train_DockingStation_C_DumpAllToInventory_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.GrabAllFromInventory
struct UWidget_Train_DockingStation_C_GrabAllFromInventory_Params
{
	class UFGInventoryComponent*                       SourceComponent;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.Init
struct UWidget_Train_DockingStation_C_Init_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.Construct
struct UWidget_Train_DockingStation_C_Construct_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.GrabAllFromStorage
struct UWidget_Train_DockingStation_C_GrabAllFromStorage_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.DumpAllInStorage
struct UWidget_Train_DockingStation_C_DumpAllInStorage_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.BndEvt__Widget_SwitchButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_Train_DockingStation_C_BndEvt__Widget_SwitchButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.Tick
struct UWidget_Train_DockingStation_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature
struct UWidget_Train_DockingStation_C_BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_Train_DockingStation_C_BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Train_DockingStation.Widget_Train_DockingStation_C.ExecuteUbergraph_Widget_Train_DockingStation
struct UWidget_Train_DockingStation_C_ExecuteUbergraph_Widget_Train_DockingStation_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
