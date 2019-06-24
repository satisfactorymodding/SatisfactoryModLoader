// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RadarTower_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RadarTower.Widget_RadarTower_C.UpdateStandByButton
// ()
// Parameters:
// bool                           Producing                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_C::UpdateStandByButton(bool Producing)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.UpdateStandByButton");

	UWidget_RadarTower_C_UpdateStandByButton_Params params;
	params.Producing = Producing;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.ToggleStandby
// ()

void UWidget_RadarTower_C::ToggleStandby()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.ToggleStandby");

	UWidget_RadarTower_C_ToggleStandby_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.RevealStepToNormalizedRevealPercent
// ()
// Parameters:
// int                            inInt                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_RadarTower_C::RevealStepToNormalizedRevealPercent(int inInt)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.RevealStepToNormalizedRevealPercent");

	UWidget_RadarTower_C_RevealStepToNormalizedRevealPercent_Params params;
	params.inInt = inInt;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RadarTower.Widget_RadarTower_C.InitScanLines
// ()

void UWidget_RadarTower_C::InitScanLines()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.InitScanLines");

	UWidget_RadarTower_C_InitScanLines_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.UpdateTitle
// ()
// Parameters:
// struct FText                   OverrideText                   (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_RadarTower_C::UpdateTitle(const struct FText& OverrideText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.UpdateTitle");

	UWidget_RadarTower_C_UpdateTitle_Params params;
	params.OverrideText = OverrideText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.SecondsToMinutesAndSecondsText
// ()
// Parameters:
// float                          Input                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   Output                         (Parm, OutParm)

void UWidget_RadarTower_C::SecondsToMinutesAndSecondsText(float Input, struct FText* Output)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.SecondsToMinutesAndSecondsText");

	UWidget_RadarTower_C_SecondsToMinutesAndSecondsText_Params params;
	params.Input = Input;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Output != nullptr)
		*Output = params.Output;
}


// Function Widget_RadarTower.Widget_RadarTower_C.InitScannedPercent
// ()

void UWidget_RadarTower_C::InitScannedPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.InitScannedPercent");

	UWidget_RadarTower_C_InitScannedPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.Construct
// ()

void UWidget_RadarTower_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.Construct");

	UWidget_RadarTower_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.OnRadiusChanged
// ()

void UWidget_RadarTower_C::OnRadiusChanged()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.OnRadiusChanged");

	UWidget_RadarTower_C_OnRadiusChanged_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.UpdateScanTimer
// ()

void UWidget_RadarTower_C::UpdateScanTimer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.UpdateScanTimer");

	UWidget_RadarTower_C_UpdateScanTimer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.Destruct
// ()

void UWidget_RadarTower_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.Destruct");

	UWidget_RadarTower_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__mTowerName_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_C::BndEvt__mTowerName_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__mTowerName_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature");

	UWidget_RadarTower_C_BndEvt__mTowerName_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.LerpScannedAreaEvent
// ()

void UWidget_RadarTower_C::LerpScannedAreaEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.LerpScannedAreaEvent");

	UWidget_RadarTower_C_LerpScannedAreaEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__mRadarTower_K2Node_ComponentBoundEvent_2_BuildingStateChanged__DelegateSignature
// ()
// Parameters:
// bool                           State                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_C::BndEvt__mRadarTower_K2Node_ComponentBoundEvent_2_BuildingStateChanged__DelegateSignature(bool State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__mRadarTower_K2Node_ComponentBoundEvent_2_BuildingStateChanged__DelegateSignature");

	UWidget_RadarTower_C_BndEvt__mRadarTower_K2Node_ComponentBoundEvent_2_BuildingStateChanged__DelegateSignature_Params params;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_3_OnStandbyClicked__DelegateSignature
// ()

void UWidget_RadarTower_C::BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_3_OnStandbyClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_3_OnStandbyClicked__DelegateSignature");

	UWidget_RadarTower_C_BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_3_OnStandbyClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.OnProductionChanged
// ()
// Parameters:
// bool                           HasChanged                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_C::OnProductionChanged(bool HasChanged)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.OnProductionChanged");

	UWidget_RadarTower_C_OnProductionChanged_Params params;
	params.HasChanged = HasChanged;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower.Widget_RadarTower_C.ExecuteUbergraph_Widget_RadarTower
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_C::ExecuteUbergraph_Widget_RadarTower(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower.Widget_RadarTower_C.ExecuteUbergraph_Widget_RadarTower");

	UWidget_RadarTower_C_ExecuteUbergraph_Widget_RadarTower_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
