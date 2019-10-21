// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Train_TimeTable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.SetCurrentStop
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_C::SetCurrentStop(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.SetCurrentStop");

	UWidget_Train_TimeTable_C_SetCurrentStop_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.ShowApplyChangesPrompt
// ()

void UWidget_Train_TimeTable_C::ShowApplyChangesPrompt()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.ShowApplyChangesPrompt");

	UWidget_Train_TimeTable_C_ShowApplyChangesPrompt_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.CloseAvailableStationsWidget
// ()

void UWidget_Train_TimeTable_C::CloseAvailableStationsWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.CloseAvailableStationsWidget");

	UWidget_Train_TimeTable_C_CloseAvailableStationsWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.MoveRule
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           MoveDown                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_C::MoveRule(class UWidget_Train_TimeTable_Rule_C* RuleWidget, bool MoveDown)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.MoveRule");

	UWidget_Train_TimeTable_C_MoveRule_Params params;
	params.RuleWidget = RuleWidget;
	params.MoveDown = MoveDown;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.SetSelectedRule
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* SelectedRule                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_C::SetSelectedRule(class UWidget_Train_TimeTable_Rule_C* SelectedRule)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.SetSelectedRule");

	UWidget_Train_TimeTable_C_SetSelectedRule_Params params;
	params.SelectedRule = SelectedRule;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.AddRule
// ()
// Parameters:
// class AFGTrainStationIdentifier* mStation                       (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)

void UWidget_Train_TimeTable_C::AddRule(class AFGTrainStationIdentifier* mStation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.AddRule");

	UWidget_Train_TimeTable_C_AddRule_Params params;
	params.mStation = mStation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateStopsOnServer
// ()

void UWidget_Train_TimeTable_C::UpdateStopsOnServer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateStopsOnServer");

	UWidget_Train_TimeTable_C_UpdateStopsOnServer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.GenerateNewStopArray
// ()

void UWidget_Train_TimeTable_C::GenerateNewStopArray()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.GenerateNewStopArray");

	UWidget_Train_TimeTable_C_GenerateNewStopArray_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.PopulateAvailableStations
// ()

void UWidget_Train_TimeTable_C::PopulateAvailableStations()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.PopulateAvailableStations");

	UWidget_Train_TimeTable_C_PopulateAvailableStations_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.PopulateTimeTable
// ()

void UWidget_Train_TimeTable_C::PopulateTimeTable()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.PopulateTimeTable");

	UWidget_Train_TimeTable_C_PopulateTimeTable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateTrainStations
// ()

void UWidget_Train_TimeTable_C::UpdateTrainStations()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateTrainStations");

	UWidget_Train_TimeTable_C_UpdateTrainStations_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.Init
// ()
// Parameters:
// class AFGTrain*                Train                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_C::Init(class AFGTrain* Train)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.Init");

	UWidget_Train_TimeTable_C_Init_Params params;
	params.Train = Train;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.BndEvt__Widget_Splitter_OutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature
// ()

void UWidget_Train_TimeTable_C::BndEvt__Widget_Splitter_OutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.BndEvt__Widget_Splitter_OutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature");

	UWidget_Train_TimeTable_C_BndEvt__Widget_Splitter_OutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleClicked
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_C::OnRuleClicked(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleClicked");

	UWidget_Train_TimeTable_C_OnRuleClicked_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateStation
// ()

void UWidget_Train_TimeTable_C::UpdateStation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateStation");

	UWidget_Train_TimeTable_C_UpdateStation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateAvailableStationsSelectedIndex
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_ListButton_C*    ListButton                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_C::UpdateAvailableStationsSelectedIndex(int Index, class UWidget_ListButton_C* ListButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateAvailableStationsSelectedIndex");

	UWidget_Train_TimeTable_C_UpdateAvailableStationsSelectedIndex_Params params;
	params.Index = Index;
	params.ListButton = ListButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleDeleted
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_C::OnRuleDeleted(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleDeleted");

	UWidget_Train_TimeTable_C_OnRuleDeleted_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.Destruct
// ()

void UWidget_Train_TimeTable_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.Destruct");

	UWidget_Train_TimeTable_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleMoveUp
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_C::OnRuleMoveUp(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleMoveUp");

	UWidget_Train_TimeTable_C_OnRuleMoveUp_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleMoveDown
// ()
// Parameters:
// class UWidget_Train_TimeTable_Rule_C* RuleWidget                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Train_TimeTable_C::OnRuleMoveDown(class UWidget_Train_TimeTable_Rule_C* RuleWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleMoveDown");

	UWidget_Train_TimeTable_C_OnRuleMoveDown_Params params;
	params.RuleWidget = RuleWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.CheckCurrentStop
// ()

void UWidget_Train_TimeTable_C::CheckCurrentStop()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.CheckCurrentStop");

	UWidget_Train_TimeTable_C_CheckCurrentStop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.ExecuteUbergraph_Widget_Train_TimeTable
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Train_TimeTable_C::ExecuteUbergraph_Widget_Train_TimeTable(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.ExecuteUbergraph_Widget_Train_TimeTable");

	UWidget_Train_TimeTable_C_ExecuteUbergraph_Widget_Train_TimeTable_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
