// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ProgressBar_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ProgressBar.Widget_ProgressBar_C.GetCurveType
// ()
// Parameters:
// class UCurveFloat*             Curve                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgressBar_C::GetCurveType(class UCurveFloat** Curve)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgressBar.Widget_ProgressBar_C.GetCurveType");

	UWidget_ProgressBar_C_GetCurveType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Curve != nullptr)
		*Curve = params.Curve;
}


// Function Widget_ProgressBar.Widget_ProgressBar_C.SetProgressBarFillColor
// ()
// Parameters:
// float                          InputValue                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgressBar_C::SetProgressBarFillColor(float InputValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgressBar.Widget_ProgressBar_C.SetProgressBarFillColor");

	UWidget_ProgressBar_C_SetProgressBarFillColor_Params params;
	params.InputValue = InputValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ProgressBar.Widget_ProgressBar_C.LerpBar
// ()
// Parameters:
// float                          StartValue                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          EndValue                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          LerpTime                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgressBar_C::LerpBar(float StartValue, float EndValue, float LerpTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgressBar.Widget_ProgressBar_C.LerpBar");

	UWidget_ProgressBar_C_LerpBar_Params params;
	params.StartValue = StartValue;
	params.EndValue = EndValue;
	params.LerpTime = LerpTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ProgressBar.Widget_ProgressBar_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgressBar_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgressBar.Widget_ProgressBar_C.PreConstruct");

	UWidget_ProgressBar_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ProgressBar.Widget_ProgressBar_C.ExecuteUbergraph_Widget_ProgressBar
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgressBar_C::ExecuteUbergraph_Widget_ProgressBar(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgressBar.Widget_ProgressBar_C.ExecuteUbergraph_Widget_ProgressBar");

	UWidget_ProgressBar_C_ExecuteUbergraph_Widget_ProgressBar_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
