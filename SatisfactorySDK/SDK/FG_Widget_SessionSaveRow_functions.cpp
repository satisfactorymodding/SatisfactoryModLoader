// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SessionSaveRow_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.SetSelected
// ()
// Parameters:
// bool                           isSelected                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SessionSaveRow_C::SetSelected(bool isSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.SetSelected");

	UWidget_SessionSaveRow_C_SetSelected_Params params;
	params.isSelected = isSelected;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetIconColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SessionSaveRow_C::GetIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetIconColor");

	UWidget_SessionSaveRow_C_GetIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_SessionSaveRow_C::GetTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetTextColor");

	UWidget_SessionSaveRow_C_GetTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetPlayDurationTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_SessionSaveRow_C::GetPlayDurationTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetPlayDurationTextColor");

	UWidget_SessionSaveRow_C_GetPlayDurationTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetIconBGColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SessionSaveRow_C::GetIconBGColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetIconBGColor");

	UWidget_SessionSaveRow_C_GetIconBGColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetHoverColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SessionSaveRow_C::GetHoverColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetHoverColor");

	UWidget_SessionSaveRow_C_GetHoverColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetPlayDuration
// ()

void UWidget_SessionSaveRow_C::GetPlayDuration()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetPlayDuration");

	UWidget_SessionSaveRow_C_GetPlayDuration_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetSaveTimeText
// ()

void UWidget_SessionSaveRow_C::GetSaveTimeText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetSaveTimeText");

	UWidget_SessionSaveRow_C_GetSaveTimeText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetSaveNameText
// ()

void UWidget_SessionSaveRow_C::GetSaveNameText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetSaveNameText");

	UWidget_SessionSaveRow_C_GetSaveNameText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SessionSaveRow_C::BndEvt__mSaveButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_SessionSaveRow_C_BndEvt__mSaveButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SessionSaveRow_C::BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature");

	UWidget_SessionSaveRow_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.ConfirmDeleteSavePopUp
// ()

void UWidget_SessionSaveRow_C::ConfirmDeleteSavePopUp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.ConfirmDeleteSavePopUp");

	UWidget_SessionSaveRow_C_ConfirmDeleteSavePopUp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SessionSaveRow_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.PreConstruct");

	UWidget_SessionSaveRow_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.Event DeleteSave
// ()
// Parameters:
// bool                           confirm                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SessionSaveRow_C::Event_DeleteSave(bool confirm)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.Event DeleteSave");

	UWidget_SessionSaveRow_C_Event_DeleteSave_Params params;
	params.confirm = confirm;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SessionSaveRow_C::BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_SessionSaveRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SessionSaveRow_C::BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature");

	UWidget_SessionSaveRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SessionSaveRow_C::BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_SessionSaveRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.ExecuteUbergraph_Widget_SessionSaveRow
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SessionSaveRow_C::ExecuteUbergraph_Widget_SessionSaveRow(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.ExecuteUbergraph_Widget_SessionSaveRow");

	UWidget_SessionSaveRow_C_ExecuteUbergraph_Widget_SessionSaveRow_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
