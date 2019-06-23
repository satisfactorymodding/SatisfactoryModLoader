// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FrontEnd_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_FrontEnd.BP_FrontEnd_C.CreatePopupWidget
// ()
// Parameters:
// struct FPopupData*             PopupData                      (BlueprintVisible, BlueprintReadOnly, Parm)
// class UFGPopupWidget*          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UFGPopupWidget* UBP_FrontEnd_C::CreatePopupWidget(struct FPopupData* PopupData)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.CreatePopupWidget");

	UBP_FrontEnd_C_CreatePopupWidget_Params params;
	params.PopupData = PopupData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShutdown
// ()
// Parameters:
// bool                           Shutdown                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::ShouldShutdown(bool* Shutdown)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ShouldShutdown");

	UBP_FrontEnd_C_ShouldShutdown_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Shutdown != nullptr)
		*Shutdown = params.Shutdown;
}


// Function BP_FrontEnd.BP_FrontEnd_C.GetErrorButtonText
// ()
// Parameters:
// struct FText                   ButtonText                     (Parm, OutParm)

void UBP_FrontEnd_C::GetErrorButtonText(struct FText* ButtonText)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.GetErrorButtonText");

	UBP_FrontEnd_C_GetErrorButtonText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ButtonText != nullptr)
		*ButtonText = params.ButtonText;
}


// Function BP_FrontEnd.BP_FrontEnd_C.HasMoreErrors
// ()
// Parameters:
// bool                           moreErrors                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::HasMoreErrors(bool* moreErrors)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.HasMoreErrors");

	UBP_FrontEnd_C_HasMoreErrors_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (moreErrors != nullptr)
		*moreErrors = params.moreErrors;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShutdownAfterThisError
// ()
// Parameters:
// bool                           Shutdown                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::ShouldShutdownAfterThisError(bool* Shutdown)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ShouldShutdownAfterThisError");

	UBP_FrontEnd_C_ShouldShutdownAfterThisError_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Shutdown != nullptr)
		*Shutdown = params.Shutdown;
}


// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowLogin
// ()
// Parameters:
// bool                           ShouldShow                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::Internal_ShouldShowLogin(bool* ShouldShow)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowLogin");

	UBP_FrontEnd_C_Internal_ShouldShowLogin_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ShouldShow != nullptr)
		*ShouldShow = params.ShouldShow;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowLogin
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_FrontEnd_C::ShouldShowLogin()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowLogin");

	UBP_FrontEnd_C_ShouldShowLogin_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_FrontEnd.BP_FrontEnd_C.SetNextErrorMessage
// ()
// Parameters:
// class UFGErrorMessage*         newError                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::SetNextErrorMessage(class UFGErrorMessage* newError)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.SetNextErrorMessage");

	UBP_FrontEnd_C_SetNextErrorMessage_Params params;
	params.newError = newError;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.GetNextErrorMessage
// ()
// Parameters:
// class UFGErrorMessage*         errorMessage                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::GetNextErrorMessage(class UFGErrorMessage** errorMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.GetNextErrorMessage");

	UBP_FrontEnd_C_GetNextErrorMessage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (errorMessage != nullptr)
		*errorMessage = params.errorMessage;
}


// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShowErrorMessage
// ()
// Parameters:
// bool                           ShouldShow                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::Internal_ShowErrorMessage(bool* ShouldShow)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShowErrorMessage");

	UBP_FrontEnd_C_Internal_ShowErrorMessage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ShouldShow != nullptr)
		*ShouldShow = params.ShouldShow;
}


// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowMainMenu
// ()
// Parameters:
// bool                           ShouldShow                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::Internal_ShouldShowMainMenu(bool* ShouldShow)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowMainMenu");

	UBP_FrontEnd_C_Internal_ShouldShowMainMenu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ShouldShow != nullptr)
		*ShouldShow = params.ShouldShow;
}


// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowAlphaInfo
// ()
// Parameters:
// bool                           ShouldShow                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::Internal_ShouldShowAlphaInfo(bool* ShouldShow)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowAlphaInfo");

	UBP_FrontEnd_C_Internal_ShouldShowAlphaInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ShouldShow != nullptr)
		*ShouldShow = params.ShouldShow;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowErrorPopup
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_FrontEnd_C::ShouldShowErrorPopup()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowErrorPopup");

	UBP_FrontEnd_C_ShouldShowErrorPopup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowMainMenu
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_FrontEnd_C::ShouldShowMainMenu()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowMainMenu");

	UBP_FrontEnd_C_ShouldShowMainMenu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowAlphaInfo
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_FrontEnd_C::ShouldShowAlphaInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowAlphaInfo");

	UBP_FrontEnd_C_ShouldShowAlphaInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_FrontEnd.BP_FrontEnd_C.SetupMainMenu
// ()

void UBP_FrontEnd_C::SetupMainMenu()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.SetupMainMenu");

	UBP_FrontEnd_C_SetupMainMenu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.Construct
// ()

void UBP_FrontEnd_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.Construct");

	UBP_FrontEnd_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.BndEvt__Widget_ErrorMessage_K2Node_ComponentBoundEvent_0_mOnClicked__DelegateSignature
// ()

void UBP_FrontEnd_C::BndEvt__Widget_ErrorMessage_K2Node_ComponentBoundEvent_0_mOnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.BndEvt__Widget_ErrorMessage_K2Node_ComponentBoundEvent_0_mOnClicked__DelegateSignature");

	UBP_FrontEnd_C_BndEvt__Widget_ErrorMessage_K2Node_ComponentBoundEvent_0_mOnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.GetAndSetNewError
// ()

void UBP_FrontEnd_C::GetAndSetNewError()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.GetAndSetNewError");

	UBP_FrontEnd_C_GetAndSetNewError_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ConditionallySetNewError
// ()

void UBP_FrontEnd_C::ConditionallySetNewError()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ConditionallySetNewError");

	UBP_FrontEnd_C_ConditionallySetNewError_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.Destruct
// ()

void UBP_FrontEnd_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.Destruct");

	UBP_FrontEnd_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ClosePopup
// ()

void UBP_FrontEnd_C::ClosePopup()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ClosePopup");

	UBP_FrontEnd_C_ClosePopup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FrontEnd.BP_FrontEnd_C.ExecuteUbergraph_BP_FrontEnd
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_FrontEnd_C::ExecuteUbergraph_BP_FrontEnd(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FrontEnd.BP_FrontEnd_C.ExecuteUbergraph_BP_FrontEnd");

	UBP_FrontEnd_C_ExecuteUbergraph_BP_FrontEnd_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
