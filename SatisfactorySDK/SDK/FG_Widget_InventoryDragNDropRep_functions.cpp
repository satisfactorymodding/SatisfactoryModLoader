// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventoryDragNDropRep_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetTextBackgroundColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_InventoryDragNDropRep_C::GetTextBackgroundColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetTextBackgroundColor");

	UWidget_InventoryDragNDropRep_C_GetTextBackgroundColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetSlotColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_InventoryDragNDropRep_C::GetSlotColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetSlotColor");

	UWidget_InventoryDragNDropRep_C_GetSlotColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetBorderVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_InventoryDragNDropRep_C::GetBorderVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetBorderVisibility");

	UWidget_InventoryDragNDropRep_C_GetBorderVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetStackSizeVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_InventoryDragNDropRep_C::GetStackSizeVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetStackSizeVisibility");

	UWidget_InventoryDragNDropRep_C_GetStackSizeVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetItemBrush
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_InventoryDragNDropRep_C::GetItemBrush()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetItemBrush");

	UWidget_InventoryDragNDropRep_C_GetItemBrush_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetStackSizeText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_InventoryDragNDropRep_C::GetStackSizeText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.GetStackSizeText");

	UWidget_InventoryDragNDropRep_C_GetStackSizeText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.Construct
// ()

void UWidget_InventoryDragNDropRep_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.Construct");

	UWidget_InventoryDragNDropRep_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.Destruct
// ()

void UWidget_InventoryDragNDropRep_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.Destruct");

	UWidget_InventoryDragNDropRep_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.ExecuteUbergraph_Widget_InventoryDragNDropRep
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventoryDragNDropRep_C::ExecuteUbergraph_Widget_InventoryDragNDropRep(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventoryDragNDropRep.Widget_InventoryDragNDropRep_C.ExecuteUbergraph_Widget_InventoryDragNDropRep");

	UWidget_InventoryDragNDropRep_C_ExecuteUbergraph_Widget_InventoryDragNDropRep_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
