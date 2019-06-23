#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_DropPod_Repair_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.GetHasAllRepairParts
struct UWidget_DropPod_Repair_C_GetHasAllRepairParts_Params
{
	bool                                               Has_All_Parts;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.SetHasDoorBeenOpened
struct UWidget_DropPod_Repair_C_SetHasDoorBeenOpened_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.SetupScreenText
struct UWidget_DropPod_Repair_C_SetupScreenText_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.SetupCostSlot
struct UWidget_DropPod_Repair_C_SetupCostSlot_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.GetHasPartsAndPower
struct UWidget_DropPod_Repair_C_GetHasPartsAndPower_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.GetRepairButtonVisibility
struct UWidget_DropPod_Repair_C_GetRepairButtonVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.GetRepairConditionText
struct UWidget_DropPod_Repair_C_GetRepairConditionText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.BndEvt__mGrabAllButton_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UWidget_DropPod_Repair_C_BndEvt__mGrabAllButton_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.Init
struct UWidget_DropPod_Repair_C_Init_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.OnDoorOpen
struct UWidget_DropPod_Repair_C_OnDoorOpen_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.PodUnlocked
struct UWidget_DropPod_Repair_C_PodUnlocked_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.SpawnSmoke
struct UWidget_DropPod_Repair_C_SpawnSmoke_Params
{
};

// Function Widget_DropPod_Repair.Widget_DropPod_Repair_C.ExecuteUbergraph_Widget_DropPod_Repair
struct UWidget_DropPod_Repair_C_ExecuteUbergraph_Widget_DropPod_Repair_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
