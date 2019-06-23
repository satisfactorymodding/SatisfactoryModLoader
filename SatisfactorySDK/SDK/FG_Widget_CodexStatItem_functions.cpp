// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexStatItem_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CodexStatItem.Widget_CodexStatItem_C.Construct
// ()

void UWidget_CodexStatItem_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexStatItem.Widget_CodexStatItem_C.Construct");

	UWidget_CodexStatItem_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexStatItem.Widget_CodexStatItem_C.ExecuteUbergraph_Widget_CodexStatItem
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CodexStatItem_C::ExecuteUbergraph_Widget_CodexStatItem(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexStatItem.Widget_CodexStatItem_C.ExecuteUbergraph_Widget_CodexStatItem");

	UWidget_CodexStatItem_C_ExecuteUbergraph_Widget_CodexStatItem_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
