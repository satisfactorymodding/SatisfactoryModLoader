// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Train_TimeTable_Rule_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetIsNextStop
// ()
// Parameters:
// bool                           mIsNextStop                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::SetIsNextStop(bool mIsNextStop)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetIsNextStop");

	UWidget_Train_TimeTable_Rule_C_SetIsNextStop_Params params;
	params.mIsNextStop = mIsNextStop;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnUnhovered
// ()

void UWidget_Train_TimeTable_Rule_C::OnUnhovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnUnhovered");

	UWidget_Train_TimeTable_Rule_C_OnUnhovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnHovered
// ()

void UWidget_Train_TimeTable_Rule_C::OnHovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnHovered");

	UWidget_Train_TimeTable_Rule_C_OnHovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.PlayNewNameAnim
// ()

void UWidget_Train_TimeTable_Rule_C::PlayNewNameAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.PlayNewNameAnim");

	UWidget_Train_TimeTable_Rule_C_PlayNewNameAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetOrderButtonsVisibility
// ()
// Parameters:
// bool                           UpVisible                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           DownVisible                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::SetOrderButtonsVisibility(bool UpVisible, bool DownVisible)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetOrderButtonsVisibility");

	UWidget_Train_TimeTable_Rule_C_SetOrderButtonsVisibility_Params params;
	params.UpVisible = UpVisible;
	params.DownVisible = DownVisible;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.UpdateRule
// ()
// Parameters:
// class AFGTrainStationIdentifier* mStation                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::UpdateRule(class AFGTrainStationIdentifier* mStation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.UpdateRule");

	UWidget_Train_TimeTable_Rule_C_UpdateRule_Params params;
	params.mStation = mStation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetIsSelected
// ()
// Parameters:
// bool                           mIsSelected                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::SetIsSelected(bool mIsSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetIsSelected");

	UWidget_Train_TimeTable_Rule_C_SetIsSelected_Params params;
	params.mIsSelected = mIsSelected;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetTitle
// ()
// Parameters:
// struct FText                   mTitle                         (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Train_TimeTable_Rule_C::SetTitle(const struct FText& mTitle)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.SetTitle");

	UWidget_Train_TimeTable_Rule_C_SetTitle_Params params;
	params.mTitle = mTitle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.PreConstruct");

	UWidget_Train_TimeTable_Rule_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.Construct
// ()

void UWidget_Train_TimeTable_Rule_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.Construct");

	UWidget_Train_TimeTable_Rule_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveUp_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mMoveUp_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveUp_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mMoveUp_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveDown_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mMoveDown_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveDown_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mMoveDown_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveUp_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mMoveUp_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveUp_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mMoveUp_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveDown_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mMoveDown_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveDown_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mMoveDown_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mButton_K2Node_ComponentBoundEvent_9_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mButton_K2Node_ComponentBoundEvent_9_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mButton_K2Node_ComponentBoundEvent_9_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mButton_K2Node_ComponentBoundEvent_9_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_10_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_10_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_10_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_10_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveUp_K2Node_ComponentBoundEvent_11_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mMoveUp_K2Node_ComponentBoundEvent_11_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveUp_K2Node_ComponentBoundEvent_11_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mMoveUp_K2Node_ComponentBoundEvent_11_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveDown_K2Node_ComponentBoundEvent_12_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mMoveDown_K2Node_ComponentBoundEvent_12_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mMoveDown_K2Node_ComponentBoundEvent_12_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mMoveDown_K2Node_ComponentBoundEvent_12_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_13_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_13_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_13_OnButtonHoverEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_13_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Train_TimeTable_Rule_C::BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_BndEvt__mSetCurrentStopButton_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.ExecuteUbergraph_Widget_Train_TimeTable_Rule
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::ExecuteUbergraph_Widget_Train_TimeTable_Rule(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.ExecuteUbergraph_Widget_Train_TimeTable_Rule");

	UWidget_Train_TimeTable_Rule_C_ExecuteUbergraph_Widget_Train_TimeTable_Rule_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnSetCurrentStopClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::OnSetCurrentStopClicked__DelegateSignature(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnSetCurrentStopClicked__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_OnSetCurrentStopClicked__DelegateSignature_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnMoveDownClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::OnMoveDownClicked__DelegateSignature(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnMoveDownClicked__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_OnMoveDownClicked__DelegateSignature_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnMoveUpClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::OnMoveUpClicked__DelegateSignature(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnMoveUpClicked__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_OnMoveUpClicked__DelegateSignature_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnDeleted__DelegateSignature
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::OnDeleted__DelegateSignature(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnDeleted__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_OnDeleted__DelegateSignature_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_Rule_C::OnClicked__DelegateSignature(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable_Rule.Widget_Train_TimeTable_Rule_C.OnClicked__DelegateSignature");

	UWidget_Train_TimeTable_Rule_C_OnClicked__DelegateSignature_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
