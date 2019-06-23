// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayMenu_JoinGame_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.SetupButtonForJoinGame
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* Button                         (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, InstancedReference, ReferenceParm, IsPlainOldData)
// struct FFGOnlineFriend         _friend                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_PlayMenu_JoinGame_C::SetupButtonForJoinGame(class UWidget_Multiplayer_ListButton_C* Button, struct FFGOnlineFriend* _friend)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.SetupButtonForJoinGame");

	UWidget_PlayMenu_JoinGame_C_SetupButtonForJoinGame_Params params;
	params.Button = Button;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (_friend != nullptr)
		*_friend = params._friend;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateFriendsForJoinMenu
// ()
// Parameters:
// TArray<struct FFGOnlineFriend> Friends                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UWidget_PlayMenu_JoinGame_C::UpdateFriendsForJoinMenu(TArray<struct FFGOnlineFriend>* Friends)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateFriendsForJoinMenu");

	UWidget_PlayMenu_JoinGame_C_UpdateFriendsForJoinMenu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Friends != nullptr)
		*Friends = params.Friends;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateFriendForJoinMenu
// ()
// Parameters:
// struct FUniqueNetIdRepl        netId                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_PlayMenu_JoinGame_C::UpdateFriendForJoinMenu(const struct FUniqueNetIdRepl& netId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateFriendForJoinMenu");

	UWidget_PlayMenu_JoinGame_C_UpdateFriendForJoinMenu_Params params;
	params.netId = netId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ShowSessionInfoAnim
// ()

void UWidget_PlayMenu_JoinGame_C::ShowSessionInfoAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ShowSessionInfoAnim");

	UWidget_PlayMenu_JoinGame_C_ShowSessionInfoAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.SetSessionInfo
// ()
// Parameters:
// struct FBlueprintSessionResult session                        (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_PlayMenu_JoinGame_C::SetSessionInfo(const struct FBlueprintSessionResult& session)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.SetSessionInfo");

	UWidget_PlayMenu_JoinGame_C_SetSessionInfo_Params params;
	params.session = session;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ClearMultiplayerList
// ()

void UWidget_PlayMenu_JoinGame_C::ClearMultiplayerList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ClearMultiplayerList");

	UWidget_PlayMenu_JoinGame_C_ClearMultiplayerList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.PopulateMultiplayerList
// ()

void UWidget_PlayMenu_JoinGame_C::PopulateMultiplayerList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.PopulateMultiplayerList");

	UWidget_PlayMenu_JoinGame_C_PopulateMultiplayerList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnJoinSession
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* ClickedButton                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_PlayMenu_JoinGame_C::OnJoinSession(class UWidget_Multiplayer_ListButton_C* ClickedButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnJoinSession");

	UWidget_PlayMenu_JoinGame_C_OnJoinSession_Params params;
	params.ClickedButton = ClickedButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnNewSessionSelected
// ()
// Parameters:
// struct FBlueprintSessionResult session                        (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_PlayMenu_JoinGame_C::OnNewSessionSelected(const struct FBlueprintSessionResult& session)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnNewSessionSelected");

	UWidget_PlayMenu_JoinGame_C_OnNewSessionSelected_Params params;
	params.session = session;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnJoinSessionNew
// ()

void UWidget_PlayMenu_JoinGame_C::OnJoinSessionNew()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnJoinSessionNew");

	UWidget_PlayMenu_JoinGame_C_OnJoinSessionNew_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_PlayMenu_JoinGame_C::BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_PlayMenu_JoinGame_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnSessionDeselected
// ()

void UWidget_PlayMenu_JoinGame_C::OnSessionDeselected()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnSessionDeselected");

	UWidget_PlayMenu_JoinGame_C_OnSessionDeselected_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_PlayMenu_JoinGame_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnMenuEnter");

	UWidget_PlayMenu_JoinGame_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateMultiplayerList
// ()
// Parameters:
// struct FUpdatedFriends         UpdatedFriends                 (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_PlayMenu_JoinGame_C::UpdateMultiplayerList(const struct FUpdatedFriends& UpdatedFriends)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.UpdateMultiplayerList");

	UWidget_PlayMenu_JoinGame_C_UpdateMultiplayerList_Params params;
	params.UpdatedFriends = UpdatedFriends;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.PresenceUpdated
// ()
// Parameters:
// struct FUniqueNetIdRepl        updatedId                      (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_PlayMenu_JoinGame_C::PresenceUpdated(const struct FUniqueNetIdRepl& updatedId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.PresenceUpdated");

	UWidget_PlayMenu_JoinGame_C_PresenceUpdated_Params params;
	params.updatedId = updatedId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnMenuExit
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool*                          noAnimation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayMenu_JoinGame_C::OnMenuExit(class UWidget** prevMenu, bool* noAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.OnMenuExit");

	UWidget_PlayMenu_JoinGame_C_OnMenuExit_Params params;
	params.prevMenu = prevMenu;
	params.noAnimation = noAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ExecuteUbergraph_Widget_PlayMenu_JoinGame
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayMenu_JoinGame_C::ExecuteUbergraph_Widget_PlayMenu_JoinGame(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayMenu_JoinGame.Widget_PlayMenu_JoinGame_C.ExecuteUbergraph_Widget_PlayMenu_JoinGame");

	UWidget_PlayMenu_JoinGame_C_ExecuteUbergraph_Widget_PlayMenu_JoinGame_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
