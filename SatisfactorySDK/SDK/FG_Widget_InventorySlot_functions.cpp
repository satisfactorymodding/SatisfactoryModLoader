// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventorySlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_InventorySlot.Widget_InventorySlot_C.CheckForNuclearWaste
// ()
// Parameters:
// class UClass*                  Object                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::CheckForNuclearWaste(class UClass* Object)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.CheckForNuclearWaste");

	UWidget_InventorySlot_C_CheckForNuclearWaste_Params params;
	params.Object = Object;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.QuickMoveInventory
// ()

void UWidget_InventorySlot_C::QuickMoveInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.QuickMoveInventory");

	UWidget_InventorySlot_C_QuickMoveInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.SetSlotSize
// ()
// Parameters:
// bool                           SmallSlot                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           BigSlot                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::SetSlotSize(bool SmallSlot, bool BigSlot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.SetSlotSize");

	UWidget_InventorySlot_C_SetSlotSize_Params params;
	params.SmallSlot = SmallSlot;
	params.BigSlot = BigSlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.DropOntoInventorySlot
// ()
// Parameters:
// class UWidget_InventorySlot_C* OtherInventorySlot             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::DropOntoInventorySlot(class UWidget_InventorySlot_C* OtherInventorySlot, bool* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.DropOntoInventorySlot");

	UWidget_InventorySlot_C_DropOntoInventorySlot_Params params;
	params.OtherInventorySlot = OtherInventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseButtonUp
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_InventorySlot_C::OnMouseButtonUp(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseButtonUp");

	UWidget_InventorySlot_C_OnMouseButtonUp_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.ResetHoverEffect
// ()

void UWidget_InventorySlot_C::ResetHoverEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.ResetHoverEffect");

	UWidget_InventorySlot_C_ResetHoverEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetOrangeColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_InventorySlot_C::GetOrangeColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetOrangeColor");

	UWidget_InventorySlot_C_GetOrangeColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotBorderColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_InventorySlot_C::GetSlotBorderColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotBorderColor");

	UWidget_InventorySlot_C_GetSlotBorderColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackSizeBGColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_InventorySlot_C::GetStackSizeBGColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackSizeBGColor");

	UWidget_InventorySlot_C_GetStackSizeBGColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnKeyUp
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_InventorySlot_C::OnKeyUp(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnKeyUp");

	UWidget_InventorySlot_C_OnKeyUp_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_InventorySlot_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnKeyDown");

	UWidget_InventorySlot_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotStateColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_InventorySlot_C::GetSlotStateColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotStateColor");

	UWidget_InventorySlot_C_GetSlotStateColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetBorderVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_InventorySlot_C::GetBorderVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetBorderVisibility");

	UWidget_InventorySlot_C_GetBorderVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.CheckSlotHasItems
// ()
// Parameters:
// bool                           slotHasItems                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::CheckSlotHasItems(bool* slotHasItems)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.CheckSlotHasItems");

	UWidget_InventorySlot_C_CheckSlotHasItems_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (slotHasItems != nullptr)
		*slotHasItems = params.slotHasItems;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_InventorySlot_C::GetSlotColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotColor");

	UWidget_InventorySlot_C_GetSlotColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetNumItems
// ()
// Parameters:
// int                            Num                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::GetNumItems(int* Num)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetNumItems");

	UWidget_InventorySlot_C_GetNumItems_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Num != nullptr)
		*Num = params.Num;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemClass
// ()
// Parameters:
// class UClass*                  ItemClass                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::GetItemClass(class UClass** ItemClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemClass");

	UWidget_InventorySlot_C_GetItemClass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ItemClass != nullptr)
		*ItemClass = params.ItemClass;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStack
// ()
// Parameters:
// struct FInventoryStack         stack                          (Parm, OutParm)

void UWidget_InventorySlot_C::GetStack(struct FInventoryStack* stack)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetStack");

	UWidget_InventorySlot_C_GetStack_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (stack != nullptr)
		*stack = params.stack;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseDoubleClick
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_InventorySlot_C::OnMouseDoubleClick(const struct FGeometry& MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseDoubleClick");

	UWidget_InventorySlot_C_OnMouseDoubleClick_Params params;
	params.MyGeometry = MyGeometry;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (MouseEvent != nullptr)
		*MouseEvent = params.MouseEvent;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetTooltipWidget
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_InventorySlot_C::GetTooltipWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetTooltipWidget");

	UWidget_InventorySlot_C_GetTooltipWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetNumLabelVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_InventorySlot_C::GetNumLabelVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetNumLabelVisibility");

	UWidget_InventorySlot_C_GetNumLabelVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetFilterImageVisibility
// ()
// Parameters:
// bool                           Visible                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::GetFilterImageVisibility(bool* Visible)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetFilterImageVisibility");

	UWidget_InventorySlot_C_GetFilterImageVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Visible != nullptr)
		*Visible = params.Visible;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.CreateSplitSlider
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_InventorySlot_C::CreateSplitSlider()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.CreateSplitSlider");

	UWidget_InventorySlot_C_CreateSplitSlider_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackNumber
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_InventorySlot_C::GetStackNumber()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackNumber");

	UWidget_InventorySlot_C_GetStackNumber_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnFocusReceived
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FFocusEvent*            InFocusEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_InventorySlot_C::OnFocusReceived(struct FGeometry* MyGeometry, struct FFocusEvent* InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnFocusReceived");

	UWidget_InventorySlot_C_OnFocusReceived_Params params;
	params.MyGeometry = MyGeometry;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetGamepadButtonIsEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_InventorySlot_C::GetGamepadButtonIsEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetGamepadButtonIsEnabled");

	UWidget_InventorySlot_C_GetGamepadButtonIsEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetFilterImage
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_InventorySlot_C::GetFilterImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetFilterImage");

	UWidget_InventorySlot_C_GetFilterImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.PlaySomeSound
// ()

void UWidget_InventorySlot_C::PlaySomeSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.PlaySomeSound");

	UWidget_InventorySlot_C_PlaySomeSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemImageBrush
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_InventorySlot_C::GetItemImageBrush()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemImageBrush");

	UWidget_InventorySlot_C_GetItemImageBrush_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_InventorySlot_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnDrop");

	UWidget_InventorySlot_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseButtonDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_InventorySlot_C::OnMouseButtonDown(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseButtonDown");

	UWidget_InventorySlot_C_OnMouseButtonDown_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragDetected
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// class UDragDropOperation*      Operation                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::OnDragDetected(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragDetected");

	UWidget_InventorySlot_C_OnDragDetected_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Operation != nullptr)
		*Operation = params.Operation;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackSizeText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_InventorySlot_C::GetStackSizeText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackSizeText");

	UWidget_InventorySlot_C_GetStackSizeText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_InventorySlot_C::GetItemVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemVisibility");

	UWidget_InventorySlot_C_GetItemVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.CacheSlotData
// ()

void UWidget_InventorySlot_C::CacheSlotData()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.CacheSlotData");

	UWidget_InventorySlot_C_CacheSlotData_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseLeave
// ()
// Parameters:
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_InventorySlot_C::OnMouseLeave(struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseLeave");

	UWidget_InventorySlot_C_OnMouseLeave_Params params;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragLeave
// ()
// Parameters:
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::OnDragLeave(struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragLeave");

	UWidget_InventorySlot_C_OnDragLeave_Params params;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragEnter
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::OnDragEnter(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragEnter");

	UWidget_InventorySlot_C_OnDragEnter_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnFocusLost
// ()
// Parameters:
// struct FFocusEvent*            InFocusEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_InventorySlot_C::OnFocusLost(struct FFocusEvent* InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnFocusLost");

	UWidget_InventorySlot_C_OnFocusLost_Params params;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.Tick");

	UWidget_InventorySlot_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.SubscribeToParentWindow
// ()
// Parameters:
// class UWidget_Window_C*        ParentWindow                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_InventorySlot_C::SubscribeToParentWindow(class UWidget_Window_C* ParentWindow)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.SubscribeToParentWindow");

	UWidget_InventorySlot_C_SubscribeToParentWindow_Params params;
	params.ParentWindow = ParentWindow;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.PreConstruct");

	UWidget_InventorySlot_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.UpdateStyle
// ()

void UWidget_InventorySlot_C::UpdateStyle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.UpdateStyle");

	UWidget_InventorySlot_C_UpdateStyle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.Destruct
// ()

void UWidget_InventorySlot_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.Destruct");

	UWidget_InventorySlot_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.Construct
// ()

void UWidget_InventorySlot_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.Construct");

	UWidget_InventorySlot_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.Event CreateNuclearWastePopup
// ()
// Parameters:
// bool                           isNuclearWaste                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::Event_CreateNuclearWastePopup(bool isNuclearWaste)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.Event CreateNuclearWastePopup");

	UWidget_InventorySlot_C_Event_CreateNuclearWastePopup_Params params;
	params.isNuclearWaste = isNuclearWaste;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.CloseNuclearWastePopup
// ()
// Parameters:
// bool                           ConfirmClicked                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::CloseNuclearWastePopup(bool ConfirmClicked)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.CloseNuclearWastePopup");

	UWidget_InventorySlot_C_CloseNuclearWastePopup_Params params;
	params.ConfirmClicked = ConfirmClicked;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseEnter
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_InventorySlot_C::OnMouseEnter(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseEnter");

	UWidget_InventorySlot_C_OnMouseEnter_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.ExecuteUbergraph_Widget_InventorySlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InventorySlot_C::ExecuteUbergraph_Widget_InventorySlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.ExecuteUbergraph_Widget_InventorySlot");

	UWidget_InventorySlot_C_ExecuteUbergraph_Widget_InventorySlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMoveStack__DelegateSignature
// ()
// Parameters:
// class UWidget_InventorySlot_C* Sender                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_InventorySlot_C::OnMoveStack__DelegateSignature(class UWidget_InventorySlot_C* Sender)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnMoveStack__DelegateSignature");

	UWidget_InventorySlot_C_OnMoveStack__DelegateSignature_Params params;
	params.Sender = Sender;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InventorySlot.Widget_InventorySlot_C.OnSlotHovered__DelegateSignature
// ()
// Parameters:
// class UWidget_InventorySlot_C* SelfInventorySlot              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_InventorySlot_C::OnSlotHovered__DelegateSignature(class UWidget_InventorySlot_C* SelfInventorySlot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InventorySlot.Widget_InventorySlot_C.OnSlotHovered__DelegateSignature");

	UWidget_InventorySlot_C_OnSlotHovered__DelegateSignature_Params params;
	params.SelfInventorySlot = SelfInventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
