#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SplitterProgrammableRule_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ShowHideDeleteButton
struct UWidget_SplitterProgrammableRule_C_ShowHideDeleteButton_Params
{
	bool                                               ShowDeleteButton;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.RemoveRule
struct UWidget_SplitterProgrammableRule_C_RemoveRule_Params
{
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetRuleOutputIndex
struct UWidget_SplitterProgrammableRule_C_SetRuleOutputIndex_Params
{
	int                                                OutputIndex;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetRuleItemClass
struct UWidget_SplitterProgrammableRule_C_SetRuleItemClass_Params
{
	class UClass*                                      ItemClass;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.GetSortRuleSafe
struct UWidget_SplitterProgrammableRule_C_GetSortRuleSafe_Params
{
	struct FSplitterSortRule                           Rule;                                                     // (Parm, OutParm)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.AddButtonsForDescriptorsContaining
struct UWidget_SplitterProgrammableRule_C_AddButtonsForDescriptorsContaining_Params
{
	struct FText                                       textToContain;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.SetSelectedItemDescriptor
struct UWidget_SplitterProgrammableRule_C_SetSelectedItemDescriptor_Params
{
	class UClass*                                      inDescriptor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.RefreshItemClassButton
struct UWidget_SplitterProgrammableRule_C_RefreshItemClassButton_Params
{
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.Construct
struct UWidget_SplitterProgrammableRule_C_Construct_Params
{
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_0_OnTextChanged__DelegateSignature
struct UWidget_SplitterProgrammableRule_C_BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_0_OnTextChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonClickedEvent__DelegateSignature
struct UWidget_SplitterProgrammableRule_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ForceRefreshButton
struct UWidget_SplitterProgrammableRule_C_ForceRefreshButton_Params
{
	struct FSplitterSortRule                           Splitter_Rule;                                            // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.BndEvt__mOtherListButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_SplitterProgrammableRule_C_BndEvt__mOtherListButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.PreConstruct
struct UWidget_SplitterProgrammableRule_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.ExecuteUbergraph_Widget_SplitterProgrammableRule
struct UWidget_SplitterProgrammableRule_C_ExecuteUbergraph_Widget_SplitterProgrammableRule_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnClicked__DelegateSignature
struct UWidget_SplitterProgrammableRule_C_OnClicked__DelegateSignature_Params
{
	class UWidget_SplitterProgrammableRule_C*          SplitterRule;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnUpdated__DelegateSignature
struct UWidget_SplitterProgrammableRule_C_OnUpdated__DelegateSignature_Params
{
	int                                                RuleIndex;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSplitterSortRule                           RuleData;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SplitterProgrammableRule.Widget_SplitterProgrammableRule_C.OnRemoved__DelegateSignature
struct UWidget_SplitterProgrammableRule_C_OnRemoved__DelegateSignature_Params
{
	class UWidget_SplitterProgrammableRule_C*          SplitterRule;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
