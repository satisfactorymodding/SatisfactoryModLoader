// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_Module_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.SetAndUpdateColor
// ()

void UWidget_ColorPicker_Module_C::SetAndUpdateColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.SetAndUpdateColor");

	UWidget_ColorPicker_Module_C_SetAndUpdateColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.Construct
// ()

void UWidget_ColorPicker_Module_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.Construct");

	UWidget_ColorPicker_Module_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.BndEvt__Widget_ColorPicker_Slider_K2Node_ComponentBoundEvent_0_OnValueChanged__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Module_C::BndEvt__Widget_ColorPicker_Slider_K2Node_ComponentBoundEvent_0_OnValueChanged__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.BndEvt__Widget_ColorPicker_Slider_K2Node_ComponentBoundEvent_0_OnValueChanged__DelegateSignature");

	UWidget_ColorPicker_Module_C_BndEvt__Widget_ColorPicker_Slider_K2Node_ComponentBoundEvent_0_OnValueChanged__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.BndEvt__mBrightnessSlider_K2Node_ComponentBoundEvent_1_OnValueChanged__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Module_C::BndEvt__mBrightnessSlider_K2Node_ComponentBoundEvent_1_OnValueChanged__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.BndEvt__mBrightnessSlider_K2Node_ComponentBoundEvent_1_OnValueChanged__DelegateSignature");

	UWidget_ColorPicker_Module_C_BndEvt__mBrightnessSlider_K2Node_ComponentBoundEvent_1_OnValueChanged__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.BndEvt__mSaturationSlider_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Module_C::BndEvt__mSaturationSlider_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.BndEvt__mSaturationSlider_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature");

	UWidget_ColorPicker_Module_C_BndEvt__mSaturationSlider_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.SetupColorAndSliders
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Module_C::SetupColorAndSliders(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.SetupColorAndSliders");

	UWidget_ColorPicker_Module_C_SetupColorAndSliders_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.ExecuteUbergraph_Widget_ColorPicker_Module
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Module_C::ExecuteUbergraph_Widget_ColorPicker_Module(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.ExecuteUbergraph_Widget_ColorPicker_Module");

	UWidget_ColorPicker_Module_C_ExecuteUbergraph_Widget_ColorPicker_Module_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.OnValueChanged__DelegateSignature
// ()

void UWidget_ColorPicker_Module_C::OnValueChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_Module.Widget_ColorPicker_Module_C.OnValueChanged__DelegateSignature");

	UWidget_ColorPicker_Module_C_OnValueChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
