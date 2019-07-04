// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SpaceElevatorPayOffSlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.DropOntoInventorySlot
// ()
// Parameters:
// class UWidget_InventorySlot_C* InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevatorPayOffSlot_C::DropOntoInventorySlot(class UWidget_InventorySlot_C* InventorySlot, bool* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.DropOntoInventorySlot");

	UWidget_SpaceElevatorPayOffSlot_C_DropOntoInventorySlot_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetCustomTooltip
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_SpaceElevatorPayOffSlot_C::GetCustomTooltip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetCustomTooltip");

	UWidget_SpaceElevatorPayOffSlot_C_GetCustomTooltip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetPaidOffSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SpaceElevatorPayOffSlot_C::GetPaidOffSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetPaidOffSlotVisibility");

	UWidget_SpaceElevatorPayOffSlot_C_GetPaidOffSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetProgressbarVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SpaceElevatorPayOffSlot_C::GetProgressbarVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetProgressbarVisibility");

	UWidget_SpaceElevatorPayOffSlot_C_GetProgressbarVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetPaidOffColorFeedback
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_SpaceElevatorPayOffSlot_C::GetPaidOffColorFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetPaidOffColorFeedback");

	UWidget_SpaceElevatorPayOffSlot_C_GetPaidOffColorFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetPaidOffFeedbackImage
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SpaceElevatorPayOffSlot_C::GetPaidOffFeedbackImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetPaidOffFeedbackImage");

	UWidget_SpaceElevatorPayOffSlot_C_GetPaidOffFeedbackImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetProgressbarPercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_SpaceElevatorPayOffSlot_C::GetProgressbarPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetProgressbarPercent");

	UWidget_SpaceElevatorPayOffSlot_C_GetProgressbarPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_SpaceElevatorPayOffSlot_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.OnDrop");

	UWidget_SpaceElevatorPayOffSlot_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetItemQuotaText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SpaceElevatorPayOffSlot_C::GetItemQuotaText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetItemQuotaText");

	UWidget_SpaceElevatorPayOffSlot_C_GetItemQuotaText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetItemText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SpaceElevatorPayOffSlot_C::GetItemText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetItemText");

	UWidget_SpaceElevatorPayOffSlot_C_GetItemText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetItemImage
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_SpaceElevatorPayOffSlot_C::GetItemImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GetItemImage");

	UWidget_SpaceElevatorPayOffSlot_C_GetItemImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.Construct
// ()

void UWidget_SpaceElevatorPayOffSlot_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.Construct");

	UWidget_SpaceElevatorPayOffSlot_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevatorPayOffSlot_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.Tick");

	UWidget_SpaceElevatorPayOffSlot_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GlowTimer
// ()

void UWidget_SpaceElevatorPayOffSlot_C::GlowTimer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.GlowTimer");

	UWidget_SpaceElevatorPayOffSlot_C_GlowTimer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.ExecuteUbergraph_Widget_SpaceElevatorPayOffSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevatorPayOffSlot_C::ExecuteUbergraph_Widget_SpaceElevatorPayOffSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevatorPayOffSlot.Widget_SpaceElevatorPayOffSlot_C.ExecuteUbergraph_Widget_SpaceElevatorPayOffSlot");

	UWidget_SpaceElevatorPayOffSlot_C_ExecuteUbergraph_Widget_SpaceElevatorPayOffSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
