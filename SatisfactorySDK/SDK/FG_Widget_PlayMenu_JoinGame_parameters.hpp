#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayMenu_JoinGame_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.SetupButtonForJoinGame
struct UWidget_PlayMenu_JoinGame_C_SetupButtonForJoinGame_Params
{
	class UWidget_Multiplayer_ListButton_C*            Button;                                                   // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, InstancedReference, ReferenceParm, IsPlainOldData)
	struct FFGOnlineFriend                             _friend;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateFriendsForJoinMenu
struct UWidget_PlayMenu_JoinGame_C_UpdateFriendsForJoinMenu_Params
{
	TArray<struct FFGOnlineFriend>                     Friends;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateFriendForJoinMenu
struct UWidget_PlayMenu_JoinGame_C_UpdateFriendForJoinMenu_Params
{
	struct FUniqueNetIdRepl                            netId;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ShowSessionInfoAnim
struct UWidget_PlayMenu_JoinGame_C_ShowSessionInfoAnim_Params
{
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.SetSessionInfo
struct UWidget_PlayMenu_JoinGame_C_SetSessionInfo_Params
{
	struct FBlueprintSessionResult                     session;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ClearMultiplayerList
struct UWidget_PlayMenu_JoinGame_C_ClearMultiplayerList_Params
{
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.PopulateMultiplayerList
struct UWidget_PlayMenu_JoinGame_C_PopulateMultiplayerList_Params
{
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnJoinSession
struct UWidget_PlayMenu_JoinGame_C_OnJoinSession_Params
{
	class UWidget_Multiplayer_ListButton_C*            ClickedButton;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnNewSessionSelected
struct UWidget_PlayMenu_JoinGame_C_OnNewSessionSelected_Params
{
	struct FBlueprintSessionResult                     session;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnJoinSessionNew
struct UWidget_PlayMenu_JoinGame_C_OnJoinSessionNew_Params
{
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_PlayMenu_JoinGame_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnSessionDeselected
struct UWidget_PlayMenu_JoinGame_C_OnSessionDeselected_Params
{
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnMenuEnter
struct UWidget_PlayMenu_JoinGame_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateMultiplayerList
struct UWidget_PlayMenu_JoinGame_C_UpdateMultiplayerList_Params
{
	struct FUpdatedFriends                             UpdatedFriends;                                           // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.PresenceUpdated
struct UWidget_PlayMenu_JoinGame_C_PresenceUpdated_Params
{
	struct FUniqueNetIdRepl                            updatedId;                                                // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnMenuExit
struct UWidget_PlayMenu_JoinGame_C_OnMenuExit_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool*                                              noAnimation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ExecuteUbergraph_Widget_PlayMenu_JoinGame
struct UWidget_PlayMenu_JoinGame_C_ExecuteUbergraph_Widget_PlayMenu_JoinGame_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
