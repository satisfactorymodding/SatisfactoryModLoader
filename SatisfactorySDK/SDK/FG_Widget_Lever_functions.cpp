// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Lever_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Lever.Widget_Lever_C.LeverShake
// ()
// Parameters:
// int                            MaxOrMinSelectionIndex         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Lever_C::LeverShake(int MaxOrMinSelectionIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.LeverShake");

	UWidget_Lever_C_LeverShake_Params params;
	params.MaxOrMinSelectionIndex = MaxOrMinSelectionIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.OnShake
// ()

void UWidget_Lever_C::OnShake()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.OnShake");

	UWidget_Lever_C_OnShake_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.SetShowButton
// ()
// Parameters:
// bool                           ShowButton                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Lever_C::SetShowButton(bool ShowButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.SetShowButton");

	UWidget_Lever_C_SetShowButton_Params params;
	params.ShowButton = ShowButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.StartLerp
// ()

void UWidget_Lever_C::StartLerp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.StartLerp");

	UWidget_Lever_C_StartLerp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.GetCurrentSelectionPosOnSlider
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_Lever_C::GetCurrentSelectionPosOnSlider()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.GetCurrentSelectionPosOnSlider");

	UWidget_Lever_C_GetCurrentSelectionPosOnSlider_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Lever.Widget_Lever_C.GetCalculatedCurve
// ()
// Parameters:
// class UCurveFloat*             CurveFloat                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          InTime                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_Lever_C::GetCalculatedCurve(class UCurveFloat* CurveFloat, float InTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.GetCalculatedCurve");

	UWidget_Lever_C_GetCalculatedCurve_Params params;
	params.CurveFloat = CurveFloat;
	params.InTime = InTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Lever.Widget_Lever_C.GetSliderMinClamp
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_Lever_C::GetSliderMinClamp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.GetSliderMinClamp");

	UWidget_Lever_C_GetSliderMinClamp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Lever.Widget_Lever_C.GetSliderMaxClamp
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_Lever_C::GetSliderMaxClamp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.GetSliderMaxClamp");

	UWidget_Lever_C_GetSliderMaxClamp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Lever.Widget_Lever_C.SetHandle
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Lever_C::SetHandle(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.SetHandle");

	UWidget_Lever_C_SetHandle_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Lever_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.PreConstruct");

	UWidget_Lever_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.Construct
// ()

void UWidget_Lever_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.Construct");

	UWidget_Lever_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Lever_C::BndEvt__LeverHandle_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_3_OnMouseCaptureEndEvent__DelegateSignature
// ()

void UWidget_Lever_C::BndEvt__LeverHandle_K2Node_ComponentBoundEvent_3_OnMouseCaptureEndEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_3_OnMouseCaptureEndEvent__DelegateSignature");

	UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_3_OnMouseCaptureEndEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_4_OnControllerCaptureEndEvent__DelegateSignature
// ()

void UWidget_Lever_C::BndEvt__LeverHandle_K2Node_ComponentBoundEvent_4_OnControllerCaptureEndEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_4_OnControllerCaptureEndEvent__DelegateSignature");

	UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_4_OnControllerCaptureEndEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.LerpLever
// ()

void UWidget_Lever_C::LerpLever()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.LerpLever");

	UWidget_Lever_C_LerpLever_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_5_OnMouseCaptureBeginEvent__DelegateSignature
// ()

void UWidget_Lever_C::BndEvt__LeverHandle_K2Node_ComponentBoundEvent_5_OnMouseCaptureBeginEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_5_OnMouseCaptureBeginEvent__DelegateSignature");

	UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_5_OnMouseCaptureBeginEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_6_OnControllerCaptureBeginEvent__DelegateSignature
// ()

void UWidget_Lever_C::BndEvt__LeverHandle_K2Node_ComponentBoundEvent_6_OnControllerCaptureBeginEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_6_OnControllerCaptureBeginEvent__DelegateSignature");

	UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_6_OnControllerCaptureBeginEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.ExecuteUbergraph_Widget_Lever
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Lever_C::ExecuteUbergraph_Widget_Lever(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.ExecuteUbergraph_Widget_Lever");

	UWidget_Lever_C_ExecuteUbergraph_Widget_Lever_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Lever.Widget_Lever_C.OnNewSelection__DelegateSignature
// ()
// Parameters:
// int                            SelectionIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Lever_C::OnNewSelection__DelegateSignature(int SelectionIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Lever.Widget_Lever_C.OnNewSelection__DelegateSignature");

	UWidget_Lever_C_OnNewSelection__DelegateSignature_Params params;
	params.SelectionIndex = SelectionIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
