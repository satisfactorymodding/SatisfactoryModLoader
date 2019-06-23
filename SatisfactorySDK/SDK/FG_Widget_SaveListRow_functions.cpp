// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SaveListRow_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SaveListRow.Widget_SaveListRow_C.SetColorForImage
// ()
// Parameters:
// class UImage*                  ImageBG                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SaveListRow_C::SetColorForImage(class UImage* ImageBG, const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.SetColorForImage");

	UWidget_SaveListRow_C_SetColorForImage_Params params;
	params.ImageBG = ImageBG;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetNewSaveGameVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SaveListRow_C::GetNewSaveGameVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetNewSaveGameVisibility");

	UWidget_SaveListRow_C_GetNewSaveGameVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetLoadDeleteVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SaveListRow_C::GetLoadDeleteVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetLoadDeleteVisibility");

	UWidget_SaveListRow_C_GetLoadDeleteVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.OnFocusReceived
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FFocusEvent*            InFocusEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_SaveListRow_C::OnFocusReceived(struct FGeometry* MyGeometry, struct FFocusEvent* InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.OnFocusReceived");

	UWidget_SaveListRow_C_OnFocusReceived_Params params;
	params.MyGeometry = MyGeometry;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveNameTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_SaveListRow_C::GetSaveNameTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveNameTextColor");

	UWidget_SaveListRow_C_GetSaveNameTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_SaveListRow_C::GetTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetTextColor");

	UWidget_SaveListRow_C_GetTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetIconBGColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SaveListRow_C::GetIconBGColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetIconBGColor");

	UWidget_SaveListRow_C_GetIconBGColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetIconColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SaveListRow_C::GetIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetIconColor");

	UWidget_SaveListRow_C_GetIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetButtonColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SaveListRow_C::GetButtonColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetButtonColor");

	UWidget_SaveListRow_C_GetButtonColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetNewSaveVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SaveListRow_C::GetNewSaveVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetNewSaveVisibility");

	UWidget_SaveListRow_C_GetNewSaveVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSessionName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SaveListRow_C::GetSessionName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetSessionName");

	UWidget_SaveListRow_C_GetSessionName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveDuration
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SaveListRow_C::GetSaveDuration()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveDuration");

	UWidget_SaveListRow_C_GetSaveDuration_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetDesiredFileName
// ()
// Parameters:
// class FString                  desiredFileName                (Parm, OutParm, ZeroConstructor)

void UWidget_SaveListRow_C::GetDesiredFileName(class FString* desiredFileName)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetDesiredFileName");

	UWidget_SaveListRow_C_GetDesiredFileName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (desiredFileName != nullptr)
		*desiredFileName = params.desiredFileName;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.Clicked
// ()

void UWidget_SaveListRow_C::Clicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.Clicked");

	UWidget_SaveListRow_C_Clicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveMap
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SaveListRow_C::GetSaveMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveMap");

	UWidget_SaveListRow_C_GetSaveMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveVersion
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SaveListRow_C::GetSaveVersion()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.GetSaveVersion");

	UWidget_SaveListRow_C_GetSaveVersion_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SaveListRow_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_SaveListRow_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SaveListRow_C::BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature");

	UWidget_SaveListRow_C_BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SaveListRow_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature");

	UWidget_SaveListRow_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.OnWorldSave
// ()
// Parameters:
// bool                           wasSuccessful                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   errorMessage                   (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SaveListRow_C::OnWorldSave(bool wasSuccessful, const struct FText& errorMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.OnWorldSave");

	UWidget_SaveListRow_C_OnWorldSave_Params params;
	params.wasSuccessful = wasSuccessful;
	params.errorMessage = errorMessage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.ConfirmDeleteSessionPopUp
// ()

void UWidget_SaveListRow_C::ConfirmDeleteSessionPopUp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.ConfirmDeleteSessionPopUp");

	UWidget_SaveListRow_C_ConfirmDeleteSessionPopUp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SaveListRow_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_SaveListRow_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.DeleteSave
// ()

void UWidget_SaveListRow_C::DeleteSave()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.DeleteSave");

	UWidget_SaveListRow_C_DeleteSave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SaveListRow_C::BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature");

	UWidget_SaveListRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.Construct
// ()

void UWidget_SaveListRow_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.Construct");

	UWidget_SaveListRow_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.ExecuteUbergraph_Widget_SaveListRow
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SaveListRow_C::ExecuteUbergraph_Widget_SaveListRow(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.ExecuteUbergraph_Widget_SaveListRow");

	UWidget_SaveListRow_C_ExecuteUbergraph_Widget_SaveListRow_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveListRow.Widget_SaveListRow_C.OnClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_SaveListRow_C*   clickedRow                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SaveListRow_C::OnClicked__DelegateSignature(class UWidget_SaveListRow_C* clickedRow)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveListRow.Widget_SaveListRow_C.OnClicked__DelegateSignature");

	UWidget_SaveListRow_C_OnClicked__DelegateSignature_Params params;
	params.clickedRow = clickedRow;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
