// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_TierButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.SetLockedText
// ()

void UWidget_TradingPost_TierButton_C::SetLockedText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.SetLockedText");

	UWidget_TradingPost_TierButton_C_SetLockedText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetTierNumVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_TierButton_C::GetTierNumVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetTierNumVisibility");

	UWidget_TradingPost_TierButton_C_GetTierNumVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetCheckVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_TierButton_C::GetCheckVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetCheckVisibility");

	UWidget_TradingPost_TierButton_C_GetCheckVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.IsSelectable
// ()
// Parameters:
// bool                           IsSelectable                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_TierButton_C::IsSelectable(bool* IsSelectable)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.IsSelectable");

	UWidget_TradingPost_TierButton_C_IsSelectable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsSelectable != nullptr)
		*IsSelectable = params.IsSelectable;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetWidgetClickable
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_TierButton_C::GetWidgetClickable()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetWidgetClickable");

	UWidget_TradingPost_TierButton_C_GetWidgetClickable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetTextHoverColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_TradingPost_TierButton_C::GetTextHoverColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetTextHoverColor");

	UWidget_TradingPost_TierButton_C_GetTextHoverColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetButtonColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_TradingPost_TierButton_C::GetButtonColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.GetButtonColor");

	UWidget_TradingPost_TierButton_C_GetButtonColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.UpdateTier
// ()

void UWidget_TradingPost_TierButton_C::UpdateTier()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.UpdateTier");

	UWidget_TradingPost_TierButton_C_UpdateTier_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.SetTierNumber
// ()
// Parameters:
// int                            TierNumber                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_TradingPost_C*   Tradingpost                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_TradingPost_TierButton_C::SetTierNumber(int TierNumber, class UWidget_TradingPost_C* Tradingpost)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.SetTierNumber");

	UWidget_TradingPost_TierButton_C_SetTierNumber_Params params;
	params.TierNumber = TierNumber;
	params.Tradingpost = Tradingpost;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.BndEvt__Button_2_K2Node_ComponentBoundEvent_70_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_TradingPost_TierButton_C::BndEvt__Button_2_K2Node_ComponentBoundEvent_70_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.BndEvt__Button_2_K2Node_ComponentBoundEvent_70_OnButtonClickedEvent__DelegateSignature");

	UWidget_TradingPost_TierButton_C_BndEvt__Button_2_K2Node_ComponentBoundEvent_70_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.ExecuteUbergraph_Widget_TradingPost_TierButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_TierButton_C::ExecuteUbergraph_Widget_TradingPost_TierButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_TierButton.Widget_TradingPost_TierButton_C.ExecuteUbergraph_Widget_TradingPost_TierButton");

	UWidget_TradingPost_TierButton_C_ExecuteUbergraph_Widget_TradingPost_TierButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
