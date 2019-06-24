// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TutorialInfo_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TutorialInfo.Widget_TutorialInfo_C.Construct
// ()

void UWidget_TutorialInfo_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TutorialInfo.Widget_TutorialInfo_C.Construct");

	UWidget_TutorialInfo_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TutorialInfo.Widget_TutorialInfo_C.ExecuteUbergraph_Widget_TutorialInfo
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TutorialInfo_C::ExecuteUbergraph_Widget_TutorialInfo(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TutorialInfo.Widget_TutorialInfo_C.ExecuteUbergraph_Widget_TutorialInfo");

	UWidget_TutorialInfo_C_ExecuteUbergraph_Widget_TutorialInfo_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
