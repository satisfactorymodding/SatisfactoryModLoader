// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorPicker.Widget_ColorPicker_C.GetResetButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ColorPicker_C::GetResetButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.GetResetButtonVisibility");

	UWidget_ColorPicker_C_GetResetButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.GetOneDimensionalIndex
// ()
// Parameters:
// int                            ColorIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            shadeIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            Index                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_C::GetOneDimensionalIndex(int ColorIndex, int shadeIndex, int* Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.GetOneDimensionalIndex");

	UWidget_ColorPicker_C_GetOneDimensionalIndex_Params params;
	params.ColorIndex = ColorIndex;
	params.shadeIndex = shadeIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Index != nullptr)
		*Index = params.Index;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.GetSavedColorFromIndexes
// ()
// Parameters:
// int                            ColorIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            shadeIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             SavedColor                     (Parm, OutParm)

void UWidget_ColorPicker_C::GetSavedColorFromIndexes(int ColorIndex, int shadeIndex, struct FSlateColor* SavedColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.GetSavedColorFromIndexes");

	UWidget_ColorPicker_C_GetSavedColorFromIndexes_Params params;
	params.ColorIndex = ColorIndex;
	params.shadeIndex = shadeIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (SavedColor != nullptr)
		*SavedColor = params.SavedColor;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.CalculateSaturationAndValueFromIndex
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Saturation                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// float                          Value                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_C::CalculateSaturationAndValueFromIndex(int Index, float* Saturation, float* Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.CalculateSaturationAndValueFromIndex");

	UWidget_ColorPicker_C_CalculateSaturationAndValueFromIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Saturation != nullptr)
		*Saturation = params.Saturation;
	if (Value != nullptr)
		*Value = params.Value;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.CalculateHueFromIndex
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Hue                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_C::CalculateHueFromIndex(int Index, float* Hue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.CalculateHueFromIndex");

	UWidget_ColorPicker_C_CalculateHueFromIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Hue != nullptr)
		*Hue = params.Hue;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.FirstTimeFillColors
// ()

void UWidget_ColorPicker_C::FirstTimeFillColors()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.FirstTimeFillColors");

	UWidget_ColorPicker_C_FirstTimeFillColors_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.GetFinalColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ColorPicker_C::GetFinalColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.GetFinalColor");

	UWidget_ColorPicker_C_GetFinalColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.CloseColorPicker
// ()

void UWidget_ColorPicker_C::CloseColorPicker()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.CloseColorPicker");

	UWidget_ColorPicker_C_CloseColorPicker_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.Construct
// ()

void UWidget_ColorPicker_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.Construct");

	UWidget_ColorPicker_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.Init
// ()

void UWidget_ColorPicker_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.Init");

	UWidget_ColorPicker_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.ExitColorPicker
// ()

void UWidget_ColorPicker_C::ExitColorPicker()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.ExitColorPicker");

	UWidget_ColorPicker_C_ExitColorPicker_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mCancelButton_K2Node_ComponentBoundEvent_36_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_C::BndEvt__mCancelButton_K2Node_ComponentBoundEvent_36_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mCancelButton_K2Node_ComponentBoundEvent_36_OnClicked__DelegateSignature");

	UWidget_ColorPicker_C_BndEvt__mCancelButton_K2Node_ComponentBoundEvent_36_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.Tick");

	UWidget_ColorPicker_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mResetButton_K2Node_ComponentBoundEvent_31_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_C::BndEvt__mResetButton_K2Node_ComponentBoundEvent_31_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mResetButton_K2Node_ComponentBoundEvent_31_OnClicked__DelegateSignature");

	UWidget_ColorPicker_C_BndEvt__mResetButton_K2Node_ComponentBoundEvent_31_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_331_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_C::BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_331_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_331_OnClicked__DelegateSignature");

	UWidget_ColorPicker_C_BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_331_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
// ()

void UWidget_ColorPicker_C::BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature");

	UWidget_ColorPicker_C_BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_C::BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_ColorPicker_C_BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mReset_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_C::BndEvt__mReset_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mReset_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature");

	UWidget_ColorPicker_C_BndEvt__mReset_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mAccept_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
// ()

void UWidget_ColorPicker_C::BndEvt__mAccept_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mAccept_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature");

	UWidget_ColorPicker_C_BndEvt__mAccept_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.ExecuteUbergraph_Widget_ColorPicker
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_C::ExecuteUbergraph_Widget_ColorPicker(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.ExecuteUbergraph_Widget_ColorPicker");

	UWidget_ColorPicker_C_ExecuteUbergraph_Widget_ColorPicker_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorPicker.Widget_ColorPicker_C.mOnColorPicked__DelegateSignature
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorPicker_C::mOnColorPicked__DelegateSignature(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorPicker.Widget_ColorPicker_C.mOnColorPicked__DelegateSignature");

	UWidget_ColorPicker_C_mOnColorPicked__DelegateSignature_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
