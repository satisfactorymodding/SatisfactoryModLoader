// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Window_DarkMode_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.InitTabs
// ()

void UWidget_Window_DarkMode_C::InitTabs()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.InitTabs");

	UWidget_Window_DarkMode_C_InitTabs_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.SetInventoryVisibility
// ()
// Parameters:
// bool                           mShowInventory                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           Animate                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_DarkMode_C::SetInventoryVisibility(bool mShowInventory, bool Animate)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.SetInventoryVisibility");

	UWidget_Window_DarkMode_C_SetInventoryVisibility_Params params;
	params.mShowInventory = mShowInventory;
	params.Animate = Animate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetDividerButtonSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_DarkMode_C::GetDividerButtonSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetDividerButtonSlotVisibility");

	UWidget_Window_DarkMode_C_GetDividerButtonSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetNavigationVisibiliy
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_DarkMode_C::GetNavigationVisibiliy()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetNavigationVisibiliy");

	UWidget_Window_DarkMode_C_GetNavigationVisibiliy_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetInventoryBodyVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_DarkMode_C::GetInventoryBodyVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetInventoryBodyVisibility");

	UWidget_Window_DarkMode_C_GetInventoryBodyVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetTopButtonSlotVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Window_DarkMode_C::GetTopButtonSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetTopButtonSlotVisibility");

	UWidget_Window_DarkMode_C_GetTopButtonSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_Window_DarkMode_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnDrop");

	UWidget_Window_DarkMode_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.SetTitle
// ()
// Parameters:
// struct FText                   Title                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Window_DarkMode_C::SetTitle(const struct FText& Title)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.SetTitle");

	UWidget_Window_DarkMode_C_SetTitle_Params params;
	params.Title = Title;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Construct
// ()

void UWidget_Window_DarkMode_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Construct");

	UWidget_Window_DarkMode_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnEscapePressed
// ()

void UWidget_Window_DarkMode_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnEscapePressed");

	UWidget_Window_DarkMode_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Destruct
// ()

void UWidget_Window_DarkMode_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Destruct");

	UWidget_Window_DarkMode_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_DarkMode_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Tick");

	UWidget_Window_DarkMode_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnConstructAnimFinished
// ()

void UWidget_Window_DarkMode_C::OnConstructAnimFinished()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnConstructAnimFinished");

	UWidget_Window_DarkMode_C_OnConstructAnimFinished_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_DarkMode_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.PreConstruct");

	UWidget_Window_DarkMode_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnCloseButtonClicked
// ()

void UWidget_Window_DarkMode_C::OnCloseButtonClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnCloseButtonClicked");

	UWidget_Window_DarkMode_C_OnCloseButtonClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.LerpShowInventory
// ()

void UWidget_Window_DarkMode_C::LerpShowInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.LerpShowInventory");

	UWidget_Window_DarkMode_C_LerpShowInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_2_OnButtonClicked__DelegateSignature
// ()
// Parameters:
// int                            ButtonIndex                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_DarkMode_C::BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_2_OnButtonClicked__DelegateSignature(int ButtonIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_2_OnButtonClicked__DelegateSignature");

	UWidget_Window_DarkMode_C_BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_2_OnButtonClicked__DelegateSignature_Params params;
	params.ButtonIndex = ButtonIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_0_OnNoTabsGenerated__DelegateSignature
// ()

void UWidget_Window_DarkMode_C::BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_0_OnNoTabsGenerated__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_0_OnNoTabsGenerated__DelegateSignature");

	UWidget_Window_DarkMode_C_BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_0_OnNoTabsGenerated__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_1_OnTabsGenerated__DelegateSignature
// ()

void UWidget_Window_DarkMode_C::BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_1_OnTabsGenerated__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_1_OnTabsGenerated__DelegateSignature");

	UWidget_Window_DarkMode_C_BndEvt__Widget_TabsContainer_K2Node_ComponentBoundEvent_1_OnTabsGenerated__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.ExecuteUbergraph_Widget_Window_DarkMode
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_DarkMode_C::ExecuteUbergraph_Widget_Window_DarkMode(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.ExecuteUbergraph_Widget_Window_DarkMode");

	UWidget_Window_DarkMode_C_ExecuteUbergraph_Widget_Window_DarkMode_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnTabButtonClicked__DelegateSignature
// ()
// Parameters:
// int                            ButtonIndex                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Window_DarkMode_C::OnTabButtonClicked__DelegateSignature(int ButtonIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnTabButtonClicked__DelegateSignature");

	UWidget_Window_DarkMode_C_OnTabButtonClicked__DelegateSignature_Params params;
	params.ButtonIndex = ButtonIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnClose__DelegateSignature
// ()

void UWidget_Window_DarkMode_C::OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnClose__DelegateSignature");

	UWidget_Window_DarkMode_C_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
