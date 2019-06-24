#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_HUD_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_HUD.BP_HUD_C.IsInventoryOpen
struct ABP_HUD_C_IsInventoryOpen_Params
{
	bool                                               IsOpen;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_HUD.BP_HUD_C.GetBP_GameUI
struct ABP_HUD_C_GetBP_GameUI_Params
{
	class UBP_GameUI_C*                                BPGameUI;                                                 // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_HUD.BP_HUD_C.SetupFrontEnd
struct ABP_HUD_C_SetupFrontEnd_Params
{
};

// Function BP_HUD.BP_HUD_C.UserConstructionScript
struct ABP_HUD_C_UserConstructionScript_Params
{
};

// Function BP_HUD.BP_HUD_C.ToggleInventoryUI
struct ABP_HUD_C_ToggleInventoryUI_Params
{
};

// Function BP_HUD.BP_HUD_C.OpenInventoryUI
struct ABP_HUD_C_OpenInventoryUI_Params
{
};

// Function BP_HUD.BP_HUD_C.OpenInteractUI
struct ABP_HUD_C_OpenInteractUI_Params
{
	class UClass**                                     WidgetClass;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject**                                    interactObject;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_HUD.BP_HUD_C.RemovePawnHUD
struct ABP_HUD_C_RemovePawnHUD_Params
{
};

// Function BP_HUD.BP_HUD_C.AddEquipmentHUD
struct ABP_HUD_C_AddEquipmentHUD_Params
{
	class UClass**                                     WidgetClass;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	EEquipmentSlot*                                    Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_HUD.BP_HUD_C.RemoveEquipmentHUD
struct ABP_HUD_C_RemoveEquipmentHUD_Params
{
	EEquipmentSlot*                                    Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_HUD.BP_HUD_C.CloseInteractUIIfOpen
struct ABP_HUD_C_CloseInteractUIIfOpen_Params
{
};

// Function BP_HUD.BP_HUD_C.ExecuteUbergraph_BP_HUD
struct ABP_HUD_C_ExecuteUbergraph_BP_HUD_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
