// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PowerCircuitGraph_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.UpdateStats
// ()

void UWidget_PowerCircuitGraph_C::UpdateStats()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.UpdateStats");

	UWidget_PowerCircuitGraph_C_UpdateStats_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.OnMouseMove
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_PowerCircuitGraph_C::OnMouseMove(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.OnMouseMove");

	UWidget_PowerCircuitGraph_C_OnMouseMove_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.SetHoverStyle
// ()
// Parameters:
// class UTextBlock*              TextObject                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UImage*                  BackgroundObject               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           IsHovered                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PowerCircuitGraph_C::SetHoverStyle(class UTextBlock* TextObject, class UImage* BackgroundObject, bool IsHovered)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.SetHoverStyle");

	UWidget_PowerCircuitGraph_C_SetHoverStyle_Params params;
	params.TextObject = TextObject;
	params.BackgroundObject = BackgroundObject;
	params.IsHovered = IsHovered;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCurrentlyUsingText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_PowerCircuitGraph_C::GetCurrentlyUsingText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCurrentlyUsingText");

	UWidget_PowerCircuitGraph_C_GetCurrentlyUsingText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetResetFuseButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_PowerCircuitGraph_C::GetResetFuseButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetResetFuseButtonEnabled");

	UWidget_PowerCircuitGraph_C_GetResetFuseButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCapacityText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_PowerCircuitGraph_C::GetCapacityText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCapacityText");

	UWidget_PowerCircuitGraph_C_GetCapacityText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.UpdatePoints
// ()

void UWidget_PowerCircuitGraph_C::UpdatePoints()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.UpdatePoints");

	UWidget_PowerCircuitGraph_C_UpdatePoints_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCapacityColorAndOpacity
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_PowerCircuitGraph_C::GetCapacityColorAndOpacity()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetCapacityColorAndOpacity");

	UWidget_PowerCircuitGraph_C_GetCapacityColorAndOpacity_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetProductionColorAndOpacity
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_PowerCircuitGraph_C::GetProductionColorAndOpacity()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetProductionColorAndOpacity");

	UWidget_PowerCircuitGraph_C_GetProductionColorAndOpacity_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetConsumptionColorAndOpacity
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_PowerCircuitGraph_C::GetConsumptionColorAndOpacity()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.GetConsumptionColorAndOpacity");

	UWidget_PowerCircuitGraph_C_GetConsumptionColorAndOpacity_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PowerCircuitGraph_C::BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_PowerCircuitGraph_C_BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mProductionButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PowerCircuitGraph_C::BndEvt__mProductionButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mProductionButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_PowerCircuitGraph_C_BndEvt__mProductionButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PowerCircuitGraph_C::BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_PowerCircuitGraph_C_BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PowerCircuitGraph_C::BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature");

	UWidget_PowerCircuitGraph_C_BndEvt__mCapacityButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mProductionButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PowerCircuitGraph_C::BndEvt__mProductionButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mProductionButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature");

	UWidget_PowerCircuitGraph_C_BndEvt__mProductionButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_PowerCircuitGraph_C::BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature");

	UWidget_PowerCircuitGraph_C_BndEvt__mConsumptionButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.Construct
// ()

void UWidget_PowerCircuitGraph_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.Construct");

	UWidget_PowerCircuitGraph_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PowerCircuitGraph_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.Tick");

	UWidget_PowerCircuitGraph_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.ExecuteUbergraph_Widget_PowerCircuitGraph
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PowerCircuitGraph_C::ExecuteUbergraph_Widget_PowerCircuitGraph(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PowerCircuitGraph.Widget_PowerCircuitGraph_C.ExecuteUbergraph_Widget_PowerCircuitGraph");

	UWidget_PowerCircuitGraph_C_ExecuteUbergraph_Widget_PowerCircuitGraph_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
