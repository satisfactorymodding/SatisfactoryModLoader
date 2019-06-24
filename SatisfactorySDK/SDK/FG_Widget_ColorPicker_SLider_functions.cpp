// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_SLider_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.UpdateSliderValue
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slider_C::UpdateSliderValue(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.UpdateSliderValue");

	UWidget_ColorPicker_Slider_C_UpdateSliderValue_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.UpdateSliderMaterial
// ()
// Parameters:
// float                          Hue                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          SecondaryValue                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slider_C::UpdateSliderMaterial(float Hue, float SecondaryValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.UpdateSliderMaterial");

	UWidget_ColorPicker_Slider_C_UpdateSliderMaterial_Params params;
	params.Hue = Hue;
	params.SecondaryValue = SecondaryValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_109_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slider_C::BndEvt__Slider_0_K2Node_ComponentBoundEvent_109_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_109_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_ColorPicker_Slider_C_BndEvt__Slider_0_K2Node_ComponentBoundEvent_109_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.BndEvt__mInputText_K2Node_ComponentBoundEvent_270_OnEditableTextBoxCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slider_C::BndEvt__mInputText_K2Node_ComponentBoundEvent_270_OnEditableTextBoxCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.BndEvt__mInputText_K2Node_ComponentBoundEvent_270_OnEditableTextBoxCommittedEvent__DelegateSignature");

	UWidget_ColorPicker_Slider_C_BndEvt__mInputText_K2Node_ComponentBoundEvent_270_OnEditableTextBoxCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slider_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.PreConstruct");

	UWidget_ColorPicker_Slider_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.ExecuteUbergraph_Widget_ColorPicker_Slider
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slider_C::ExecuteUbergraph_Widget_ColorPicker_Slider(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.ExecuteUbergraph_Widget_ColorPicker_Slider");

	UWidget_ColorPicker_Slider_C_ExecuteUbergraph_Widget_ColorPicker_Slider_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.OnValueChanged__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_Slider_C::OnValueChanged__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker_SLider.Widget_ColorPicker_Slider_C.OnValueChanged__DelegateSignature");

	UWidget_ColorPicker_Slider_C_OnValueChanged__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
