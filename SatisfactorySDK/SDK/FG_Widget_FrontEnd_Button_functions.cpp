// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_FrontEnd_Button_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetActiveWidgetInSwitcher
// ()

void UWidget_FrontEnd_Button_C::SetActiveWidgetInSwitcher()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetActiveWidgetInSwitcher");

	UWidget_FrontEnd_Button_C_SetActiveWidgetInSwitcher_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ClearListOfSelections
// ()

void UWidget_FrontEnd_Button_C::ClearListOfSelections()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ClearListOfSelections");

	UWidget_FrontEnd_Button_C_ClearListOfSelections_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_FrontEnd_Button_C::GetButtonTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonTextColor");

	UWidget_FrontEnd_Button_C_GetButtonTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_FrontEnd_Button_C::GetButtonColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonColor");

	UWidget_FrontEnd_Button_C_GetButtonColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetFocused
// ()

void UWidget_FrontEnd_Button_C::SetFocused()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetFocused");

	UWidget_FrontEnd_Button_C_SetFocused_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.OnFocusReceived
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FFocusEvent*            InFocusEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_FrontEnd_Button_C::OnFocusReceived(struct FGeometry* MyGeometry, struct FFocusEvent* InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.OnFocusReceived");

	UWidget_FrontEnd_Button_C_OnFocusReceived_Params params;
	params.MyGeometry = MyGeometry;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ShowButton
// ()

void UWidget_FrontEnd_Button_C::ShowButton()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ShowButton");

	UWidget_FrontEnd_Button_C_ShowButton_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.HideButton
// ()

void UWidget_FrontEnd_Button_C::HideButton()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.HideButton");

	UWidget_FrontEnd_Button_C_HideButton_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_FrontEnd_Button_C::GetButtonText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonText");

	UWidget_FrontEnd_Button_C_GetButtonText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.Construct
// ()

void UWidget_FrontEnd_Button_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.Construct");

	UWidget_FrontEnd_Button_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.Destruct
// ()

void UWidget_FrontEnd_Button_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.Destruct");

	UWidget_FrontEnd_Button_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_FrontEnd_Button_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_FrontEnd_Button_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.BndEvt__PauseMenuButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_FrontEnd_Button_C::BndEvt__PauseMenuButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.BndEvt__PauseMenuButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_FrontEnd_Button_C_BndEvt__PauseMenuButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FrontEnd_Button_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.PreConstruct");

	UWidget_FrontEnd_Button_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetSelected
// ()
// Parameters:
// bool                           isSelected                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FrontEnd_Button_C::SetSelected(bool isSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetSelected");

	UWidget_FrontEnd_Button_C_SetSelected_Params params;
	params.isSelected = isSelected;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ExecuteUbergraph_Widget_FrontEnd_Button
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FrontEnd_Button_C::ExecuteUbergraph_Widget_FrontEnd_Button(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ExecuteUbergraph_Widget_FrontEnd_Button");

	UWidget_FrontEnd_Button_C_ExecuteUbergraph_Widget_FrontEnd_Button_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.OnClicked__DelegateSignature
// ()

void UWidget_FrontEnd_Button_C::OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.OnClicked__DelegateSignature");

	UWidget_FrontEnd_Button_C_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
