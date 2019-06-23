// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_StackSplitSlider_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.OnPaint
// ()
// Parameters:
// struct FPaintContext           Context                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_StackSplitSlider_C::OnPaint(struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.OnPaint");

	UWidget_StackSplitSlider_C_OnPaint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.UpdateSliderValue
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)

void UWidget_StackSplitSlider_C::UpdateSliderValue(const struct FGeometry& MyGeometry)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.UpdateSliderValue");

	UWidget_StackSplitSlider_C_UpdateSliderValue_Params params;
	params.MyGeometry = MyGeometry;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetProgressBarPercentage
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_StackSplitSlider_C::GetProgressBarPercentage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetProgressBarPercentage");

	UWidget_StackSplitSlider_C_GetProgressBarPercentage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumInNewStackText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_StackSplitSlider_C::GetNumInNewStackText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumInNewStackText");

	UWidget_StackSplitSlider_C_GetNumInNewStackText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumLeftAtSlot
// ()
// Parameters:
// int                            NumLeft                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_StackSplitSlider_C::GetNumLeftAtSlot(int* NumLeft)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumLeftAtSlot");

	UWidget_StackSplitSlider_C_GetNumLeftAtSlot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NumLeft != nullptr)
		*NumLeft = params.NumLeft;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumLeftAtSlotText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_StackSplitSlider_C::GetNumLeftAtSlotText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.GetNumLeftAtSlotText");

	UWidget_StackSplitSlider_C_GetNumLeftAtSlotText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.SplitResource
// ()

void UWidget_StackSplitSlider_C::SplitResource()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.SplitResource");

	UWidget_StackSplitSlider_C_SplitResource_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.OnMouseButtonUp
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_StackSplitSlider_C::OnMouseButtonUp(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.OnMouseButtonUp");

	UWidget_StackSplitSlider_C_OnMouseButtonUp_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.Construct
// ()

void UWidget_StackSplitSlider_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.Construct");

	UWidget_StackSplitSlider_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_StackSplitSlider_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.Tick");

	UWidget_StackSplitSlider_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.ExecuteUbergraph_Widget_StackSplitSlider
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_StackSplitSlider_C::ExecuteUbergraph_Widget_StackSplitSlider(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_StackSplitSlider.Widget_StackSplitSlider_C.ExecuteUbergraph_Widget_StackSplitSlider");

	UWidget_StackSplitSlider_C_ExecuteUbergraph_Widget_StackSplitSlider_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
