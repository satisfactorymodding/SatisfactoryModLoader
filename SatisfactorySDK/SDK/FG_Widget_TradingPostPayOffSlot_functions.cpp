// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPostPayOffSlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.StopEmptyAnim
// ()

void UWidget_TradingPostPayOffSlot_C::StopEmptyAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.StopEmptyAnim");

	UWidget_TradingPostPayOffSlot_C_StopEmptyAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.DropOntoInventorySlot
// ()
// Parameters:
// class UWidget_InventorySlot_C* InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPostPayOffSlot_C::DropOntoInventorySlot(class UWidget_InventorySlot_C* InventorySlot, bool* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.DropOntoInventorySlot");

	UWidget_TradingPostPayOffSlot_C_DropOntoInventorySlot_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetSlotBackgroundBrush
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_TradingPostPayOffSlot_C::GetSlotBackgroundBrush()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetSlotBackgroundBrush");

	UWidget_TradingPostPayOffSlot_C_GetSlotBackgroundBrush_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetDarkGrayColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_TradingPostPayOffSlot_C::GetDarkGrayColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetDarkGrayColor");

	UWidget_TradingPostPayOffSlot_C_GetDarkGrayColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetProgressbarPercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_TradingPostPayOffSlot_C::GetProgressbarPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetProgressbarPercent");

	UWidget_TradingPostPayOffSlot_C_GetProgressbarPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.SetTextboxFormating
// ()

void UWidget_TradingPostPayOffSlot_C::SetTextboxFormating()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.SetTextboxFormating");

	UWidget_TradingPostPayOffSlot_C_SetTextboxFormating_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetCustomTooltip
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_TradingPostPayOffSlot_C::GetCustomTooltip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetCustomTooltip");

	UWidget_TradingPostPayOffSlot_C_GetCustomTooltip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPostPayOffSlot_C::GetPaidOffSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffSlotVisibility");

	UWidget_TradingPostPayOffSlot_C_GetPaidOffSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetProgressbarVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPostPayOffSlot_C::GetProgressbarVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetProgressbarVisibility");

	UWidget_TradingPostPayOffSlot_C_GetProgressbarVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffColorFeedback
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_TradingPostPayOffSlot_C::GetPaidOffColorFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffColorFeedback");

	UWidget_TradingPostPayOffSlot_C_GetPaidOffColorFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffFeedbackImage
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPostPayOffSlot_C::GetPaidOffFeedbackImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffFeedbackImage");

	UWidget_TradingPostPayOffSlot_C_GetPaidOffFeedbackImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_TradingPostPayOffSlot_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnDrop");

	UWidget_TradingPostPayOffSlot_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemQuotaText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_TradingPostPayOffSlot_C::GetItemQuotaText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemQuotaText");

	UWidget_TradingPostPayOffSlot_C_GetItemQuotaText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_TradingPostPayOffSlot_C::GetItemText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemText");

	UWidget_TradingPostPayOffSlot_C_GetItemText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemImage
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_TradingPostPayOffSlot_C::GetItemImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemImage");

	UWidget_TradingPostPayOffSlot_C_GetItemImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Construct
// ()

void UWidget_TradingPostPayOffSlot_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Construct");

	UWidget_TradingPostPayOffSlot_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnSchematicPaidOff
// ()
// Parameters:
// class AFGSchematicManager*     schematicManager               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPostPayOffSlot_C::OnSchematicPaidOff(class AFGSchematicManager* schematicManager)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnSchematicPaidOff");

	UWidget_TradingPostPayOffSlot_C_OnSchematicPaidOff_Params params;
	params.schematicManager = schematicManager;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Destruct
// ()

void UWidget_TradingPostPayOffSlot_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Destruct");

	UWidget_TradingPostPayOffSlot_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPostPayOffSlot_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Tick");

	UWidget_TradingPostPayOffSlot_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnMouseEnter
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_TradingPostPayOffSlot_C::OnMouseEnter(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnMouseEnter");

	UWidget_TradingPostPayOffSlot_C_OnMouseEnter_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.ExecuteUbergraph_Widget_TradingPostPayOffSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPostPayOffSlot_C::ExecuteUbergraph_Widget_TradingPostPayOffSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.ExecuteUbergraph_Widget_TradingPostPayOffSlot");

	UWidget_TradingPostPayOffSlot_C_ExecuteUbergraph_Widget_TradingPostPayOffSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
