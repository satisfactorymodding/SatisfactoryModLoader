#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManageInvites_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ManageInvites.Widget_ManageInvites_C.AddInviteToInviteList
struct UWidget_ManageInvites_C_AddInviteToInviteList_Params
{
	struct FPendingInvite                              invite;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateFriendInviteButton
struct UWidget_ManageInvites_C_UpdateFriendInviteButton_Params
{
	struct FUniqueNetIdRepl                            netId;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.SetupButtonForJoinInvite
struct UWidget_ManageInvites_C_SetupButtonForJoinInvite_Params
{
	class UWidget_Multiplayer_ListButton_C*            Button;                                                   // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, InstancedReference, ReferenceParm, IsPlainOldData)
	struct FPendingInvite                              invite;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.SetupButtonForSendInvite
struct UWidget_ManageInvites_C_SetupButtonForSendInvite_Params
{
	class UWidget_Multiplayer_ListButton_C*            Button;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FFGOnlineFriend                             onlineFriend;                                             // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateOrAddFriendsToInvite
struct UWidget_ManageInvites_C_UpdateOrAddFriendsToInvite_Params
{
	TArray<struct FFGOnlineFriend>                     UpdatedFriends;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateInviteFriendButton
struct UWidget_ManageInvites_C_UpdateInviteFriendButton_Params
{
	struct FUniqueNetIdRepl                            friendId;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.PopulateInviteList
struct UWidget_ManageInvites_C_PopulateInviteList_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.ClearInviteList
struct UWidget_ManageInvites_C_ClearInviteList_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.ClearInvitePlayerList
struct UWidget_ManageInvites_C_ClearInvitePlayerList_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.PopulateFriendsToInvite
struct UWidget_ManageInvites_C_PopulateFriendsToInvite_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.OnEscape
struct UWidget_ManageInvites_C_OnEscape_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.Construct
struct UWidget_ManageInvites_C_Construct_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.OnJoinInvite
struct UWidget_ManageInvites_C_OnJoinInvite_Params
{
	class UWidget_Multiplayer_ListButton_C*            Button;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.AddInvitePlayersDelegates
struct UWidget_ManageInvites_C_AddInvitePlayersDelegates_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.FriendListUpdated_InvitePlayerss
struct UWidget_ManageInvites_C_FriendListUpdated_InvitePlayerss_Params
{
	struct FUpdatedFriends                             UpdatedFriends;                                           // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.PresenceUpdated_InvitePlayers
struct UWidget_ManageInvites_C_PresenceUpdated_InvitePlayers_Params
{
	struct FUniqueNetIdRepl                            updatedId;                                                // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.RemoveInvitePlayersDelegates
struct UWidget_ManageInvites_C_RemoveInvitePlayersDelegates_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.AddManageInvitesDelegates
struct UWidget_ManageInvites_C_AddManageInvitesDelegates_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.FriendsPresenceUpdate_ManageInvites
struct UWidget_ManageInvites_C_FriendsPresenceUpdate_ManageInvites_Params
{
	struct FUniqueNetIdRepl                            updatedId;                                                // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.RemoveManageInvitesDelegates
struct UWidget_ManageInvites_C_RemoveManageInvitesDelegates_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.InviteReceived_ManageInvites
struct UWidget_ManageInvites_C_InviteReceived_ManageInvites_Params
{
	struct FPendingInvite                              receivedInvite;                                           // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.OnMenuExit
struct UWidget_ManageInvites_C_OnMenuExit_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool*                                              noAnimation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.BndEvt__mSwitcher_K2Node_ComponentBoundEvent_0_OnActiveWidgetSet__DelegateSignature
struct UWidget_ManageInvites_C_BndEvt__mSwitcher_K2Node_ComponentBoundEvent_0_OnActiveWidgetSet__DelegateSignature_Params
{
	class UWidget*                                     oldWidget;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget*                                     newWidget;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.OnMenuEnter
struct UWidget_ManageInvites_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.Destruct
struct UWidget_ManageInvites_C_Destruct_Params
{
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.OnInvite
struct UWidget_ManageInvites_C_OnInvite_Params
{
	class UWidget_Multiplayer_ListButton_C*            ClickedButton;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManageInvites.Widget_ManageInvites_C.ExecuteUbergraph_Widget_ManageInvites
struct UWidget_ManageInvites_C_ExecuteUbergraph_Widget_ManageInvites_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
