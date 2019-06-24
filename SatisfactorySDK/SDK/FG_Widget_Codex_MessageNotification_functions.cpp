// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_MessageNotification_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Codex_MessageNotification.Widget_Codex_MessageNotification_C.GetText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Codex_MessageNotification_C::GetText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_MessageNotification.Widget_Codex_MessageNotification_C.GetText");

	UWidget_Codex_MessageNotification_C_GetText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
