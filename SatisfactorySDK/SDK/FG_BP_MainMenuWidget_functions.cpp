// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MainMenuWidget_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetExperimentalVisibility
// ()

void UBP_MainMenuWidget_C::GetExperimentalVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetExperimentalVisibility");

	UBP_MainMenuWidget_C_GetExperimentalVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.UpdateUsername
// ()

void UBP_MainMenuWidget_C::UpdateUsername()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.UpdateUsername");

	UBP_MainMenuWidget_C_UpdateUsername_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.UpdateVersionString
// ()

void UBP_MainMenuWidget_C::UpdateVersionString()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.UpdateVersionString");

	UBP_MainMenuWidget_C_UpdateVersionString_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetMostRecentSave
// ()

void UBP_MainMenuWidget_C::GetMostRecentSave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetMostRecentSave");

	UBP_MainMenuWidget_C_GetMostRecentSave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetVersionString
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UBP_MainMenuWidget_C::GetVersionString()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetVersionString");

	UBP_MainMenuWidget_C_GetVersionString_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnEscape
// ()

void UBP_MainMenuWidget_C::OnEscape()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnEscape");

	UBP_MainMenuWidget_C_OnEscape_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonQuit_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::BndEvt__mButtonQuit_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonQuit_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UBP_MainMenuWidget_C_BndEvt__mButtonQuit_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.Construct
// ()

void UBP_MainMenuWidget_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.Construct");

	UBP_MainMenuWidget_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonContinue_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::BndEvt__mButtonContinue_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonContinue_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UBP_MainMenuWidget_C_BndEvt__mButtonContinue_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonMP_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::BndEvt__mButtonMP_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonMP_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature");

	UBP_MainMenuWidget_C_BndEvt__mButtonMP_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnExit
// ()
// Parameters:
// bool                           Bool                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MainMenuWidget_C::OnExit(bool Bool)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnExit");

	UBP_MainMenuWidget_C_OnExit_Params params;
	params.Bool = Bool;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.NATTypeUpdated
// ()
// Parameters:
// ECachedNATType                 natType                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MainMenuWidget_C::NATTypeUpdated(ECachedNATType natType)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.NATTypeUpdated");

	UBP_MainMenuWidget_C_NATTypeUpdated_Params params;
	params.natType = natType;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.Destruct
// ()

void UBP_MainMenuWidget_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.Destruct");

	UBP_MainMenuWidget_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_MainMenuWidget_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnMenuEnter");

	UBP_MainMenuWidget_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.LoginStateChanged
// ()
// Parameters:
// TEnumAsByte<ELoginState>       oldState                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ELoginState>       newState                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MainMenuWidget_C::LoginStateChanged(TEnumAsByte<ELoginState> oldState, TEnumAsByte<ELoginState> newState)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.LoginStateChanged");

	UBP_MainMenuWidget_C_LoginStateChanged_Params params;
	params.oldState = oldState;
	params.newState = newState;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.ExecuteUbergraph_BP_MainMenuWidget
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MainMenuWidget_C::ExecuteUbergraph_BP_MainMenuWidget(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.ExecuteUbergraph_BP_MainMenuWidget");

	UBP_MainMenuWidget_C_ExecuteUbergraph_BP_MainMenuWidget_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnCreditsClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::OnCreditsClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnCreditsClicked__DelegateSignature");

	UBP_MainMenuWidget_C_OnCreditsClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnModsClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::OnModsClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnModsClicked__DelegateSignature");

	UBP_MainMenuWidget_C_OnModsClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnOptionsClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::OnOptionsClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnOptionsClicked__DelegateSignature");

	UBP_MainMenuWidget_C_OnOptionsClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnLoadClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::OnLoadClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnLoadClicked__DelegateSignature");

	UBP_MainMenuWidget_C_OnLoadClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnExitClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::OnExitClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnExitClicked__DelegateSignature");

	UBP_MainMenuWidget_C_OnExitClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnBrowseClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::OnBrowseClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnBrowseClicked__DelegateSignature");

	UBP_MainMenuWidget_C_OnBrowseClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnPlayClicked__DelegateSignature
// ()

void UBP_MainMenuWidget_C::OnPlayClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnPlayClicked__DelegateSignature");

	UBP_MainMenuWidget_C_OnPlayClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
