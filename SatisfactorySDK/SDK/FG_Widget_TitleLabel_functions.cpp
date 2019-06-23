// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TitleLabel_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TitleLabel.Widget_TitleLabel_C.SetFicsItDriverText
// ()

void UWidget_TitleLabel_C::SetFicsItDriverText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TitleLabel.Widget_TitleLabel_C.SetFicsItDriverText");

	UWidget_TitleLabel_C_SetFicsItDriverText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TitleLabel.Widget_TitleLabel_C.SetTitle
// ()
// Parameters:
// struct FText                   Title                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_TitleLabel_C::SetTitle(const struct FText& Title)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TitleLabel.Widget_TitleLabel_C.SetTitle");

	UWidget_TitleLabel_C_SetTitle_Params params;
	params.Title = Title;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
