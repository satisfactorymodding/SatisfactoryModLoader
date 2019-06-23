// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ResourceExtractorUI_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ResourceExtractorUI_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.DropInventorySlotStack");

	UWidget_ResourceExtractorUI_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.GetWarningVisibility
// ()
// Parameters:
// class AFGBuildableResourceExtractor* buildableResourceExtractor     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ResourceExtractorUI_C::GetWarningVisibility(class AFGBuildableResourceExtractor* buildableResourceExtractor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.GetWarningVisibility");

	UWidget_ResourceExtractorUI_C_GetWarningVisibility_Params params;
	params.buildableResourceExtractor = buildableResourceExtractor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateOutputInfo
// ()

void UWidget_ResourceExtractorUI_C::UpdateOutputInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateOutputInfo");

	UWidget_ResourceExtractorUI_C_UpdateOutputInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateExtractorStats
// ()

void UWidget_ResourceExtractorUI_C::UpdateExtractorStats()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateExtractorStats");

	UWidget_ResourceExtractorUI_C_UpdateExtractorStats_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateExtractorProgress
// ()

void UWidget_ResourceExtractorUI_C::UpdateExtractorProgress()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateExtractorProgress");

	UWidget_ResourceExtractorUI_C_UpdateExtractorProgress_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.GetOverclockWidgetVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ResourceExtractorUI_C::GetOverclockWidgetVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.GetOverclockWidgetVisibility");

	UWidget_ResourceExtractorUI_C_GetOverclockWidgetVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Construct
// ()

void UWidget_ResourceExtractorUI_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Construct");

	UWidget_ResourceExtractorUI_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ResourceExtractorUI_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Tick");

	UWidget_ResourceExtractorUI_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_0_OnStandbyClicked__DelegateSignature
// ()

void UWidget_ResourceExtractorUI_C::BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_0_OnStandbyClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_0_OnStandbyClicked__DelegateSignature");

	UWidget_ResourceExtractorUI_C_BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_0_OnStandbyClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Init
// ()

void UWidget_ResourceExtractorUI_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Init");

	UWidget_ResourceExtractorUI_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature
// ()

void UWidget_ResourceExtractorUI_C::BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature");

	UWidget_ResourceExtractorUI_C_BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.ExecuteUbergraph_Widget_ResourceExtractorUI
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ResourceExtractorUI_C::ExecuteUbergraph_Widget_ResourceExtractorUI(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.ExecuteUbergraph_Widget_ResourceExtractorUI");

	UWidget_ResourceExtractorUI_C_ExecuteUbergraph_Widget_ResourceExtractorUI_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
