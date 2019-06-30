// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManageSession_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ManageSession.Widget_ManageSession_C.ClearIngamePlayerList
// ()

void UWidget_ManageSession_C::ClearIngamePlayerList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.ClearIngamePlayerList");

	UWidget_ManageSession_C_ClearIngamePlayerList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.IsHost
// ()
// Parameters:
// class APlayerState*            State                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           isOurself                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ManageSession_C::IsHost(class APlayerState* State, bool* isOurself)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.IsHost");

	UWidget_ManageSession_C_IsHost_Params params;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (isOurself != nullptr)
		*isOurself = params.isOurself;
}


// Function Widget_ManageSession.Widget_ManageSession_C.DisableManagePlayers
// ()

void UWidget_ManageSession_C::DisableManagePlayers()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.DisableManagePlayers");

	UWidget_ManageSession_C_DisableManagePlayers_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.DisableSessionType
// ()

void UWidget_ManageSession_C::DisableSessionType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.DisableSessionType");

	UWidget_ManageSession_C_DisableSessionType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.DisableClientOptions
// ()

void UWidget_ManageSession_C::DisableClientOptions()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.DisableClientOptions");

	UWidget_ManageSession_C_DisableClientOptions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.UpdateCurrentSessionType
// ()

void UWidget_ManageSession_C::UpdateCurrentSessionType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.UpdateCurrentSessionType");

	UWidget_ManageSession_C_UpdateCurrentSessionType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.PopulateManagePlayerList
// ()

void UWidget_ManageSession_C::PopulateManagePlayerList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.PopulateManagePlayerList");

	UWidget_ManageSession_C_PopulateManagePlayerList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.ClearLeftSelection
// ()

void UWidget_ManageSession_C::ClearLeftSelection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.ClearLeftSelection");

	UWidget_ManageSession_C_ClearLeftSelection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_0_onSelectionChanged__DelegateSignature
// ()
// Parameters:
// class FString                  SelectedOption                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UWidget_ManageSession_C::BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_0_onSelectionChanged__DelegateSignature(const class FString& SelectedOption)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_0_onSelectionChanged__DelegateSignature");

	UWidget_ManageSession_C_BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_0_onSelectionChanged__DelegateSignature_Params params;
	params.SelectedOption = SelectedOption;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.OnJoinInvite
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* Button                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageSession_C::OnJoinInvite(class UWidget_Multiplayer_ListButton_C* Button)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.OnJoinInvite");

	UWidget_ManageSession_C_OnJoinInvite_Params params;
	params.Button = Button;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.SpawnAnim
// ()
// Parameters:
// bool*                          PlayBackgroundAnim             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManageSession_C::SpawnAnim(bool* PlayBackgroundAnim)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.SpawnAnim");

	UWidget_ManageSession_C_SpawnAnim_Params params;
	params.PlayBackgroundAnim = PlayBackgroundAnim;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.OnEscape
// ()

void UWidget_ManageSession_C::OnEscape()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.OnEscape");

	UWidget_ManageSession_C_OnEscape_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageSession_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.OnMenuEnter");

	UWidget_ManageSession_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.OnKick
// ()
// Parameters:
// class UWidget_Multiplayer_ListButton_C* ClickedButton                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageSession_C::OnKick(class UWidget_Multiplayer_ListButton_C* ClickedButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.OnKick");

	UWidget_ManageSession_C_OnKick_Params params;
	params.ClickedButton = ClickedButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.BndEvt__mSwitcher_K2Node_ComponentBoundEvent_1_OnActiveWidgetSet__DelegateSignature
// ()
// Parameters:
// class UWidget*                 oldWidget                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UWidget*                 newWidget                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManageSession_C::BndEvt__mSwitcher_K2Node_ComponentBoundEvent_1_OnActiveWidgetSet__DelegateSignature(class UWidget* oldWidget, class UWidget* newWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.BndEvt__mSwitcher_K2Node_ComponentBoundEvent_1_OnActiveWidgetSet__DelegateSignature");

	UWidget_ManageSession_C_BndEvt__mSwitcher_K2Node_ComponentBoundEvent_1_OnActiveWidgetSet__DelegateSignature_Params params;
	params.oldWidget = oldWidget;
	params.newWidget = newWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManageSession.Widget_ManageSession_C.ExecuteUbergraph_Widget_ManageSession
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManageSession_C::ExecuteUbergraph_Widget_ManageSession(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManageSession.Widget_ManageSession_C.ExecuteUbergraph_Widget_ManageSession");

	UWidget_ManageSession_C_ExecuteUbergraph_Widget_ManageSession_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
