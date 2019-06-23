// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerHUD_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mCollectBar_Percent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_PlayerHUD_C::Get_mCollectBar_Percent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mCollectBar_Percent");

	UWidget_PlayerHUD_C_Get_mCollectBar_Percent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_CollectBarContainer_Visibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PlayerHUD_C::Get_CollectBarContainer_Visibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_CollectBarContainer_Visibility");

	UWidget_PlayerHUD_C_Get_CollectBarContainer_Visibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnToggleInteractUI
// ()
// Parameters:
// bool                           IsOpen                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  InteractWidgetClass            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerHUD_C::OnToggleInteractUI(bool IsOpen, class UClass* InteractWidgetClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnToggleInteractUI");

	UWidget_PlayerHUD_C_OnToggleInteractUI_Params params;
	params.IsOpen = IsOpen;
	params.InteractWidgetClass = InteractWidgetClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnToggleInventory
// ()
// Parameters:
// bool                           IsOpen                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerHUD_C::OnToggleInventory(bool IsOpen)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnToggleInventory");

	UWidget_PlayerHUD_C_OnToggleInventory_Params params;
	params.IsOpen = IsOpen;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.SetImageVisibility
// ()
// Parameters:
// bool                           Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UImage*                  Image                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_PlayerHUD_C::SetImageVisibility(bool Value, class UImage* Image)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.SetImageVisibility");

	UWidget_PlayerHUD_C_SetImageVisibility_Params params;
	params.Value = Value;
	params.Image = Image;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnDisabledInputGateChanged
// ()
// Parameters:
// struct FDisabledInputGate      NewValue                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerHUD_C::OnDisabledInputGateChanged(const struct FDisabledInputGate& NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.OnDisabledInputGateChanged");

	UWidget_PlayerHUD_C_OnDisabledInputGateChanged_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.GetVisibility_1
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PlayerHUD_C::GetVisibility_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.GetVisibility_1");

	UWidget_PlayerHUD_C_GetVisibility_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mInputLockedTExt_Visibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PlayerHUD_C::Get_mInputLockedTExt_Visibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mInputLockedTExt_Visibility");

	UWidget_PlayerHUD_C_Get_mInputLockedTExt_Visibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.GetScannerDetailsVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PlayerHUD_C::GetScannerDetailsVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.GetScannerDetailsVisibility");

	UWidget_PlayerHUD_C_GetScannerDetailsVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mReviveProgressBar_Visibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_PlayerHUD_C::Get_mReviveProgressBar_Visibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mReviveProgressBar_Visibility");

	UWidget_PlayerHUD_C_Get_mReviveProgressBar_Visibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mReviveProgressBar_Percent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_PlayerHUD_C::Get_mReviveProgressBar_Percent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.Get_mReviveProgressBar_Percent");

	UWidget_PlayerHUD_C_Get_mReviveProgressBar_Percent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.PlayRadiationAnimation
// ()

void UWidget_PlayerHUD_C::PlayRadiationAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.PlayRadiationAnimation");

	UWidget_PlayerHUD_C_PlayRadiationAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.StopRadiationAnimation
// ()

void UWidget_PlayerHUD_C::StopRadiationAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.StopRadiationAnimation");

	UWidget_PlayerHUD_C_StopRadiationAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.Construct
// ()

void UWidget_PlayerHUD_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.Construct");

	UWidget_PlayerHUD_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerHUD.Widget_PlayerHUD_C.ExecuteUbergraph_Widget_PlayerHUD
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerHUD_C::ExecuteUbergraph_Widget_PlayerHUD(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerHUD.Widget_PlayerHUD_C.ExecuteUbergraph_Widget_PlayerHUD");

	UWidget_PlayerHUD_C_ExecuteUbergraph_Widget_PlayerHUD_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
