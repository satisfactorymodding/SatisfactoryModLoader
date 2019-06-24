// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_LetterSpacedLetter_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.SetTextAndFont
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FSlateFontInfo          Font                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_LetterSpacedLetter_C::SetTextAndFont(const struct FText& Text, const struct FSlateFontInfo& Font)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.SetTextAndFont");

	UWidget_LetterSpacedLetter_C_SetTextAndFont_Params params;
	params.Text = Text;
	params.Font = Font;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_LetterSpacedLetter_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.PreConstruct");

	UWidget_LetterSpacedLetter_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.ExecuteUbergraph_Widget_LetterSpacedLetter
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_LetterSpacedLetter_C::ExecuteUbergraph_Widget_LetterSpacedLetter(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.ExecuteUbergraph_Widget_LetterSpacedLetter");

	UWidget_LetterSpacedLetter_C_ExecuteUbergraph_Widget_LetterSpacedLetter_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
