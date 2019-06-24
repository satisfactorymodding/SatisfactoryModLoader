// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_LetterSpacedText_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_LetterSpacedText_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.PreConstruct");

	UWidget_LetterSpacedText_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.SetTitle
// ()
// Parameters:
// class FString                  Text                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UWidget_LetterSpacedText_C::SetTitle(const class FString& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.SetTitle");

	UWidget_LetterSpacedText_C_SetTitle_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.OnAnimateText
// ()

void UWidget_LetterSpacedText_C::OnAnimateText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.OnAnimateText");

	UWidget_LetterSpacedText_C_OnAnimateText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.Construct
// ()

void UWidget_LetterSpacedText_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.Construct");

	UWidget_LetterSpacedText_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.ExecuteUbergraph_Widget_LetterSpacedText
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_LetterSpacedText_C::ExecuteUbergraph_Widget_LetterSpacedText(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.ExecuteUbergraph_Widget_LetterSpacedText");

	UWidget_LetterSpacedText_C_ExecuteUbergraph_Widget_LetterSpacedText_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
