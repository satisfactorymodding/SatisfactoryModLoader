// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TutorialHint_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TutorialHint.Widget_TutorialHint_C.Construct
// ()

void UWidget_TutorialHint_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TutorialHint.Widget_TutorialHint_C.Construct");

	UWidget_TutorialHint_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TutorialHint.Widget_TutorialHint_C.ExecuteUbergraph_Widget_TutorialHint
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TutorialHint_C::ExecuteUbergraph_Widget_TutorialHint(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TutorialHint.Widget_TutorialHint_C.ExecuteUbergraph_Widget_TutorialHint");

	UWidget_TutorialHint_C_ExecuteUbergraph_Widget_TutorialHint_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
