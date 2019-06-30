#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Multiplayer_ListButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateNATWarningForClient
struct UWidget_Multiplayer_ListButton_C_UpdateNATWarningForClient_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.GetHostingNATIsse
struct UWidget_Multiplayer_ListButton_C_GetHostingNATIsse_Params
{
	ECachedNATType                                     HostNAT;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	ECachedNATType                                     clientNat;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ToolTip;                                                  // (Parm, OutParm)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.GetConnectingNATIsse
struct UWidget_Multiplayer_ListButton_C_GetConnectingNATIsse_Params
{
	ECachedNATType                                     HostNAT;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	ECachedNATType                                     clientNat;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ToolTip;                                                  // (Parm, OutParm)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.IsNATIssue
struct UWidget_Multiplayer_ListButton_C_IsNATIssue_Params
{
	ECachedNATType                                     HostNAT;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	ECachedNATType                                     clientNat;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isIssue;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateNATWarningForHost
struct UWidget_Multiplayer_ListButton_C_UpdateNATWarningForHost_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForManagePlayers
struct UWidget_Multiplayer_ListButton_C_SetupForManagePlayers_Params
{
	class AFGPlayerState*                              PlayerState;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForJoinInvite
struct UWidget_Multiplayer_ListButton_C_SetupForJoinInvite_Params
{
	struct FPendingInvite                              invite;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForSendInvite
struct UWidget_Multiplayer_ListButton_C_SetupForSendInvite_Params
{
	struct FFGOnlineFriend                             _friend;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.Internal_UpdateButton
struct UWidget_Multiplayer_ListButton_C_Internal_UpdateButton_Params
{
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               IsOnline;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       AdditionalInfo;                                           // (BlueprintVisible, BlueprintReadOnly, Parm)
	int                                                PlayersInSession;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               privateSession;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                TimePlayed;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ActionButtonText;                                         // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               hideSessionInfo;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isPlayingSatisfactory;                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               hideActionButton;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               hideSecondaryActionButton;                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               disableActionButton;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       actionButtonTooltip;                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               inAGame;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FBlueprintSessionResult                     session;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               IsSelectable;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsNonInteractable;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	ECachedNATType                                     natType;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsHost;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               careAboutNAT;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForJoinGame
struct UWidget_Multiplayer_ListButton_C_SetupForJoinGame_Params
{
	struct FFGOnlineFriend                             _friend;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetButtonColor
struct UWidget_Multiplayer_ListButton_C_SetButtonColor_Params
{
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.ClearListSelection
struct UWidget_Multiplayer_ListButton_C_ClearListSelection_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateButton
struct UWidget_Multiplayer_ListButton_C_UpdateButton_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.PreConstruct
struct UWidget_Multiplayer_ListButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__ActionButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_BndEvt__ActionButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.ExecuteUbergraph_Widget_Multiplayer_ListButton
struct UWidget_Multiplayer_ListButton_C_ExecuteUbergraph_Widget_Multiplayer_ListButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnSessionDeselected__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_OnSessionDeselected__DelegateSignature_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnButtonClicked__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_OnButtonClicked__DelegateSignature_Params
{
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnSessionSelected__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_OnSessionSelected__DelegateSignature_Params
{
	struct FBlueprintSessionResult                     session;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnActionButtonClicked__DelegateSignature
struct UWidget_Multiplayer_ListButton_C_OnActionButtonClicked__DelegateSignature_Params
{
	class UWidget_Multiplayer_ListButton_C*            ClickedButton;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
