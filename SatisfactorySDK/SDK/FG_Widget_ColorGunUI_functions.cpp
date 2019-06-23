// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorGunUI_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorGunUI.Widget_ColorGunUI_C.OnPrimaryColorPicked
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorGunUI_C::OnPrimaryColorPicked(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.OnPrimaryColorPicked");

	UWidget_ColorGunUI_C_OnPrimaryColorPicked_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGunUI.Widget_ColorGunUI_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_21_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ColorGunUI_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_21_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_21_OnButtonClickedEvent__DelegateSignature");

	UWidget_ColorGunUI_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_21_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGunUI.Widget_ColorGunUI_C.OnSecondaryColorPicked
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorGunUI_C::OnSecondaryColorPicked(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.OnSecondaryColorPicked");

	UWidget_ColorGunUI_C_OnSecondaryColorPicked_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGunUI.Widget_ColorGunUI_C.BndEvt__mSecondaryButton_K2Node_ComponentBoundEvent_26_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ColorGunUI_C::BndEvt__mSecondaryButton_K2Node_ComponentBoundEvent_26_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.BndEvt__mSecondaryButton_K2Node_ComponentBoundEvent_26_OnButtonClickedEvent__DelegateSignature");

	UWidget_ColorGunUI_C_BndEvt__mSecondaryButton_K2Node_ComponentBoundEvent_26_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGunUI.Widget_ColorGunUI_C.Construct
// ()

void UWidget_ColorGunUI_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.Construct");

	UWidget_ColorGunUI_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGunUI.Widget_ColorGunUI_C.BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_ColorGunUI_C::BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_ColorGunUI_C_BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGunUI.Widget_ColorGunUI_C.OnClose
// ()

void UWidget_ColorGunUI_C::OnClose()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.OnClose");

	UWidget_ColorGunUI_C_OnClose_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorGunUI.Widget_ColorGunUI_C.ExecuteUbergraph_Widget_ColorGunUI
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorGunUI_C::ExecuteUbergraph_Widget_ColorGunUI(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorGunUI.Widget_ColorGunUI_C.ExecuteUbergraph_Widget_ColorGunUI");

	UWidget_ColorGunUI_C_ExecuteUbergraph_Widget_ColorGunUI_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
