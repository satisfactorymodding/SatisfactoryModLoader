#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_VehicleTrunk_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.OnPreviewKeyDown
struct UWidget_VehicleTrunk_C_OnPreviewKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.SetTitle
struct UWidget_VehicleTrunk_C_SetTitle_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.InitCallbacks
struct UWidget_VehicleTrunk_C_InitCallbacks_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.DropInventorySlotStack
struct UWidget_VehicleTrunk_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.SetWindowAlignment
struct UWidget_VehicleTrunk_C_SetWindowAlignment_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.CloseVehicle
struct UWidget_VehicleTrunk_C_CloseVehicle_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Cleanup
struct UWidget_VehicleTrunk_C_Cleanup_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Destruct
struct UWidget_VehicleTrunk_C_Destruct_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Init
struct UWidget_VehicleTrunk_C_Init_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.Construct
struct UWidget_VehicleTrunk_C_Construct_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.GrabAllFromVehicleStorage
struct UWidget_VehicleTrunk_C_GrabAllFromVehicleStorage_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.StoreAllInVehicleStorage
struct UWidget_VehicleTrunk_C_StoreAllInVehicleStorage_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_VehicleTrunk_C_BndEvt__mSortButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_VehicleTrunk.Widget_VehicleTrunk_C.ExecuteUbergraph_Widget_VehicleTrunk
struct UWidget_VehicleTrunk_C_ExecuteUbergraph_Widget_VehicleTrunk_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
