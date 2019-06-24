// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Credit_Trademark_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.ShowHideText
// ()

void UWidget_Credit_Trademark_C::ShowHideText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.ShowHideText");

	UWidget_Credit_Trademark_C_ShowHideText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.SetText
// ()
// Parameters:
// struct FText                   mText                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Credit_Trademark_C::SetText(const struct FText& mText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.SetText");

	UWidget_Credit_Trademark_C_SetText_Params params;
	params.mText = mText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Credit_Trademark_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.PreConstruct");

	UWidget_Credit_Trademark_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.Construct
// ()

void UWidget_Credit_Trademark_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.Construct");

	UWidget_Credit_Trademark_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.ExecuteUbergraph_Widget_Credit_Trademark
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Credit_Trademark_C::ExecuteUbergraph_Widget_Credit_Trademark(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.ExecuteUbergraph_Widget_Credit_Trademark");

	UWidget_Credit_Trademark_C_ExecuteUbergraph_Widget_Credit_Trademark_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
