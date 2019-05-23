// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SwitchButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SwitchButton.Widget_SwitchButton_C.SetButtonBrush
// ()
// Parameters:
// bool                           mButtonState                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SwitchButton_C::SetButtonBrush(bool mButtonState)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SwitchButton.Widget_SwitchButton_C.SetButtonBrush");

	UWidget_SwitchButton_C_SetButtonBrush_Params params;
	params.mButtonState = mButtonState;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SwitchButton.Widget_SwitchButton_C.BndEvt__Button_2_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SwitchButton_C::BndEvt__Button_2_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SwitchButton.Widget_SwitchButton_C.BndEvt__Button_2_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_SwitchButton_C_BndEvt__Button_2_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SwitchButton.Widget_SwitchButton_C.Construct
// ()

void UWidget_SwitchButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SwitchButton.Widget_SwitchButton_C.Construct");

	UWidget_SwitchButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SwitchButton.Widget_SwitchButton_C.ExecuteUbergraph_Widget_SwitchButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SwitchButton_C::ExecuteUbergraph_Widget_SwitchButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SwitchButton.Widget_SwitchButton_C.ExecuteUbergraph_Widget_SwitchButton");

	UWidget_SwitchButton_C_ExecuteUbergraph_Widget_SwitchButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SwitchButton.Widget_SwitchButton_C.OnClicked__DelegateSignature
// ()

void UWidget_SwitchButton_C::OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SwitchButton.Widget_SwitchButton_C.OnClicked__DelegateSignature");

	UWidget_SwitchButton_C_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
