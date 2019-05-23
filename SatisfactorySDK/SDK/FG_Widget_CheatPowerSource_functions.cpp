// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CheatPowerSource_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.OnGetPowerCircuit
// ()
// Parameters:
// class UFGPowerCircuit*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UFGPowerCircuit* UWidget_CheatPowerSource_C::OnGetPowerCircuit()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.OnGetPowerCircuit");

	UWidget_CheatPowerSource_C_OnGetPowerCircuit_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.SetDynamicPowerSliderValue
// ()

void UWidget_CheatPowerSource_C::SetDynamicPowerSliderValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.SetDynamicPowerSliderValue");

	UWidget_CheatPowerSource_C_SetDynamicPowerSliderValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.SetBasePowerSliderValue
// ()

void UWidget_CheatPowerSource_C::SetBasePowerSliderValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.SetBasePowerSliderValue");

	UWidget_CheatPowerSource_C_SetBasePowerSliderValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetTotalProductionText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CheatPowerSource_C::GetTotalProductionText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetTotalProductionText");

	UWidget_CheatPowerSource_C_GetTotalProductionText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsagePercentColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_CheatPowerSource_C::GetDynamicUsagePercentColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsagePercentColor");

	UWidget_CheatPowerSource_C_GetDynamicUsagePercentColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsageText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CheatPowerSource_C::GetDynamicUsageText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsageText");

	UWidget_CheatPowerSource_C_GetDynamicUsageText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsagePercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_CheatPowerSource_C::GetDynamicUsagePercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsagePercent");

	UWidget_CheatPowerSource_C_GetDynamicUsagePercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetBasePowerText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CheatPowerSource_C::GetBasePowerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetBasePowerText");

	UWidget_CheatPowerSource_C_GetBasePowerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicPowerText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CheatPowerSource_C::GetDynamicPowerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicPowerText");

	UWidget_CheatPowerSource_C_GetDynamicPowerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CheatPowerSource_C::BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_CheatPowerSource_C_BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.BndEvt__mDynamicPowerSlider_K2Node_ComponentBoundEvent_233_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CheatPowerSource_C::BndEvt__mDynamicPowerSlider_K2Node_ComponentBoundEvent_233_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.BndEvt__mDynamicPowerSlider_K2Node_ComponentBoundEvent_233_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_CheatPowerSource_C_BndEvt__mDynamicPowerSlider_K2Node_ComponentBoundEvent_233_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.Init
// ()

void UWidget_CheatPowerSource_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.Init");

	UWidget_CheatPowerSource_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.ExecuteUbergraph_Widget_CheatPowerSource
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CheatPowerSource_C::ExecuteUbergraph_Widget_CheatPowerSource(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.ExecuteUbergraph_Widget_CheatPowerSource");

	UWidget_CheatPowerSource_C_ExecuteUbergraph_Widget_CheatPowerSource_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
