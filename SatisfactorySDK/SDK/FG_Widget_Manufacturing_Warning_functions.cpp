// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Manufacturing_Warning_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.HideWarning
// ()

void UWidget_Manufacturing_Warning_C::HideWarning()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.HideWarning");

	UWidget_Manufacturing_Warning_C_HideWarning_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.UpdateWarning
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Manufacturing_Warning_C::UpdateWarning(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.UpdateWarning");

	UWidget_Manufacturing_Warning_C_UpdateWarning_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.SetText
// ()
// Parameters:
// struct FText                   InText                         (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Manufacturing_Warning_C::SetText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.SetText");

	UWidget_Manufacturing_Warning_C_SetText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.GetWarningText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Manufacturing_Warning_C::GetWarningText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.GetWarningText");

	UWidget_Manufacturing_Warning_C_GetWarningText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.Construct
// ()

void UWidget_Manufacturing_Warning_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.Construct");

	UWidget_Manufacturing_Warning_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Manufacturing_Warning_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.PreConstruct");

	UWidget_Manufacturing_Warning_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.ExecuteUbergraph_Widget_Manufacturing_Warning
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Manufacturing_Warning_C::ExecuteUbergraph_Widget_Manufacturing_Warning(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.ExecuteUbergraph_Widget_Manufacturing_Warning");

	UWidget_Manufacturing_Warning_C_ExecuteUbergraph_Widget_Manufacturing_Warning_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
