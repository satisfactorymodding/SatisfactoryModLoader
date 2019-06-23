// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManufacturingIOSlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.ConstructFromManufacturingWidget
// ()
// Parameters:
// class UWidget_Manufacturing_C* WidgetManufacturing            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManufacturingIOSlot_C::ConstructFromManufacturingWidget(class UWidget_Manufacturing_C* WidgetManufacturing)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.ConstructFromManufacturingWidget");

	UWidget_ManufacturingIOSlot_C_ConstructFromManufacturingWidget_Params params;
	params.WidgetManufacturing = WidgetManufacturing;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.UpdateOutputTooltip
// ()

void UWidget_ManufacturingIOSlot_C::UpdateOutputTooltip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.UpdateOutputTooltip");

	UWidget_ManufacturingIOSlot_C_UpdateOutputTooltip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetDividerTopVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManufacturingIOSlot_C::GetDividerTopVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetDividerTopVisibility");

	UWidget_ManufacturingIOSlot_C_GetDividerTopVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetDividerVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManufacturingIOSlot_C::GetDividerVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetDividerVisibility");

	UWidget_ManufacturingIOSlot_C_GetDividerVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetInputInfoVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManufacturingIOSlot_C::GetInputInfoVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetInputInfoVisibility");

	UWidget_ManufacturingIOSlot_C_GetInputInfoVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetNumPerSecond
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ManufacturingIOSlot_C::GetNumPerSecond()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetNumPerSecond");

	UWidget_ManufacturingIOSlot_C_GetNumPerSecond_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetOutputSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManufacturingIOSlot_C::GetOutputSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetOutputSlotVisibility");

	UWidget_ManufacturingIOSlot_C_GetOutputSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemNum
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ManufacturingIOSlot_C::GetItemNum()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemNum");

	UWidget_ManufacturingIOSlot_C_GetItemNum_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemAmount
// ()
// Parameters:
// struct FItemAmount             ItemAmount                     (Parm, OutParm)

void UWidget_ManufacturingIOSlot_C::GetItemAmount(struct FItemAmount* ItemAmount)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemAmount");

	UWidget_ManufacturingIOSlot_C_GetItemAmount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ItemAmount != nullptr)
		*ItemAmount = params.ItemAmount;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ManufacturingIOSlot_C::GetItemName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemName");

	UWidget_ManufacturingIOSlot_C_GetItemName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.Construct
// ()

void UWidget_ManufacturingIOSlot_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.Construct");

	UWidget_ManufacturingIOSlot_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.Set CostSlot
// ()
// Parameters:
// int                            SlotIdx                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManufacturingIOSlot_C::Set_CostSlot(int SlotIdx)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.Set CostSlot");

	UWidget_ManufacturingIOSlot_C_Set_CostSlot_Params params;
	params.SlotIdx = SlotIdx;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.ExecuteUbergraph_Widget_ManufacturingIOSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManufacturingIOSlot_C::ExecuteUbergraph_Widget_ManufacturingIOSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.ExecuteUbergraph_Widget_ManufacturingIOSlot");

	UWidget_ManufacturingIOSlot_C_ExecuteUbergraph_Widget_ManufacturingIOSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
