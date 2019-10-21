#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManageSession_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ManageSession.Widget_ManageSession_C.ClearIngamePlayerList
struct UWidget_ManageSession_C_ClearIngamePlayerList_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.IsHost
struct UWidget_ManageSession_C_IsHost_Params
{
	class APlayerState*                                State;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isOurself;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManageSession.Widget_ManageSession_C.DisableManagePlayers
struct UWidget_ManageSession_C_DisableManagePlayers_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.DisableSessionType
struct UWidget_ManageSession_C_DisableSessionType_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.DisableClientOptions
struct UWidget_ManageSession_C_DisableClientOptions_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.UpdateCurrentSessionType
struct UWidget_ManageSession_C_UpdateCurrentSessionType_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.PopulateManagePlayerList
struct UWidget_ManageSession_C_PopulateManagePlayerList_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.ClearLeftSelection
struct UWidget_ManageSession_C_ClearLeftSelection_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_0_onSelectionChanged__DelegateSignature
struct UWidget_ManageSession_C_BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_0_onSelectionChanged__DelegateSignature_Params
{
	class FString                                      SelectedOption;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Widget_ManageSession.Widget_ManageSession_C.OnJoinInvite
struct UWidget_ManageSession_C_OnJoinInvite_Params
{
	class UWidget_Multiplayer_ListButton_C*            Button;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageSession.Widget_ManageSession_C.SpawnAnim
struct UWidget_ManageSession_C_SpawnAnim_Params
{
	bool*                                              PlayBackgroundAnim;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManageSession.Widget_ManageSession_C.OnEscape
struct UWidget_ManageSession_C_OnEscape_Params
{
};

// Function Widget_ManageSession.Widget_ManageSession_C.OnMenuEnter
struct UWidget_ManageSession_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageSession.Widget_ManageSession_C.OnKick
struct UWidget_ManageSession_C_OnKick_Params
{
	class UWidget_Multiplayer_ListButton_C*            ClickedButton;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageSession.Widget_ManageSession_C.BndEvt__mSwitcher_K2Node_ComponentBoundEvent_1_OnActiveWidgetSet__DelegateSignature
struct UWidget_ManageSession_C_BndEvt__mSwitcher_K2Node_ComponentBoundEvent_1_OnActiveWidgetSet__DelegateSignature_Params
{
	class UWidget*                                     oldWidget;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget*                                     newWidget;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageSession.Widget_ManageSession_C.ExecuteUbergraph_Widget_ManageSession
struct UWidget_ManageSession_C_ExecuteUbergraph_Widget_ManageSession_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
