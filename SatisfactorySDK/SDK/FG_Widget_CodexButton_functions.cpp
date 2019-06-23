// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CodexButton.Widget_CodexButton_C.GetTextHoverColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_CodexButton_C::GetTextHoverColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.GetTextHoverColor");

	UWidget_CodexButton_C_GetTextHoverColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CodexButton.Widget_CodexButton_C.GetMessageNotificationVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_CodexButton_C::GetMessageNotificationVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.GetMessageNotificationVisibility");

	UWidget_CodexButton_C_GetMessageNotificationVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CodexButton.Widget_CodexButton_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_CodexButton_C::BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature");

	UWidget_CodexButton_C_BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.Construct
// ()

void UWidget_CodexButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.Construct");

	UWidget_CodexButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_CodexButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature");

	UWidget_CodexButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.Destruct
// ()

void UWidget_CodexButton_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.Destruct");

	UWidget_CodexButton_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.Clicked
// ()

void UWidget_CodexButton_C::Clicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.Clicked");

	UWidget_CodexButton_C_Clicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.ExecuteUbergraph_Widget_CodexButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CodexButton_C::ExecuteUbergraph_Widget_CodexButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.ExecuteUbergraph_Widget_CodexButton");

	UWidget_CodexButton_C_ExecuteUbergraph_Widget_CodexButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.OnReleased__DelegateSignature
// ()

void UWidget_CodexButton_C::OnReleased__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.OnReleased__DelegateSignature");

	UWidget_CodexButton_C_OnReleased__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.OnPressed__DelegateSignature
// ()

void UWidget_CodexButton_C::OnPressed__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.OnPressed__DelegateSignature");

	UWidget_CodexButton_C_OnPressed__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexButton.Widget_CodexButton_C.OnClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_CodexButton_C*   ButtonPressed                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_CodexButton_C::OnClicked__DelegateSignature(class UWidget_CodexButton_C* ButtonPressed)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexButton.Widget_CodexButton_C.OnClicked__DelegateSignature");

	UWidget_CodexButton_C_OnClicked__DelegateSignature_Params params;
	params.ButtonPressed = ButtonPressed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
