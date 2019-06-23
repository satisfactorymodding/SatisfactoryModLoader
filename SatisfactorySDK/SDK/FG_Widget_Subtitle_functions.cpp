// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Subtitle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Subtitle.Widget_Subtitle_C.GetLightGrayText
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_Subtitle_C::GetLightGrayText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Subtitle.Widget_Subtitle_C.GetLightGrayText");

	UWidget_Subtitle_C_GetLightGrayText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Subtitle.Widget_Subtitle_C.GetOrangeText
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_Subtitle_C::GetOrangeText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Subtitle.Widget_Subtitle_C.GetOrangeText");

	UWidget_Subtitle_C_GetOrangeText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
