// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Knob_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Knob.Widget_Knob_C.BndEvt__ValueSlider_K2Node_ComponentBoundEvent_1_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Knob_C::BndEvt__ValueSlider_K2Node_ComponentBoundEvent_1_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Knob.Widget_Knob_C.BndEvt__ValueSlider_K2Node_ComponentBoundEvent_1_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_Knob_C_BndEvt__ValueSlider_K2Node_ComponentBoundEvent_1_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Knob.Widget_Knob_C.SetupValue
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Knob_C::SetupValue(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Knob.Widget_Knob_C.SetupValue");

	UWidget_Knob_C_SetupValue_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Knob.Widget_Knob_C.BndEvt__Slider_75_K2Node_ComponentBoundEvent_0_OnMouseCaptureEndEvent__DelegateSignature
// ()

void UWidget_Knob_C::BndEvt__Slider_75_K2Node_ComponentBoundEvent_0_OnMouseCaptureEndEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Knob.Widget_Knob_C.BndEvt__Slider_75_K2Node_ComponentBoundEvent_0_OnMouseCaptureEndEvent__DelegateSignature");

	UWidget_Knob_C_BndEvt__Slider_75_K2Node_ComponentBoundEvent_0_OnMouseCaptureEndEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Knob.Widget_Knob_C.Construct
// ()

void UWidget_Knob_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Knob.Widget_Knob_C.Construct");

	UWidget_Knob_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Knob.Widget_Knob_C.ExecuteUbergraph_Widget_Knob
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Knob_C::ExecuteUbergraph_Widget_Knob(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Knob.Widget_Knob_C.ExecuteUbergraph_Widget_Knob");

	UWidget_Knob_C_ExecuteUbergraph_Widget_Knob_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
