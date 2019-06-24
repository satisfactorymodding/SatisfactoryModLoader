// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SessionRow_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SessionRow.Widget_SessionRow_C.SetDisabled
// ()

void UWidget_SessionRow_C::SetDisabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.SetDisabled");

	UWidget_SessionRow_C_SetDisabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetPointerVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SessionRow_C::GetPointerVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetPointerVisibility");

	UWidget_SessionRow_C_GetPointerVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionRow.Widget_SessionRow_C.OnButtonClicked
// ()

void UWidget_SessionRow_C::OnButtonClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.OnButtonClicked");

	UWidget_SessionRow_C_OnButtonClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetMostRecentSaveFromSession
// ()

void UWidget_SessionRow_C::GetMostRecentSaveFromSession()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetMostRecentSaveFromSession");

	UWidget_SessionRow_C_GetMostRecentSaveFromSession_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetLastSaveTime
// ()

void UWidget_SessionRow_C::GetLastSaveTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetLastSaveTime");

	UWidget_SessionRow_C_GetLastSaveTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetSessionName
// ()

void UWidget_SessionRow_C::GetSessionName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetSessionName");

	UWidget_SessionRow_C_GetSessionName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetLastSaveName
// ()

void UWidget_SessionRow_C::GetLastSaveName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetLastSaveName");

	UWidget_SessionRow_C_GetLastSaveName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.PopulateSavesFromSession
// ()
// Parameters:
// struct FSessionSaveStruct      session                        (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SessionRow_C::PopulateSavesFromSession(const struct FSessionSaveStruct& session)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.PopulateSavesFromSession");

	UWidget_SessionRow_C_PopulateSavesFromSession_Params params;
	params.session = session;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.OnFocusReceived
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FFocusEvent*            InFocusEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_SessionRow_C::OnFocusReceived(struct FGeometry* MyGeometry, struct FFocusEvent* InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.OnFocusReceived");

	UWidget_SessionRow_C_OnFocusReceived_Params params;
	params.MyGeometry = MyGeometry;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetSaveTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_SessionRow_C::GetSaveTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetSaveTextColor");

	UWidget_SessionRow_C_GetSaveTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetIconColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SessionRow_C::GetIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetIconColor");

	UWidget_SessionRow_C_GetIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionRow.Widget_SessionRow_C.GetButtonHoverColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SessionRow_C::GetButtonHoverColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.GetButtonHoverColor");

	UWidget_SessionRow_C_GetButtonHoverColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mButton_K2Node_ComponentBoundEvent_120_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SessionRow_C::BndEvt__mButton_K2Node_ComponentBoundEvent_120_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mButton_K2Node_ComponentBoundEvent_120_OnButtonClickedEvent__DelegateSignature");

	UWidget_SessionRow_C_BndEvt__mButton_K2Node_ComponentBoundEvent_120_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SessionRow_C::BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature");

	UWidget_SessionRow_C_BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.Construct
// ()

void UWidget_SessionRow_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.Construct");

	UWidget_SessionRow_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SessionRow_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.PreConstruct");

	UWidget_SessionRow_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mLoadButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SessionRow_C::BndEvt__mLoadButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mLoadButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature");

	UWidget_SessionRow_C_BndEvt__mLoadButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mDeleteSessionButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SessionRow_C::BndEvt__mDeleteSessionButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mDeleteSessionButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature");

	UWidget_SessionRow_C_BndEvt__mDeleteSessionButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.ConfirmDeleteSessionPopUp
// ()

void UWidget_SessionRow_C::ConfirmDeleteSessionPopUp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.ConfirmDeleteSessionPopUp");

	UWidget_SessionRow_C_ConfirmDeleteSessionPopUp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.Event DeleteSession
// ()

void UWidget_SessionRow_C::Event_DeleteSession()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.Event DeleteSession");

	UWidget_SessionRow_C_Event_DeleteSession_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SessionRow_C::BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature");

	UWidget_SessionRow_C_BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SessionRow.Widget_SessionRow_C.ExecuteUbergraph_Widget_SessionRow
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SessionRow_C::ExecuteUbergraph_Widget_SessionRow(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SessionRow.Widget_SessionRow_C.ExecuteUbergraph_Widget_SessionRow");

	UWidget_SessionRow_C_ExecuteUbergraph_Widget_SessionRow_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
