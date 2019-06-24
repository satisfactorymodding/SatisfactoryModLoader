// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HotbarEntry_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetIconVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_HotbarEntry_C::GetIconVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetIconVisibility");

	UWidget_HotbarEntry_C_GetIconVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_HotbarEntry_C::GetSlotTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotTextColor");

	UWidget_HotbarEntry_C_GetSlotTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotBrush
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_HotbarEntry_C::GetSlotBrush()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotBrush");

	UWidget_HotbarEntry_C_GetSlotBrush_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_HotbarEntry_C::GetSlotText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetSlotText");

	UWidget_HotbarEntry_C_GetSlotText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_HotbarEntry_C::GetIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarEntry.Widget_HotbarEntry_C.GetIcon");

	UWidget_HotbarEntry_C_GetIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_HotbarEntry.Widget_HotbarEntry_C.OnHotbarUpdated
// ()

void UWidget_HotbarEntry_C::OnHotbarUpdated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarEntry.Widget_HotbarEntry_C.OnHotbarUpdated");

	UWidget_HotbarEntry_C_OnHotbarUpdated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarEntry.Widget_HotbarEntry_C.ExecuteUbergraph_Widget_HotbarEntry
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HotbarEntry_C::ExecuteUbergraph_Widget_HotbarEntry(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarEntry.Widget_HotbarEntry_C.ExecuteUbergraph_Widget_HotbarEntry");

	UWidget_HotbarEntry_C_ExecuteUbergraph_Widget_HotbarEntry_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
