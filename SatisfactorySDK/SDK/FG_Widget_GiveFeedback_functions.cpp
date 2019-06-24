// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GiveFeedback_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.PopulateTypeFeedbackOptions
// ()

void UWidget_GiveFeedback_C::PopulateTypeFeedbackOptions()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.PopulateTypeFeedbackOptions");

	UWidget_GiveFeedback_C_PopulateTypeFeedbackOptions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.PopulateSatisfactorySelectOptions
// ()

void UWidget_GiveFeedback_C::PopulateSatisfactorySelectOptions()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.PopulateSatisfactorySelectOptions");

	UWidget_GiveFeedback_C_PopulateSatisfactorySelectOptions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_GiveFeedback_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.OnKeyDown");

	UWidget_GiveFeedback_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.Construct
// ()

void UWidget_GiveFeedback_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.Construct");

	UWidget_GiveFeedback_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
// ()

void UWidget_GiveFeedback_C::BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature");

	UWidget_GiveFeedback_C_BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.CloseFeedback
// ()

void UWidget_GiveFeedback_C::CloseFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.CloseFeedback");

	UWidget_GiveFeedback_C_CloseFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__THANKSDUDE_K2Node_ComponentBoundEvent_147_OnClicked__DelegateSignature
// ()

void UWidget_GiveFeedback_C::BndEvt__THANKSDUDE_K2Node_ComponentBoundEvent_147_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__THANKSDUDE_K2Node_ComponentBoundEvent_147_OnClicked__DelegateSignature");

	UWidget_GiveFeedback_C_BndEvt__THANKSDUDE_K2Node_ComponentBoundEvent_147_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__mTypeFeedbackSelect_K2Node_ComponentBoundEvent_1_onSelectionChanged__DelegateSignature
// ()
// Parameters:
// class FString                  SelectedOption                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UWidget_GiveFeedback_C::BndEvt__mTypeFeedbackSelect_K2Node_ComponentBoundEvent_1_onSelectionChanged__DelegateSignature(const class FString& SelectedOption)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__mTypeFeedbackSelect_K2Node_ComponentBoundEvent_1_onSelectionChanged__DelegateSignature");

	UWidget_GiveFeedback_C_BndEvt__mTypeFeedbackSelect_K2Node_ComponentBoundEvent_1_onSelectionChanged__DelegateSignature_Params params;
	params.SelectedOption = SelectedOption;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Details_text_K2Node_ComponentBoundEvent_4_OnMultiLineEditableTextChangedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_GiveFeedback_C::BndEvt__Details_text_K2Node_ComponentBoundEvent_4_OnMultiLineEditableTextChangedEvent__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Details_text_K2Node_ComponentBoundEvent_4_OnMultiLineEditableTextChangedEvent__DelegateSignature");

	UWidget_GiveFeedback_C_BndEvt__Details_text_K2Node_ComponentBoundEvent_4_OnMultiLineEditableTextChangedEvent__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature
// ()

void UWidget_GiveFeedback_C::BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature");

	UWidget_GiveFeedback_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature
// ()

void UWidget_GiveFeedback_C::BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature");

	UWidget_GiveFeedback_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.SendFeedbackAfterConfirm
// ()
// Parameters:
// bool                           mConfirmBool                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_GiveFeedback_C::SendFeedbackAfterConfirm(bool mConfirmBool)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.SendFeedbackAfterConfirm");

	UWidget_GiveFeedback_C_SendFeedbackAfterConfirm_Params params;
	params.mConfirmBool = mConfirmBool;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_GiveFeedback_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_GiveFeedback_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GiveFeedback.Widget_GiveFeedback_C.ExecuteUbergraph_Widget_GiveFeedback
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_GiveFeedback_C::ExecuteUbergraph_Widget_GiveFeedback(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GiveFeedback.Widget_GiveFeedback_C.ExecuteUbergraph_Widget_GiveFeedback");

	UWidget_GiveFeedback_C_ExecuteUbergraph_Widget_GiveFeedback_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
