#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PortableMiner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PortableMiner.Widget_PortableMiner_C.DropInventorySlotStack
struct UWidget_PortableMiner_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.InitCallbacks
struct UWidget_PortableMiner_C_InitCallbacks_Params
{
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.UpdateMinerInfo
struct UWidget_PortableMiner_C_UpdateMinerInfo_Params
{
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.UpdateMinerProgress
struct UWidget_PortableMiner_C_UpdateMinerProgress_Params
{
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.Init
struct UWidget_PortableMiner_C_Init_Params
{
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.Tick
struct UWidget_PortableMiner_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.Construct
struct UWidget_PortableMiner_C_Construct_Params
{
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.BndEvt__mButtonTakeAllItems_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_PortableMiner_C_BndEvt__mButtonTakeAllItems_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.BndEvt__mButtonPickUpMiner_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_PortableMiner_C_BndEvt__mButtonPickUpMiner_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_PortableMiner.Widget_PortableMiner_C.ExecuteUbergraph_Widget_PortableMiner
struct UWidget_PortableMiner_C_ExecuteUbergraph_Widget_PortableMiner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
