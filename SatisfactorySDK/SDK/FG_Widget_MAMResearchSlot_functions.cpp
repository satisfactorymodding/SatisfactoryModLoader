// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MAMResearchSlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.DropOntoInventorySlot
// ()
// Parameters:
// class UWidget_InventorySlot_C* InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_MAMResearchSlot_C::DropOntoInventorySlot(class UWidget_InventorySlot_C* InventorySlot, bool* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.DropOntoInventorySlot");

	UWidget_MAMResearchSlot_C_DropOntoInventorySlot_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetCustomTooltip
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_MAMResearchSlot_C::GetCustomTooltip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetCustomTooltip");

	UWidget_MAMResearchSlot_C_GetCustomTooltip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_MAMResearchSlot_C::GetPaidOffSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffSlotVisibility");

	UWidget_MAMResearchSlot_C_GetPaidOffSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetProgressbarVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_MAMResearchSlot_C::GetProgressbarVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetProgressbarVisibility");

	UWidget_MAMResearchSlot_C_GetProgressbarVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffColorFeedback
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_MAMResearchSlot_C::GetPaidOffColorFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffColorFeedback");

	UWidget_MAMResearchSlot_C_GetPaidOffColorFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffFeedbackImage
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_MAMResearchSlot_C::GetPaidOffFeedbackImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffFeedbackImage");

	UWidget_MAMResearchSlot_C_GetPaidOffFeedbackImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetProgressbarPercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_MAMResearchSlot_C::GetProgressbarPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetProgressbarPercent");

	UWidget_MAMResearchSlot_C_GetProgressbarPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_MAMResearchSlot_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.OnDrop");

	UWidget_MAMResearchSlot_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemQuotaText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_MAMResearchSlot_C::GetItemQuotaText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemQuotaText");

	UWidget_MAMResearchSlot_C_GetItemQuotaText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_MAMResearchSlot_C::GetItemText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemText");

	UWidget_MAMResearchSlot_C_GetItemText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemImage
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_MAMResearchSlot_C::GetItemImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemImage");

	UWidget_MAMResearchSlot_C_GetItemImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAMResearchSlot_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.Tick");

	UWidget_MAMResearchSlot_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.ExecuteUbergraph_Widget_MAMResearchSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAMResearchSlot_C::ExecuteUbergraph_Widget_MAMResearchSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.ExecuteUbergraph_Widget_MAMResearchSlot");

	UWidget_MAMResearchSlot_C_ExecuteUbergraph_Widget_MAMResearchSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
