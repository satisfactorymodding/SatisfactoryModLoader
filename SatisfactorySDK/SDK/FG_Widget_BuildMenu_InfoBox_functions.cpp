// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenu_InfoBox_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_BuildMenu_InfoBox.Widget_BuildMenu_InfoBox_C.GetStatsVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_BuildMenu_InfoBox_C::GetStatsVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_InfoBox.Widget_BuildMenu_InfoBox_C.GetStatsVisibility");

	UWidget_BuildMenu_InfoBox_C_GetStatsVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu_InfoBox.Widget_BuildMenu_InfoBox_C.AnimateCostSlots
// ()

void UWidget_BuildMenu_InfoBox_C::AnimateCostSlots()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_InfoBox.Widget_BuildMenu_InfoBox_C.AnimateCostSlots");

	UWidget_BuildMenu_InfoBox_C_AnimateCostSlots_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_InfoBox.Widget_BuildMenu_InfoBox_C.ExecuteUbergraph_Widget_BuildMenu_InfoBox
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_InfoBox_C::ExecuteUbergraph_Widget_BuildMenu_InfoBox(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_InfoBox.Widget_BuildMenu_InfoBox_C.ExecuteUbergraph_Widget_BuildMenu_InfoBox");

	UWidget_BuildMenu_InfoBox_C_ExecuteUbergraph_Widget_BuildMenu_InfoBox_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
