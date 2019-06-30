// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_LaunchButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.Test
// ()
// Parameters:
// bool                           NewParam                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_LaunchButton_C::Test(bool* NewParam)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.Test");

	UWidget_TradingPost_LaunchButton_C_Test_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NewParam != nullptr)
		*NewParam = params.NewParam;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.IsTutorialPhase
// ()
// Parameters:
// bool                           IsTutorialPhase                (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_LaunchButton_C::IsTutorialPhase(bool* IsTutorialPhase)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.IsTutorialPhase");

	UWidget_TradingPost_LaunchButton_C_IsTutorialPhase_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsTutorialPhase != nullptr)
		*IsTutorialPhase = params.IsTutorialPhase;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetButtonClickedVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_LaunchButton_C::GetButtonClickedVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetButtonClickedVisibility");

	UWidget_TradingPost_LaunchButton_C_GetButtonClickedVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.IsSchematicPaidOff
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_TradingPost_LaunchButton_C::IsSchematicPaidOff()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.IsSchematicPaidOff");

	UWidget_TradingPost_LaunchButton_C_IsSchematicPaidOff_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetTextFeedback
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_TradingPost_LaunchButton_C::GetTextFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetTextFeedback");

	UWidget_TradingPost_LaunchButton_C_GetTextFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetLaunchButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_LaunchButton_C::GetLaunchButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetLaunchButtonVisibility");

	UWidget_TradingPost_LaunchButton_C_GetLaunchButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetLaunchButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_TradingPost_LaunchButton_C::GetLaunchButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.GetLaunchButtonEnabled");

	UWidget_TradingPost_LaunchButton_C_GetLaunchButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_LaunchButton_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.Tick");

	UWidget_TradingPost_LaunchButton_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_65_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_TradingPost_LaunchButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_65_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_65_OnButtonHoverEvent__DelegateSignature");

	UWidget_TradingPost_LaunchButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_65_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_75_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_TradingPost_LaunchButton_C::BndEvt__mButton_K2Node_ComponentBoundEvent_75_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_75_OnButtonHoverEvent__DelegateSignature");

	UWidget_TradingPost_LaunchButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_75_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_TradingPost_LaunchButton_C::BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature");

	UWidget_TradingPost_LaunchButton_C_BndEvt__Button_26_K2Node_ComponentBoundEvent_100_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.Construct
// ()

void UWidget_TradingPost_LaunchButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.Construct");

	UWidget_TradingPost_LaunchButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.mLaunchShip
// ()
// Parameters:
// bool                           IsTutorialPhase                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_LaunchButton_C::mLaunchShip(bool IsTutorialPhase)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.mLaunchShip");

	UWidget_TradingPost_LaunchButton_C_mLaunchShip_Params params;
	params.IsTutorialPhase = IsTutorialPhase;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.ExecuteUbergraph_Widget_TradingPost_LaunchButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_LaunchButton_C::ExecuteUbergraph_Widget_TradingPost_LaunchButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_LaunchButton.Widget_TradingPost_LaunchButton_C.ExecuteUbergraph_Widget_TradingPost_LaunchButton");

	UWidget_TradingPost_LaunchButton_C_ExecuteUbergraph_Widget_TradingPost_LaunchButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
