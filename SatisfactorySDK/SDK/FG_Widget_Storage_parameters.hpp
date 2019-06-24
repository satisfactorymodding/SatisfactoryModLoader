#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Storage_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Storage.Widget_Storage_C.SetInventoryComp
struct UWidget_Storage_C_SetInventoryComp_Params
{
	class UFGInventoryComponent*                       InventoryComp;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Storage.Widget_Storage_C.OnSortClicked
struct UWidget_Storage_C_OnSortClicked_Params
{
};

// Function Widget_Storage.Widget_Storage_C.OnDumpAllClicked
struct UWidget_Storage_C_OnDumpAllClicked_Params
{
};

// Function Widget_Storage.Widget_Storage_C.OnGrabAllClicked
struct UWidget_Storage_C_OnGrabAllClicked_Params
{
};

// Function Widget_Storage.Widget_Storage_C.BindStorageButtons
struct UWidget_Storage_C_BindStorageButtons_Params
{
};

// Function Widget_Storage.Widget_Storage_C.DropInventorySlotStack
struct UWidget_Storage_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Storage.Widget_Storage_C.Cleanup
struct UWidget_Storage_C_Cleanup_Params
{
};

// Function Widget_Storage.Widget_Storage_C.Init
struct UWidget_Storage_C_Init_Params
{
};

// Function Widget_Storage.Widget_Storage_C.Destruct
struct UWidget_Storage_C_Destruct_Params
{
};

// Function Widget_Storage.Widget_Storage_C.Construct
struct UWidget_Storage_C_Construct_Params
{
};

// Function Widget_Storage.Widget_Storage_C.DumpAllInStorage
struct UWidget_Storage_C_DumpAllInStorage_Params
{
};

// Function Widget_Storage.Widget_Storage_C.GrabAllFromStorage
struct UWidget_Storage_C_GrabAllFromStorage_Params
{
};

// Function Widget_Storage.Widget_Storage_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_Storage_C_BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Storage.Widget_Storage_C.OnInventoryComponentReplicated
struct UWidget_Storage_C_OnInventoryComponentReplicated_Params
{
	class AActor*                                      replicationDetailActorOwner;                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Storage.Widget_Storage_C.ExecuteUbergraph_Widget_Storage
struct UWidget_Storage_C_ExecuteUbergraph_Widget_Storage_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
