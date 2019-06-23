// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Label_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Label.Widget_Label_C.SetLabelText
// ()
// Parameters:
// struct FText                   LabelText                      (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Label_C::SetLabelText(const struct FText& LabelText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Label.Widget_Label_C.SetLabelText");

	UWidget_Label_C_SetLabelText_Params params;
	params.LabelText = LabelText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Label.Widget_Label_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Label_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Label.Widget_Label_C.PreConstruct");

	UWidget_Label_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Label.Widget_Label_C.ExecuteUbergraph_Widget_Label
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Label_C::ExecuteUbergraph_Widget_Label(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Label.Widget_Label_C.ExecuteUbergraph_Widget_Label");

	UWidget_Label_C_ExecuteUbergraph_Widget_Label_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
