// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_OptionsSlider_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetDisplayValue
// ()
// Parameters:
// float                          DisplayValue                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_OptionsSlider_C::GetDisplayValue(float* DisplayValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetDisplayValue");

	UWidget_OptionsSlider_C_GetDisplayValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (DisplayValue != nullptr)
		*DisplayValue = params.DisplayValue;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.SetNormalizedValue
// ()
// Parameters:
// float                          CurrentUnadjustedValue         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_OptionsSlider_C::SetNormalizedValue(float CurrentUnadjustedValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.SetNormalizedValue");

	UWidget_OptionsSlider_C_SetNormalizedValue_Params params;
	params.CurrentUnadjustedValue = CurrentUnadjustedValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetAdjustedValue
// ()
// Parameters:
// float                          AdjustedValue                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_OptionsSlider_C::GetAdjustedValue(float* AdjustedValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetAdjustedValue");

	UWidget_OptionsSlider_C_GetAdjustedValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (AdjustedValue != nullptr)
		*AdjustedValue = params.AdjustedValue;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.SetProgressBarPercentage
// ()
// Parameters:
// float                          Percent                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_OptionsSlider_C::SetProgressBarPercentage(float Percent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.SetProgressBarPercentage");

	UWidget_OptionsSlider_C_SetProgressBarPercentage_Params params;
	params.Percent = Percent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetProgressBarPercentage
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_OptionsSlider_C::GetProgressBarPercentage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetProgressBarPercentage");

	UWidget_OptionsSlider_C_GetProgressBarPercentage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetValueText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_OptionsSlider_C::GetValueText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetValueText");

	UWidget_OptionsSlider_C_GetValueText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.BndEvt__OptionSlider_K2Node_ComponentBoundEvent_104_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_OptionsSlider_C::BndEvt__OptionSlider_K2Node_ComponentBoundEvent_104_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.BndEvt__OptionSlider_K2Node_ComponentBoundEvent_104_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_OptionsSlider_C_BndEvt__OptionSlider_K2Node_ComponentBoundEvent_104_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.OnRowHovered
// ()

void UWidget_OptionsSlider_C::OnRowHovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.OnRowHovered");

	UWidget_OptionsSlider_C_OnRowHovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.OnRowUnhovered
// ()

void UWidget_OptionsSlider_C::OnRowUnhovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.OnRowUnhovered");

	UWidget_OptionsSlider_C_OnRowUnhovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.ExecuteUbergraph_Widget_OptionsSlider
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_OptionsSlider_C::ExecuteUbergraph_Widget_OptionsSlider(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.ExecuteUbergraph_Widget_OptionsSlider");

	UWidget_OptionsSlider_C_ExecuteUbergraph_Widget_OptionsSlider_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetNewValue__DelegateSignature
// ()
// Parameters:
// float                          NewValue                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_OptionsSlider_C::GetNewValue__DelegateSignature(float NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetNewValue__DelegateSignature");

	UWidget_OptionsSlider_C_GetNewValue__DelegateSignature_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
