// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CheatPowerSink_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.OnGetPowerCircuit
// ()
// Parameters:
// class UFGPowerCircuit*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UFGPowerCircuit* UWidget_CheatPowerSink_C::OnGetPowerCircuit()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.OnGetPowerCircuit");

	UWidget_CheatPowerSink_C_OnGetPowerCircuit_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.SetPowerSliderValue
// ()

void UWidget_CheatPowerSink_C::SetPowerSliderValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.SetPowerSliderValue");

	UWidget_CheatPowerSink_C_SetPowerSliderValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.GetActualPowerText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CheatPowerSink_C::GetActualPowerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.GetActualPowerText");

	UWidget_CheatPowerSink_C_GetActualPowerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.GetPowerText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CheatPowerSink_C::GetPowerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.GetPowerText");

	UWidget_CheatPowerSink_C_GetPowerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CheatPowerSink_C::BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_CheatPowerSink_C_BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.Init
// ()

void UWidget_CheatPowerSink_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.Init");

	UWidget_CheatPowerSink_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.ExecuteUbergraph_Widget_CheatPowerSink
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CheatPowerSink_C::ExecuteUbergraph_Widget_CheatPowerSink(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.ExecuteUbergraph_Widget_CheatPowerSink");

	UWidget_CheatPowerSink_C_ExecuteUbergraph_Widget_CheatPowerSink_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
