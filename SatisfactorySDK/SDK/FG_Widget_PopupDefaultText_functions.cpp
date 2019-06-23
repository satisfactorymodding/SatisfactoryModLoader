// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupDefaultText_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PopupDefaultText.Widget_PopupDefaultText_C.Construct
// ()

void UWidget_PopupDefaultText_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupDefaultText.Widget_PopupDefaultText_C.Construct");

	UWidget_PopupDefaultText_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PopupDefaultText.Widget_PopupDefaultText_C.ExecuteUbergraph_Widget_PopupDefaultText
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PopupDefaultText_C::ExecuteUbergraph_Widget_PopupDefaultText(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PopupDefaultText.Widget_PopupDefaultText_C.ExecuteUbergraph_Widget_PopupDefaultText");

	UWidget_PopupDefaultText_C_ExecuteUbergraph_Widget_PopupDefaultText_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
