// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NetworkErrorPopup_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.CreatePopup
// ()
// Parameters:
// struct FFGGameNetworkErrorMsg  FGGameNetworkErrorMsg          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_NetworkErrorPopup_C::CreatePopup(const struct FFGGameNetworkErrorMsg& FGGameNetworkErrorMsg)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.CreatePopup");

	UWidget_NetworkErrorPopup_C_CreatePopup_Params params;
	params.FGGameNetworkErrorMsg = FGGameNetworkErrorMsg;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.Construct
// ()

void UWidget_NetworkErrorPopup_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.Construct");

	UWidget_NetworkErrorPopup_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.mOnNetworkErrorRecieved_Event_1
// ()
// Parameters:
// TEnumAsByte<ENetworkFailure>   errorType                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class FString                  errorMsg                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void UWidget_NetworkErrorPopup_C::mOnNetworkErrorRecieved_Event_1(TEnumAsByte<ENetworkFailure> errorType, const class FString& errorMsg)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.mOnNetworkErrorRecieved_Event_1");

	UWidget_NetworkErrorPopup_C_mOnNetworkErrorRecieved_Event_1_Params params;
	params.errorType = errorType;
	params.errorMsg = errorMsg;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.CheckErrors
// ()

void UWidget_NetworkErrorPopup_C::CheckErrors()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.CheckErrors");

	UWidget_NetworkErrorPopup_C_CheckErrors_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.OnPopupClosed
// ()
// Parameters:
// bool                           NewParam                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_NetworkErrorPopup_C::OnPopupClosed(bool NewParam)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.OnPopupClosed");

	UWidget_NetworkErrorPopup_C_OnPopupClosed_Params params;
	params.NewParam = NewParam;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.ExecuteUbergraph_Widget_NetworkErrorPopup
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_NetworkErrorPopup_C::ExecuteUbergraph_Widget_NetworkErrorPopup(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.ExecuteUbergraph_Widget_NetworkErrorPopup");

	UWidget_NetworkErrorPopup_C_ExecuteUbergraph_Widget_NetworkErrorPopup_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
