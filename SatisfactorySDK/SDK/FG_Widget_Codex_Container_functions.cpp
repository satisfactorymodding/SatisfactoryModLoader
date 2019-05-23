// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_Container_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateNotifications
// ()
// Parameters:
// class UWidget_CodexButton_C*   forButton                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Codex_Container_C::UpdateNotifications(class UWidget_CodexButton_C* forButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateNotifications");

	UWidget_Codex_Container_C_UpdateNotifications_Params params;
	params.forButton = forButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.OnFilterButtonPressed
// ()
// Parameters:
// class UWidget_CodexButton_C*   ButtonPressed                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Codex_Container_C::OnFilterButtonPressed(class UWidget_CodexButton_C* ButtonPressed)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.OnFilterButtonPressed");

	UWidget_Codex_Container_C_OnFilterButtonPressed_Params params;
	params.ButtonPressed = ButtonPressed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.SelectButtonWithMessage
// ()
// Parameters:
// class UClass*                  inMessage                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Codex_Container_C::SelectButtonWithMessage(class UClass* inMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.SelectButtonWithMessage");

	UWidget_Codex_Container_C_SelectButtonWithMessage_Params params;
	params.inMessage = inMessage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.CheckShouldOpenMessage
// ()

void UWidget_Codex_Container_C::CheckShouldOpenMessage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.CheckShouldOpenMessage");

	UWidget_Codex_Container_C_CheckShouldOpenMessage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateMessageText
// ()
// Parameters:
// struct FText                   senderMail                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FText                   Sender                         (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FText                   Title                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Codex_Container_C::UpdateMessageText(const struct FText& senderMail, const struct FText& Sender, const struct FText& Title)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateMessageText");

	UWidget_Codex_Container_C_UpdateMessageText_Params params;
	params.senderMail = senderMail;
	params.Sender = Sender;
	params.Title = Title;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.PopulateList
// ()

void UWidget_Codex_Container_C::PopulateList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.PopulateList");

	UWidget_Codex_Container_C_PopulateList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.GetActiveTabFeedback
// ()

void UWidget_Codex_Container_C::GetActiveTabFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.GetActiveTabFeedback");

	UWidget_Codex_Container_C_GetActiveTabFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.GetMessageVisiblity
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Codex_Container_C::GetMessageVisiblity()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.GetMessageVisiblity");

	UWidget_Codex_Container_C_GetMessageVisiblity_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.Construct
// ()

void UWidget_Codex_Container_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.Construct");

	UWidget_Codex_Container_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.CloseCodex
// ()

void UWidget_Codex_Container_C::CloseCodex()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.CloseCodex");

	UWidget_Codex_Container_C_CloseCodex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Codex_Container_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.Tick");

	UWidget_Codex_Container_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.MarkAllAsRead
// ()

void UWidget_Codex_Container_C::MarkAllAsRead()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.MarkAllAsRead");

	UWidget_Codex_Container_C_MarkAllAsRead_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Container.Widget_Codex_Container_C.ExecuteUbergraph_Widget_Codex_Container
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Codex_Container_C::ExecuteUbergraph_Widget_Codex_Container(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Container.Widget_Codex_Container_C.ExecuteUbergraph_Widget_Codex_Container");

	UWidget_Codex_Container_C_ExecuteUbergraph_Widget_Codex_Container_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
