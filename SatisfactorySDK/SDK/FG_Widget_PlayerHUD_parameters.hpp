#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerHUD_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mCollectBar_Percent
struct UWidget_PlayerHUD_C_Get_mCollectBar_Percent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_CollectBarContainer_Visibility
struct UWidget_PlayerHUD_C_Get_CollectBarContainer_Visibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnToggleInteractUI
struct UWidget_PlayerHUD_C_OnToggleInteractUI_Params
{
	bool                                               IsOpen;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      InteractWidgetClass;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnToggleInventory
struct UWidget_PlayerHUD_C_OnToggleInventory_Params
{
	bool                                               IsOpen;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.SetImageVisibility
struct UWidget_PlayerHUD_C_SetImageVisibility_Params
{
	bool                                               Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UImage*                                      Image;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnDisabledInputGateChanged
struct UWidget_PlayerHUD_C_OnDisabledInputGateChanged_Params
{
	struct FDisabledInputGate                          NewValue;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.GetVisibility_1
struct UWidget_PlayerHUD_C_GetVisibility_1_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mInputLockedTExt_Visibility
struct UWidget_PlayerHUD_C_Get_mInputLockedTExt_Visibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.GetScannerDetailsVisibility
struct UWidget_PlayerHUD_C_GetScannerDetailsVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mReviveProgressBar_Visibility
struct UWidget_PlayerHUD_C_Get_mReviveProgressBar_Visibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mReviveProgressBar_Percent
struct UWidget_PlayerHUD_C_Get_mReviveProgressBar_Percent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.PlayRadiationAnimation
struct UWidget_PlayerHUD_C_PlayRadiationAnimation_Params
{
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.StopRadiationAnimation
struct UWidget_PlayerHUD_C_StopRadiationAnimation_Params
{
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Construct
struct UWidget_PlayerHUD_C_Construct_Params
{
};

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.ExecuteUbergraph_Widget_PlayerHUD
struct UWidget_PlayerHUD_C_ExecuteUbergraph_Widget_PlayerHUD_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
