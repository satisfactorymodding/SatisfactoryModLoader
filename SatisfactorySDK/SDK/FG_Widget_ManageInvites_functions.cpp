// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManageInvites_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ManageInvites.Widget_ManageInvites_C.AddInviteToInviteList
// ()
// Parameters:
// struct FPendingInvite          invite                         (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ManageInvites_C::AddInviteToInviteList(struct FPendingInvite* invite)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.AddInviteToInviteList");

	UWidget_ManageInvites_C_AddInviteToInviteList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (invite != nullptr)
		*invite = params.invite;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateFriendInviteButton
// ()
// Parameters:
// struct FUniqueNetIdRepl        netId                          (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ManageInvites_C::UpdateFriendInviteButton(struct FUniqueNetIdRepl* netId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateFriendInviteButton");

	UWidget_ManageInvites_C_UpdateFriendInviteButton_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (netId != nullptr)
		*netId = params.netId;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.SetupButtonForJoinInvite
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* Button                         (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, InstancedReference, ReferenceParm, IsPlainOldData)
// struct FPendingInvite          invite                         (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ManageInvites_C::SetupButtonForJoinInvite(class UWidget_Multiplayer_ListButton_C* Button, struct FPendingInvite* invite)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.SetupButtonForJoinInvite");

	UWidget_ManageInvites_C_SetupButtonForJoinInvite_Params params;
	params.Button = Button;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (invite != nullptr)
		*invite = params.invite;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.SetupButtonForSendInvite
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* Button                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FFGOnlineFriend         onlineFriend                   (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ManageInvites_C::SetupButtonForSendInvite(class UWidget_Multiplayer_ListButton_C* Button, const struct FFGOnlineFriend& onlineFriend)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.SetupButtonForSendInvite");

	UWidget_ManageInvites_C_SetupButtonForSendInvite_Params params;
	params.Button = Button;
	params.onlineFriend = onlineFriend;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateOrAddFriendsToInvite
// ()
// Parameters:
// TArray<struct FFGOnlineFriend> UpdatedFriends                 (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UWidget_ManageInvites_C::UpdateOrAddFriendsToInvite(TArray<struct FFGOnlineFriend>* UpdatedFriends)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateOrAddFriendsToInvite");

	UWidget_ManageInvites_C_UpdateOrAddFriendsToInvite_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (UpdatedFriends != nullptr)
		*UpdatedFriends = params.UpdatedFriends;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateInviteFriendButton
// ()
// Parameters:
// struct FUniqueNetIdRepl        friendId                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_ManageInvites_C::UpdateInviteFriendButton(const struct FUniqueNetIdRepl& friendId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.UpdateInviteFriendButton");

	UWidget_ManageInvites_C_UpdateInviteFriendButton_Params params;
	params.friendId = friendId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.PopulateInviteList
// ()

void UWidget_ManageInvites_C::PopulateInviteList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.PopulateInviteList");

	UWidget_ManageInvites_C_PopulateInviteList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.ClearInviteList
// ()

void UWidget_ManageInvites_C::ClearInviteList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.ClearInviteList");

	UWidget_ManageInvites_C_ClearInviteList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.ClearInvitePlayerList
// ()

void UWidget_ManageInvites_C::ClearInvitePlayerList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.ClearInvitePlayerList");

	UWidget_ManageInvites_C_ClearInvitePlayerList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.PopulateFriendsToInvite
// ()

void UWidget_ManageInvites_C::PopulateFriendsToInvite()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.PopulateFriendsToInvite");

	UWidget_ManageInvites_C_PopulateFriendsToInvite_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.OnEscape
// ()

void UWidget_ManageInvites_C::OnEscape()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.OnEscape");

	UWidget_ManageInvites_C_OnEscape_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.Construct
// ()

void UWidget_ManageInvites_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.Construct");

	UWidget_ManageInvites_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.OnJoinInvite
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* Button                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageInvites_C::OnJoinInvite(class UWidget_Multiplayer_ListButton_C* Button)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.OnJoinInvite");

	UWidget_ManageInvites_C_OnJoinInvite_Params params;
	params.Button = Button;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.AddInvitePlayersDelegates
// ()

void UWidget_ManageInvites_C::AddInvitePlayersDelegates()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.AddInvitePlayersDelegates");

	UWidget_ManageInvites_C_AddInvitePlayersDelegates_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.FriendListUpdated_InvitePlayerss
// ()
// Parameters:
// struct FUpdatedFriends         UpdatedFriends                 (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_ManageInvites_C::FriendListUpdated_InvitePlayerss(const struct FUpdatedFriends& UpdatedFriends)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.FriendListUpdated_InvitePlayerss");

	UWidget_ManageInvites_C_FriendListUpdated_InvitePlayerss_Params params;
	params.UpdatedFriends = UpdatedFriends;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.PresenceUpdated_InvitePlayers
// ()
// Parameters:
// struct FUniqueNetIdRepl        updatedId                      (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ManageInvites_C::PresenceUpdated_InvitePlayers(const struct FUniqueNetIdRepl& updatedId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.PresenceUpdated_InvitePlayers");

	UWidget_ManageInvites_C_PresenceUpdated_InvitePlayers_Params params;
	params.updatedId = updatedId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.RemoveInvitePlayersDelegates
// ()

void UWidget_ManageInvites_C::RemoveInvitePlayersDelegates()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.RemoveInvitePlayersDelegates");

	UWidget_ManageInvites_C_RemoveInvitePlayersDelegates_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.AddManageInvitesDelegates
// ()

void UWidget_ManageInvites_C::AddManageInvitesDelegates()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.AddManageInvitesDelegates");

	UWidget_ManageInvites_C_AddManageInvitesDelegates_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.FriendsPresenceUpdate_ManageInvites
// ()
// Parameters:
// struct FUniqueNetIdRepl        updatedId                      (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ManageInvites_C::FriendsPresenceUpdate_ManageInvites(const struct FUniqueNetIdRepl& updatedId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.FriendsPresenceUpdate_ManageInvites");

	UWidget_ManageInvites_C_FriendsPresenceUpdate_ManageInvites_Params params;
	params.updatedId = updatedId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.RemoveManageInvitesDelegates
// ()

void UWidget_ManageInvites_C::RemoveManageInvitesDelegates()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.RemoveManageInvitesDelegates");

	UWidget_ManageInvites_C_RemoveManageInvitesDelegates_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.InviteReceived_ManageInvites
// ()
// Parameters:
// struct FPendingInvite          receivedInvite                 (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ManageInvites_C::InviteReceived_ManageInvites(const struct FPendingInvite& receivedInvite)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.InviteReceived_ManageInvites");

	UWidget_ManageInvites_C_InviteReceived_ManageInvites_Params params;
	params.receivedInvite = receivedInvite;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.OnMenuExit
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool*                          noAnimation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManageInvites_C::OnMenuExit(class UWidget** prevMenu, bool* noAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.OnMenuExit");

	UWidget_ManageInvites_C_OnMenuExit_Params params;
	params.prevMenu = prevMenu;
	params.noAnimation = noAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.BndEvt__mSwitcher_K2Node_ComponentBoundEvent_0_OnActiveWidgetSet__DelegateSignature
// ()
// Parameters:
// class UWidget*                 oldWidget                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UWidget*                 newWidget                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageInvites_C::BndEvt__mSwitcher_K2Node_ComponentBoundEvent_0_OnActiveWidgetSet__DelegateSignature(class UWidget* oldWidget, class UWidget* newWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.BndEvt__mSwitcher_K2Node_ComponentBoundEvent_0_OnActiveWidgetSet__DelegateSignature");

	UWidget_ManageInvites_C_BndEvt__mSwitcher_K2Node_ComponentBoundEvent_0_OnActiveWidgetSet__DelegateSignature_Params params;
	params.oldWidget = oldWidget;
	params.newWidget = newWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageInvites_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.OnMenuEnter");

	UWidget_ManageInvites_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.Destruct
// ()

void UWidget_ManageInvites_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.Destruct");

	UWidget_ManageInvites_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.OnInvite
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* ClickedButton                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageInvites_C::OnInvite(class UWidget_Multiplayer_ListButton_C* ClickedButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.OnInvite");

	UWidget_ManageInvites_C_OnInvite_Params params;
	params.ClickedButton = ClickedButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageInvites.Widget_ManageInvites_C.ExecuteUbergraph_Widget_ManageInvites
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManageInvites_C::ExecuteUbergraph_Widget_ManageInvites(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageInvites.Widget_ManageInvites_C.ExecuteUbergraph_Widget_ManageInvites");

	UWidget_ManageInvites_C_ExecuteUbergraph_Widget_ManageInvites_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
