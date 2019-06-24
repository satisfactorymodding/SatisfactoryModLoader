#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SpaceElevator_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.DisplayEarlyAccessBlocker
struct UWidget_SpaceElevator_C_DisplayEarlyAccessBlocker_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.UpdateHeaderText
struct UWidget_SpaceElevator_C_UpdateHeaderText_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetStatusText
struct UWidget_SpaceElevator_C_SetStatusText_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               Pulsing;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.UpdatePhaseInfo
struct UWidget_SpaceElevator_C_UpdatePhaseInfo_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetUnlockTiers
struct UWidget_SpaceElevator_C_SetUnlockTiers_Params
{
	int                                                FirstUnlockTier;                                          // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	int                                                LastUnlockTier;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ClearInactiveLeverSelections
struct UWidget_SpaceElevator_C_ClearInactiveLeverSelections_Params
{
	class UWidgetAnimation*                            ActiveAnimation;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.DropInventorySlotStack
struct UWidget_SpaceElevator_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.GetPayOffContainerVisibility
struct UWidget_SpaceElevator_C_GetPayOffContainerVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetupPayOffWidgets
struct UWidget_SpaceElevator_C_SetupPayOffWidgets_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Construct
struct UWidget_SpaceElevator_C_Construct_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Init
struct UWidget_SpaceElevator_C_Init_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.PollAndSetupInventory
struct UWidget_SpaceElevator_C_PollAndSetupInventory_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.OnGamePhaseChanged
struct UWidget_SpaceElevator_C_OnGamePhaseChanged_Params
{
	TEnumAsByte<EGamePhase>                            NewGamePhase;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.On Lever Select
struct UWidget_SpaceElevator_C_On_Lever_Select_Params
{
	int                                                SelectionIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.OnUpgrade
struct UWidget_SpaceElevator_C_OnUpgrade_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Tick
struct UWidget_SpaceElevator_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ActivateSend
struct UWidget_SpaceElevator_C_ActivateSend_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSmoke
struct UWidget_SpaceElevator_C_SpawnSmoke_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSparksRight
struct UWidget_SpaceElevator_C_SpawnSparksRight_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSparksLeft
struct UWidget_SpaceElevator_C_SpawnSparksLeft_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.StartShake
struct UWidget_SpaceElevator_C_StartShake_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.StopShake
struct UWidget_SpaceElevator_C_StopShake_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ResetLever
struct UWidget_SpaceElevator_C_ResetLever_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Destruct
struct UWidget_SpaceElevator_C_Destruct_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.AnimNotify_Chime
struct UWidget_SpaceElevator_C_AnimNotify_Chime_Params
{
};

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ExecuteUbergraph_Widget_SpaceElevator
struct UWidget_SpaceElevator_C_ExecuteUbergraph_Widget_SpaceElevator_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
