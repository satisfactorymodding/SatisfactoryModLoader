// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Multiplayer_ListButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateNATWarningForClient
// ()

void UWidget_Multiplayer_ListButton_C::UpdateNATWarningForClient()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateNATWarningForClient");

	UWidget_Multiplayer_ListButton_C_UpdateNATWarningForClient_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.GetHostingNATIsse
// ()
// Parameters:
// ECachedNATType                 HostNAT                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// ECachedNATType                 clientNat                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   ToolTip                        (Parm, OutParm)

void UWidget_Multiplayer_ListButton_C::GetHostingNATIsse(ECachedNATType HostNAT, ECachedNATType clientNat, struct FText* ToolTip)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.GetHostingNATIsse");

	UWidget_Multiplayer_ListButton_C_GetHostingNATIsse_Params params;
	params.HostNAT = HostNAT;
	params.clientNat = clientNat;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ToolTip != nullptr)
		*ToolTip = params.ToolTip;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.GetConnectingNATIsse
// ()
// Parameters:
// ECachedNATType                 HostNAT                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// ECachedNATType                 clientNat                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   ToolTip                        (Parm, OutParm)

void UWidget_Multiplayer_ListButton_C::GetConnectingNATIsse(ECachedNATType HostNAT, ECachedNATType clientNat, struct FText* ToolTip)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.GetConnectingNATIsse");

	UWidget_Multiplayer_ListButton_C_GetConnectingNATIsse_Params params;
	params.HostNAT = HostNAT;
	params.clientNat = clientNat;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ToolTip != nullptr)
		*ToolTip = params.ToolTip;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.IsNATIssue
// ()
// Parameters:
// ECachedNATType                 HostNAT                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// ECachedNATType                 clientNat                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           isIssue                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_Multiplayer_ListButton_C::IsNATIssue(ECachedNATType HostNAT, ECachedNATType clientNat, bool* isIssue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.IsNATIssue");

	UWidget_Multiplayer_ListButton_C_IsNATIssue_Params params;
	params.HostNAT = HostNAT;
	params.clientNat = clientNat;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (isIssue != nullptr)
		*isIssue = params.isIssue;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateNATWarningForHost
// ()

void UWidget_Multiplayer_ListButton_C::UpdateNATWarningForHost()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateNATWarningForHost");

	UWidget_Multiplayer_ListButton_C_UpdateNATWarningForHost_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForManagePlayers
// ()
// Parameters:
// class AFGPlayerState*          PlayerState                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Multiplayer_ListButton_C::SetupForManagePlayers(class AFGPlayerState* PlayerState)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForManagePlayers");

	UWidget_Multiplayer_ListButton_C_SetupForManagePlayers_Params params;
	params.PlayerState = PlayerState;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForJoinInvite
// ()
// Parameters:
// struct FPendingInvite          invite                         (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_Multiplayer_ListButton_C::SetupForJoinInvite(struct FPendingInvite* invite)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForJoinInvite");

	UWidget_Multiplayer_ListButton_C_SetupForJoinInvite_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (invite != nullptr)
		*invite = params.invite;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForSendInvite
// ()
// Parameters:
// struct FFGOnlineFriend         _friend                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_Multiplayer_ListButton_C::SetupForSendInvite(struct FFGOnlineFriend* _friend)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForSendInvite");

	UWidget_Multiplayer_ListButton_C_SetupForSendInvite_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (_friend != nullptr)
		*_friend = params._friend;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.Internal_UpdateButton
// ()
// Parameters:
// struct FText                   Title                          (BlueprintVisible, BlueprintReadOnly, Parm)
// bool                           IsOnline                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   AdditionalInfo                 (BlueprintVisible, BlueprintReadOnly, Parm)
// int                            PlayersInSession               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           privateSession                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            TimePlayed                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   ActionButtonText               (BlueprintVisible, BlueprintReadOnly, Parm)
// bool                           hideSessionInfo                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           isPlayingSatisfactory          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           hideActionButton               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           hideSecondaryActionButton      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           disableActionButton            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   actionButtonTooltip            (BlueprintVisible, BlueprintReadOnly, Parm)
// bool                           inAGame                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FBlueprintSessionResult session                        (BlueprintVisible, BlueprintReadOnly, Parm)
// bool                           IsSelectable                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           IsNonInteractable              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// ECachedNATType                 natType                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           IsHost                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           careAboutNAT                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Multiplayer_ListButton_C::Internal_UpdateButton(const struct FText& Title, bool IsOnline, const struct FText& AdditionalInfo, int PlayersInSession, bool privateSession, int TimePlayed, const struct FText& ActionButtonText, bool hideSessionInfo, bool isPlayingSatisfactory, bool hideActionButton, bool hideSecondaryActionButton, bool disableActionButton, const struct FText& actionButtonTooltip, bool inAGame, const struct FBlueprintSessionResult& session, bool IsSelectable, bool IsNonInteractable, ECachedNATType natType, bool IsHost, bool careAboutNAT)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.Internal_UpdateButton");

	UWidget_Multiplayer_ListButton_C_Internal_UpdateButton_Params params;
	params.Title = Title;
	params.IsOnline = IsOnline;
	params.AdditionalInfo = AdditionalInfo;
	params.PlayersInSession = PlayersInSession;
	params.privateSession = privateSession;
	params.TimePlayed = TimePlayed;
	params.ActionButtonText = ActionButtonText;
	params.hideSessionInfo = hideSessionInfo;
	params.isPlayingSatisfactory = isPlayingSatisfactory;
	params.hideActionButton = hideActionButton;
	params.hideSecondaryActionButton = hideSecondaryActionButton;
	params.disableActionButton = disableActionButton;
	params.actionButtonTooltip = actionButtonTooltip;
	params.inAGame = inAGame;
	params.session = session;
	params.IsSelectable = IsSelectable;
	params.IsNonInteractable = IsNonInteractable;
	params.natType = natType;
	params.IsHost = IsHost;
	params.careAboutNAT = careAboutNAT;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForJoinGame
// ()
// Parameters:
// struct FFGOnlineFriend         _friend                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_Multiplayer_ListButton_C::SetupForJoinGame(struct FFGOnlineFriend* _friend)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetupForJoinGame");

	UWidget_Multiplayer_ListButton_C_SetupForJoinGame_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (_friend != nullptr)
		*_friend = params._friend;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetButtonColor
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Multiplayer_ListButton_C::SetButtonColor(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.SetButtonColor");

	UWidget_Multiplayer_ListButton_C_SetButtonColor_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.ClearListSelection
// ()

void UWidget_Multiplayer_ListButton_C::ClearListSelection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.ClearListSelection");

	UWidget_Multiplayer_ListButton_C_ClearListSelection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateButton
// ()

void UWidget_Multiplayer_ListButton_C::UpdateButton()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.UpdateButton");

	UWidget_Multiplayer_ListButton_C_UpdateButton_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Multiplayer_ListButton_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.PreConstruct");

	UWidget_Multiplayer_ListButton_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__ActionButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Multiplayer_ListButton_C::BndEvt__ActionButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__ActionButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_BndEvt__ActionButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Multiplayer_ListButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Multiplayer_ListButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Multiplayer_ListButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.ExecuteUbergraph_Widget_Multiplayer_ListButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Multiplayer_ListButton_C::ExecuteUbergraph_Widget_Multiplayer_ListButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.ExecuteUbergraph_Widget_Multiplayer_ListButton");

	UWidget_Multiplayer_ListButton_C_ExecuteUbergraph_Widget_Multiplayer_ListButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnSessionDeselected__DelegateSignature
// ()

void UWidget_Multiplayer_ListButton_C::OnSessionDeselected__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnSessionDeselected__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_OnSessionDeselected__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnButtonClicked__DelegateSignature
// ()

void UWidget_Multiplayer_ListButton_C::OnButtonClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnButtonClicked__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_OnButtonClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnSessionSelected__DelegateSignature
// ()
// Parameters:
// struct FBlueprintSessionResult session                        (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Multiplayer_ListButton_C::OnSessionSelected__DelegateSignature(const struct FBlueprintSessionResult& session)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnSessionSelected__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_OnSessionSelected__DelegateSignature_Params params;
	params.session = session;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnActionButtonClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* ClickedButton                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Multiplayer_ListButton_C::OnActionButtonClicked__DelegateSignature(class UWidget_Multiplayer_ListButton_C* ClickedButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Multiplayer_ListButton.Widget_Multiplayer_ListButton_C.OnActionButtonClicked__DelegateSignature");

	UWidget_Multiplayer_ListButton_C_OnActionButtonClicked__DelegateSignature_Params params;
	params.ClickedButton = ClickedButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
