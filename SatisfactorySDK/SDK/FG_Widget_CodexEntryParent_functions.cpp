// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexEntryParent_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CodexEntryParent.Widget_CodexEntryParent_C.GetStats
// ()

void UWidget_CodexEntryParent_C::GetStats()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexEntryParent.Widget_CodexEntryParent_C.GetStats");

	UWidget_CodexEntryParent_C_GetStats_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexEntryParent.Widget_CodexEntryParent_C.Construct
// ()

void UWidget_CodexEntryParent_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexEntryParent.Widget_CodexEntryParent_C.Construct");

	UWidget_CodexEntryParent_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexEntryParent.Widget_CodexEntryParent_C.ExecuteUbergraph_Widget_CodexEntryParent
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CodexEntryParent_C::ExecuteUbergraph_Widget_CodexEntryParent(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexEntryParent.Widget_CodexEntryParent_C.ExecuteUbergraph_Widget_CodexEntryParent");

	UWidget_CodexEntryParent_C_ExecuteUbergraph_Widget_CodexEntryParent_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
