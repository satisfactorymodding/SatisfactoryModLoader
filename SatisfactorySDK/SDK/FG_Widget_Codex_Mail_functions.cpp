// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_Mail_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Codex_Mail.Widget_Codex_Mail_C.Construct
// ()

void UWidget_Codex_Mail_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Mail.Widget_Codex_Mail_C.Construct");

	UWidget_Codex_Mail_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Codex_Mail.Widget_Codex_Mail_C.ExecuteUbergraph_Widget_Codex_Mail
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Codex_Mail_C::ExecuteUbergraph_Widget_Codex_Mail(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Codex_Mail.Widget_Codex_Mail_C.ExecuteUbergraph_Widget_Codex_Mail");

	UWidget_Codex_Mail_C_ExecuteUbergraph_Widget_Codex_Mail_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
