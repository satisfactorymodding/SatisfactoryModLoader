// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Popup_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Popup.Widget_Popup_C.CancelClicked
// ()

void UWidget_Popup_C::CancelClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.CancelClicked");

	UWidget_Popup_C_CancelClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.OkClicked
// ()

void UWidget_Popup_C::OkClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.OkClicked");

	UWidget_Popup_C_OkClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.CheckButtonState
// ()

void UWidget_Popup_C::CheckButtonState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.CheckButtonState");

	UWidget_Popup_C_CheckButtonState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.OnKeyUp
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_Popup_C::OnKeyUp(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.OnKeyUp");

	UWidget_Popup_C_OnKeyUp_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Popup.Widget_Popup_C.DoClosePopup
// ()
// Parameters:
// bool                           ConfirmClicked                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Popup_C::DoClosePopup(bool ConfirmClicked)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.DoClosePopup");

	UWidget_Popup_C_DoClosePopup_Params params;
	params.ConfirmClicked = ConfirmClicked;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.Init
// ()

void UWidget_Popup_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.Init");

	UWidget_Popup_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.Construct
// ()

void UWidget_Popup_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.Construct");

	UWidget_Popup_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Popup_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.Tick");

	UWidget_Popup_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_Popup_C::BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_Popup_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Popup.Widget_Popup_C.ExecuteUbergraph_Widget_Popup
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Popup_C::ExecuteUbergraph_Widget_Popup(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Popup.Widget_Popup_C.ExecuteUbergraph_Widget_Popup");

	UWidget_Popup_C_ExecuteUbergraph_Widget_Popup_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
