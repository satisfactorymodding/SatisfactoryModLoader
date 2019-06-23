// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SplitterProgrammableRule_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ShowHideDeleteButton
// ()
// Parameters:
// bool                           ShowDeleteButton               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::ShowHideDeleteButton(bool ShowDeleteButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ShowHideDeleteButton");

	UWidget_SplitterProgrammableRule_C_ShowHideDeleteButton_Params params;
	params.ShowDeleteButton = ShowDeleteButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.RemoveRule
// ()

void UWidget_SplitterProgrammableRule_C::RemoveRule()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.RemoveRule");

	UWidget_SplitterProgrammableRule_C_RemoveRule_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetRuleOutputIndex
// ()
// Parameters:
// int                            OutputIndex                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::SetRuleOutputIndex(int OutputIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetRuleOutputIndex");

	UWidget_SplitterProgrammableRule_C_SetRuleOutputIndex_Params params;
	params.OutputIndex = OutputIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetRuleItemClass
// ()
// Parameters:
// class UClass*                  ItemClass                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::SetRuleItemClass(class UClass* ItemClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetRuleItemClass");

	UWidget_SplitterProgrammableRule_C_SetRuleItemClass_Params params;
	params.ItemClass = ItemClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.GetSortRuleSafe
// ()
// Parameters:
// struct FSplitterSortRule       Rule                           (Parm, OutParm)

void UWidget_SplitterProgrammableRule_C::GetSortRuleSafe(struct FSplitterSortRule* Rule)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.GetSortRuleSafe");

	UWidget_SplitterProgrammableRule_C_GetSortRuleSafe_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Rule != nullptr)
		*Rule = params.Rule;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.AddButtonsForDescriptorsContaining
// ()
// Parameters:
// struct FText                   textToContain                  (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_SplitterProgrammableRule_C::AddButtonsForDescriptorsContaining(struct FText* textToContain)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.AddButtonsForDescriptorsContaining");

	UWidget_SplitterProgrammableRule_C_AddButtonsForDescriptorsContaining_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (textToContain != nullptr)
		*textToContain = params.textToContain;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetSelectedItemDescriptor
// ()
// Parameters:
// class UClass*                  inDescriptor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::SetSelectedItemDescriptor(class UClass* inDescriptor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetSelectedItemDescriptor");

	UWidget_SplitterProgrammableRule_C_SetSelectedItemDescriptor_Params params;
	params.inDescriptor = inDescriptor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.RefreshItemClassButton
// ()

void UWidget_SplitterProgrammableRule_C::RefreshItemClassButton()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.RefreshItemClassButton");

	UWidget_SplitterProgrammableRule_C_RefreshItemClassButton_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.Construct
// ()

void UWidget_SplitterProgrammableRule_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.Construct");

	UWidget_SplitterProgrammableRule_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_0_OnTextChanged__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SplitterProgrammableRule_C::BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_0_OnTextChanged__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_0_OnTextChanged__DelegateSignature");

	UWidget_SplitterProgrammableRule_C_BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_0_OnTextChanged__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SplitterProgrammableRule_C::BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonClickedEvent__DelegateSignature");

	UWidget_SplitterProgrammableRule_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ForceRefreshButton
// ()
// Parameters:
// struct FSplitterSortRule       Splitter_Rule                  (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SplitterProgrammableRule_C::ForceRefreshButton(const struct FSplitterSortRule& Splitter_Rule)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ForceRefreshButton");

	UWidget_SplitterProgrammableRule_C_ForceRefreshButton_Params params;
	params.Splitter_Rule = Splitter_Rule;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__mOtherListButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_ListButton_C*    ListButton                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::BndEvt__mOtherListButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature(int Index, class UWidget_ListButton_C* ListButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__mOtherListButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_SplitterProgrammableRule_C_BndEvt__mOtherListButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;
	params.Index = Index;
	params.ListButton = ListButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.PreConstruct");

	UWidget_SplitterProgrammableRule_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ExecuteUbergraph_Widget_SplitterProgrammableRule
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::ExecuteUbergraph_Widget_SplitterProgrammableRule(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ExecuteUbergraph_Widget_SplitterProgrammableRule");

	UWidget_SplitterProgrammableRule_C_ExecuteUbergraph_Widget_SplitterProgrammableRule_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_SplitterProgrammableRule_C* SplitterRule                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::OnClicked__DelegateSignature(class UWidget_SplitterProgrammableRule_C* SplitterRule)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnClicked__DelegateSignature");

	UWidget_SplitterProgrammableRule_C_OnClicked__DelegateSignature_Params params;
	params.SplitterRule = SplitterRule;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnUpdated__DelegateSignature
// ()
// Parameters:
// int                            RuleIndex                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSplitterSortRule       RuleData                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SplitterProgrammableRule_C::OnUpdated__DelegateSignature(int RuleIndex, const struct FSplitterSortRule& RuleData)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnUpdated__DelegateSignature");

	UWidget_SplitterProgrammableRule_C_OnUpdated__DelegateSignature_Params params;
	params.RuleIndex = RuleIndex;
	params.RuleData = RuleData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnRemoved__DelegateSignature
// ()
// Parameters:
// class UWidget_SplitterProgrammableRule_C* SplitterRule                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SplitterProgrammableRule_C::OnRemoved__DelegateSignature(class UWidget_SplitterProgrammableRule_C* SplitterRule)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnRemoved__DelegateSignature");

	UWidget_SplitterProgrammableRule_C_OnRemoved__DelegateSignature_Params params;
	params.SplitterRule = SplitterRule;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
