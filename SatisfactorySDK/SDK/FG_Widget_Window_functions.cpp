// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Window_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Window.Widget_Window_C.GetDividerButtonSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_C::GetDividerButtonSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.GetDividerButtonSlotVisibility");

	UWidget_Window_C_GetDividerButtonSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window.Widget_Window_C.GetNavigationVisibiliy
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_C::GetNavigationVisibiliy()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.GetNavigationVisibiliy");

	UWidget_Window_C_GetNavigationVisibiliy_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window.Widget_Window_C.GetCloseButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_C::GetCloseButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.GetCloseButtonVisibility");

	UWidget_Window_C_GetCloseButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window.Widget_Window_C.GetInventoryBodyVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_C::GetInventoryBodyVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.GetInventoryBodyVisibility");

	UWidget_Window_C_GetInventoryBodyVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window.Widget_Window_C.GetTopButtonSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_C::GetTopButtonSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.GetTopButtonSlotVisibility");

	UWidget_Window_C_GetTopButtonSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window.Widget_Window_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_Window_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.OnDrop");

	UWidget_Window_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window.Widget_Window_C.SetTitle
// ()
// Parameters:
// struct FText                   Title                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Window_C::SetTitle(const struct FText& Title)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.SetTitle");

	UWidget_Window_C_SetTitle_Params params;
	params.Title = Title;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.Construct
// ()

void UWidget_Window_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.Construct");

	UWidget_Window_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.OnEscapePressed
// ()

void UWidget_Window_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.OnEscapePressed");

	UWidget_Window_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.Destruct
// ()

void UWidget_Window_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.Destruct");

	UWidget_Window_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.BndEvt__mCloseButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_Window_C::BndEvt__mCloseButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.BndEvt__mCloseButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_Window_C_BndEvt__mCloseButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.Tick");

	UWidget_Window_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.OnConstructAnimFinished
// ()

void UWidget_Window_C::OnConstructAnimFinished()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.OnConstructAnimFinished");

	UWidget_Window_C_OnConstructAnimFinished_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.ExecuteUbergraph_Widget_Window
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_C::ExecuteUbergraph_Widget_Window(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.ExecuteUbergraph_Widget_Window");

	UWidget_Window_C_ExecuteUbergraph_Widget_Window_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window.Widget_Window_C.OnClose__DelegateSignature
// ()

void UWidget_Window_C::OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window.Widget_Window_C.OnClose__DelegateSignature");

	UWidget_Window_C_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
