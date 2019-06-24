// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HandSlamCursorHard_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HandSlamCursorHard.Widget_HandSlamCursorHard_C.Construct
// ()

void UWidget_HandSlamCursorHard_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HandSlamCursorHard.Widget_HandSlamCursorHard_C.Construct");

	UWidget_HandSlamCursorHard_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HandSlamCursorHard.Widget_HandSlamCursorHard_C.ExecuteUbergraph_Widget_HandSlamCursorHard
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HandSlamCursorHard_C::ExecuteUbergraph_Widget_HandSlamCursorHard(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HandSlamCursorHard.Widget_HandSlamCursorHard_C.ExecuteUbergraph_Widget_HandSlamCursorHard");

	UWidget_HandSlamCursorHard_C_ExecuteUbergraph_Widget_HandSlamCursorHard_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
