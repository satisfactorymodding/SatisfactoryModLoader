// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Button_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Button.Widget_Button_C.GetAccordionFeedbackVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Button_C::GetAccordionFeedbackVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.GetAccordionFeedbackVisibility");

	UWidget_Button_C_GetAccordionFeedbackVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Button.Widget_Button_C.GetButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_Button_C::GetButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.GetButtonEnabled");

	UWidget_Button_C_GetButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Button.Widget_Button_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Button_C::BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature");

	UWidget_Button_C_BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_597_OnButtonPressedEvent__DelegateSignature
// ()

void UWidget_Button_C::BndEvt__Button_26_K2Node_ComponentBoundEvent_597_OnButtonPressedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_597_OnButtonPressedEvent__DelegateSignature");

	UWidget_Button_C_BndEvt__Button_26_K2Node_ComponentBoundEvent_597_OnButtonPressedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_642_OnButtonReleasedEvent__DelegateSignature
// ()

void UWidget_Button_C::BndEvt__Button_26_K2Node_ComponentBoundEvent_642_OnButtonReleasedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_642_OnButtonReleasedEvent__DelegateSignature");

	UWidget_Button_C_BndEvt__Button_26_K2Node_ComponentBoundEvent_642_OnButtonReleasedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.Construct
// ()

void UWidget_Button_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.Construct");

	UWidget_Button_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Button_C::BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature");

	UWidget_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.Destruct
// ()

void UWidget_Button_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.Destruct");

	UWidget_Button_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.ExecuteUbergraph_Widget_Button
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Button_C::ExecuteUbergraph_Widget_Button(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.ExecuteUbergraph_Widget_Button");

	UWidget_Button_C_ExecuteUbergraph_Widget_Button_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.OnClickedWithRef__DelegateSignature
// ()
// Parameters:
// class UWidget_Button_C*        ClickedButton                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Button_C::OnClickedWithRef__DelegateSignature(class UWidget_Button_C* ClickedButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.OnClickedWithRef__DelegateSignature");

	UWidget_Button_C_OnClickedWithRef__DelegateSignature_Params params;
	params.ClickedButton = ClickedButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.OnReleased__DelegateSignature
// ()

void UWidget_Button_C::OnReleased__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.OnReleased__DelegateSignature");

	UWidget_Button_C_OnReleased__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.OnPressed__DelegateSignature
// ()

void UWidget_Button_C::OnPressed__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.OnPressed__DelegateSignature");

	UWidget_Button_C_OnPressed__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Button.Widget_Button_C.OnClicked__DelegateSignature
// ()

void UWidget_Button_C::OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Button.Widget_Button_C.OnClicked__DelegateSignature");

	UWidget_Button_C_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
