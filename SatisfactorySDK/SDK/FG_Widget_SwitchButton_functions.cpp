// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SwitchButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SwitchButton.Widget_SwitchButton_C.SetIcon
// ()
// Parameters:
// class UTexture*                TextureSending                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UTexture*                TextureReceiving               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SwitchButton_C::SetIcon(class UTexture* TextureSending, class UTexture* TextureReceiving)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SwitchButton.Widget_SwitchButton_C.SetIcon");

	UWidget_SwitchButton_C_SetIcon_Params params;
	params.TextureSending = TextureSending;
	params.TextureReceiving = TextureReceiving;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


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


// Function Widget_SwitchButton.Widget_SwitchButton_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SwitchButton_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SwitchButton.Widget_SwitchButton_C.PreConstruct");

	UWidget_SwitchButton_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

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
