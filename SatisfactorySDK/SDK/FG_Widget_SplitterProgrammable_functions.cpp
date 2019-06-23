// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SplitterProgrammable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.DeslectAllRules
// ()

void UWidget_SplitterProgrammable_C::DeslectAllRules()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.DeslectAllRules");

	UWidget_SplitterProgrammable_C_DeslectAllRules_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetAddButtonVisibility
// ()

void UWidget_SplitterProgrammable_C::SetAddButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetAddButtonVisibility");

	UWidget_SplitterProgrammable_C_SetAddButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.CheckIfSmartSplitter
// ()

void UWidget_SplitterProgrammable_C::CheckIfSmartSplitter()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.CheckIfSmartSplitter");

	UWidget_SplitterProgrammable_C_CheckIfSmartSplitter_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetLastRuleIndex
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidget_SplitterProgrammable_C::GetLastRuleIndex()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetLastRuleIndex");

	UWidget_SplitterProgrammable_C_GetLastRuleIndex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateRuleIndexes
// ()

void UWidget_SplitterProgrammable_C::UpdateRuleIndexes()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateRuleIndexes");

	UWidget_SplitterProgrammable_C_UpdateRuleIndexes_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GenerateRules
// ()

void UWidget_SplitterProgrammable_C::GenerateRules()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GenerateRules");

	UWidget_SplitterProgrammable_C_GenerateRules_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetOutputFromIndex
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UVerticalBox*            List                           (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SplitterProgrammable_C::GetOutputFromIndex(int Index, class UVerticalBox** List)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetOutputFromIndex");

	UWidget_SplitterProgrammable_C_GetOutputFromIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (List != nullptr)
		*List = params.List;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.AddRuleToOutput
// ()
// Parameters:
// struct FSplitterSortRule       SplitterSortRule               (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// int                            RuleIndex                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammable_C::AddRuleToOutput(const struct FSplitterSortRule& SplitterSortRule, int RuleIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.AddRuleToOutput");

	UWidget_SplitterProgrammable_C_AddRuleToOutput_Params params;
	params.SplitterSortRule = SplitterSortRule;
	params.RuleIndex = RuleIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetWindowTitle
// ()

void UWidget_SplitterProgrammable_C::SetWindowTitle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetWindowTitle");

	UWidget_SplitterProgrammable_C_SetWindowTitle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetSortRuleWidgetBindings
// ()
// Parameters:
// class UWidget_SplitterProgrammableRule_C* Widget                         (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, InstancedReference, ReferenceParm, IsPlainOldData)

void UWidget_SplitterProgrammable_C::SetSortRuleWidgetBindings(class UWidget_SplitterProgrammableRule_C** Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetSortRuleWidgetBindings");

	UWidget_SplitterProgrammable_C_SetSortRuleWidgetBindings_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Widget != nullptr)
		*Widget = params.Widget;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetNumSortRules
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidget_SplitterProgrammable_C::GetNumSortRules()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetNumSortRules");

	UWidget_SplitterProgrammable_C_GetNumSortRules_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.InitWindow
// ()

void UWidget_SplitterProgrammable_C::InitWindow()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.InitWindow");

	UWidget_SplitterProgrammable_C_InitWindow_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleRemoved
// ()
// Parameters:
// class UWidget_SplitterProgrammableRule_C* SplitterRule                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SplitterProgrammable_C::OnRuleRemoved(class UWidget_SplitterProgrammableRule_C* SplitterRule)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleRemoved");

	UWidget_SplitterProgrammable_C_OnRuleRemoved_Params params;
	params.SplitterRule = SplitterRule;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleUpdated
// ()
// Parameters:
// int                            RuleIndex                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSplitterSortRule       RuleData                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SplitterProgrammable_C::OnRuleUpdated(int RuleIndex, const struct FSplitterSortRule& RuleData)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleUpdated");

	UWidget_SplitterProgrammable_C_OnRuleUpdated_Params params;
	params.RuleIndex = RuleIndex;
	params.RuleData = RuleData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleAdded
// ()
// Parameters:
// struct FSplitterSortRule       RuleData                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SplitterProgrammable_C::OnRuleAdded(const struct FSplitterSortRule& RuleData)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleAdded");

	UWidget_SplitterProgrammable_C_OnRuleAdded_Params params;
	params.RuleData = RuleData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammable_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.PreConstruct");

	UWidget_SplitterProgrammable_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.ShowDescriptors
// ()
// Parameters:
// class UWidget_SplitterProgrammableRule_C* SplitterRule                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SplitterProgrammable_C::ShowDescriptors(class UWidget_SplitterProgrammableRule_C* SplitterRule)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.ShowDescriptors");

	UWidget_SplitterProgrammable_C_ShowDescriptors_Params params;
	params.SplitterRule = SplitterRule;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.HideDescriptors
// ()

void UWidget_SplitterProgrammable_C::HideDescriptors()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.HideDescriptors");

	UWidget_SplitterProgrammable_C_HideDescriptors_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateRuleFromDescriptorList
// ()
// Parameters:
// class UClass*                  SelectedDescriptor             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammable_C::UpdateRuleFromDescriptorList(class UClass* SelectedDescriptor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateRuleFromDescriptorList");

	UWidget_SplitterProgrammable_C_UpdateRuleFromDescriptorList_Params params;
	params.SelectedDescriptor = SelectedDescriptor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.Construct
// ()

void UWidget_SplitterProgrammable_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.Construct");

	UWidget_SplitterProgrammable_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateListFromServer
// ()

void UWidget_SplitterProgrammable_C::UpdateListFromServer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateListFromServer");

	UWidget_SplitterProgrammable_C_UpdateListFromServer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.Destruct
// ()

void UWidget_SplitterProgrammable_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.Destruct");

	UWidget_SplitterProgrammable_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mLeftOutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature
// ()

void UWidget_SplitterProgrammable_C::BndEvt__mLeftOutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mLeftOutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature");

	UWidget_SplitterProgrammable_C_BndEvt__mLeftOutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mCenterOutputList_K2Node_ComponentBoundEvent_1_OnAddClicked__DelegateSignature
// ()

void UWidget_SplitterProgrammable_C::BndEvt__mCenterOutputList_K2Node_ComponentBoundEvent_1_OnAddClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mCenterOutputList_K2Node_ComponentBoundEvent_1_OnAddClicked__DelegateSignature");

	UWidget_SplitterProgrammable_C_BndEvt__mCenterOutputList_K2Node_ComponentBoundEvent_1_OnAddClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mRightOutputList_K2Node_ComponentBoundEvent_2_OnAddClicked__DelegateSignature
// ()

void UWidget_SplitterProgrammable_C::BndEvt__mRightOutputList_K2Node_ComponentBoundEvent_2_OnAddClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mRightOutputList_K2Node_ComponentBoundEvent_2_OnAddClicked__DelegateSignature");

	UWidget_SplitterProgrammable_C_BndEvt__mRightOutputList_K2Node_ComponentBoundEvent_2_OnAddClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.ExecuteUbergraph_Widget_SplitterProgrammable
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammable_C::ExecuteUbergraph_Widget_SplitterProgrammable(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.ExecuteUbergraph_Widget_SplitterProgrammable");

	UWidget_SplitterProgrammable_C_ExecuteUbergraph_Widget_SplitterProgrammable_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
