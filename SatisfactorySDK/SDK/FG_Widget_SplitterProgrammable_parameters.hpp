#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SplitterProgrammable_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.DeslectAllRules
struct UWidget_SplitterProgrammable_C_DeslectAllRules_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetAddButtonVisibility
struct UWidget_SplitterProgrammable_C_SetAddButtonVisibility_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.CheckIfSmartSplitter
struct UWidget_SplitterProgrammable_C_CheckIfSmartSplitter_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetLastRuleIndex
struct UWidget_SplitterProgrammable_C_GetLastRuleIndex_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateRuleIndexes
struct UWidget_SplitterProgrammable_C_UpdateRuleIndexes_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GenerateRules
struct UWidget_SplitterProgrammable_C_GenerateRules_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetOutputFromIndex
struct UWidget_SplitterProgrammable_C_GetOutputFromIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UVerticalBox*                                List;                                                     // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.AddRuleToOutput
struct UWidget_SplitterProgrammable_C_AddRuleToOutput_Params
{
	struct FSplitterSortRule                           SplitterSortRule;                                         // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	int                                                RuleIndex;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetWindowTitle
struct UWidget_SplitterProgrammable_C_SetWindowTitle_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.SetSortRuleWidgetBindings
struct UWidget_SplitterProgrammable_C_SetSortRuleWidgetBindings_Params
{
	class UWidget_SplitterProgrammableRule_C*          Widget;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, InstancedReference, ReferenceParm, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.GetNumSortRules
struct UWidget_SplitterProgrammable_C_GetNumSortRules_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.InitWindow
struct UWidget_SplitterProgrammable_C_InitWindow_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleRemoved
struct UWidget_SplitterProgrammable_C_OnRuleRemoved_Params
{
	class UWidget_SplitterProgrammableRule_C*          SplitterRule;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleUpdated
struct UWidget_SplitterProgrammable_C_OnRuleUpdated_Params
{
	int                                                RuleIndex;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSplitterSortRule                           RuleData;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.OnRuleAdded
struct UWidget_SplitterProgrammable_C_OnRuleAdded_Params
{
	struct FSplitterSortRule                           RuleData;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.PreConstruct
struct UWidget_SplitterProgrammable_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.ShowDescriptors
struct UWidget_SplitterProgrammable_C_ShowDescriptors_Params
{
	class UWidget_SplitterProgrammableRule_C*          SplitterRule;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.HideDescriptors
struct UWidget_SplitterProgrammable_C_HideDescriptors_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateRuleFromDescriptorList
struct UWidget_SplitterProgrammable_C_UpdateRuleFromDescriptorList_Params
{
	class UClass*                                      SelectedDescriptor;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.Construct
struct UWidget_SplitterProgrammable_C_Construct_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.UpdateListFromServer
struct UWidget_SplitterProgrammable_C_UpdateListFromServer_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.Destruct
struct UWidget_SplitterProgrammable_C_Destruct_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mLeftOutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature
struct UWidget_SplitterProgrammable_C_BndEvt__mLeftOutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mCenterOutputList_K2Node_ComponentBoundEvent_1_OnAddClicked__DelegateSignature
struct UWidget_SplitterProgrammable_C_BndEvt__mCenterOutputList_K2Node_ComponentBoundEvent_1_OnAddClicked__DelegateSignature_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.BndEvt__mRightOutputList_K2Node_ComponentBoundEvent_2_OnAddClicked__DelegateSignature
struct UWidget_SplitterProgrammable_C_BndEvt__mRightOutputList_K2Node_ComponentBoundEvent_2_OnAddClicked__DelegateSignature_Params
{
};

// Function Widget_SplitterProgrammable.Widget_SplitterProgrammable_C.ExecuteUbergraph_Widget_SplitterProgrammable
struct UWidget_SplitterProgrammable_C_ExecuteUbergraph_Widget_SplitterProgrammable_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
