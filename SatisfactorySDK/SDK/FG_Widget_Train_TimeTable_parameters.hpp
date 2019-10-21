#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Train_TimeTable_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.SetCurrentStop
struct UWidget_Train_TimeTable_C_SetCurrentStop_Params
{
	class UWidget_Train_TimeTable_Rule_C*              RuleWidget;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.ShowApplyChangesPrompt
struct UWidget_Train_TimeTable_C_ShowApplyChangesPrompt_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.CloseAvailableStationsWidget
struct UWidget_Train_TimeTable_C_CloseAvailableStationsWidget_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.MoveRule
struct UWidget_Train_TimeTable_C_MoveRule_Params
{
	class UWidget_Train_TimeTable_Rule_C*              RuleWidget;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               MoveDown;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.SetSelectedRule
struct UWidget_Train_TimeTable_C_SetSelectedRule_Params
{
	class UWidget_Train_TimeTable_Rule_C*              SelectedRule;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.AddRule
struct UWidget_Train_TimeTable_C_AddRule_Params
{
	class AFGTrainStationIdentifier*                   mStation;                                                 // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateStopsOnServer
struct UWidget_Train_TimeTable_C_UpdateStopsOnServer_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.GenerateNewStopArray
struct UWidget_Train_TimeTable_C_GenerateNewStopArray_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.PopulateAvailableStations
struct UWidget_Train_TimeTable_C_PopulateAvailableStations_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.PopulateTimeTable
struct UWidget_Train_TimeTable_C_PopulateTimeTable_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateTrainStations
struct UWidget_Train_TimeTable_C_UpdateTrainStations_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.Init
struct UWidget_Train_TimeTable_C_Init_Params
{
	class AFGTrain*                                    Train;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.BndEvt__Widget_Splitter_OutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature
struct UWidget_Train_TimeTable_C_BndEvt__Widget_Splitter_OutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleClicked
struct UWidget_Train_TimeTable_C_OnRuleClicked_Params
{
	class UWidget_Train_TimeTable_Rule_C*              RuleWidget;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateStation
struct UWidget_Train_TimeTable_C_UpdateStation_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.UpdateAvailableStationsSelectedIndex
struct UWidget_Train_TimeTable_C_UpdateAvailableStationsSelectedIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleDeleted
struct UWidget_Train_TimeTable_C_OnRuleDeleted_Params
{
	class UWidget_Train_TimeTable_Rule_C*              RuleWidget;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.Destruct
struct UWidget_Train_TimeTable_C_Destruct_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleMoveUp
struct UWidget_Train_TimeTable_C_OnRuleMoveUp_Params
{
	class UWidget_Train_TimeTable_Rule_C*              RuleWidget;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.OnRuleMoveDown
struct UWidget_Train_TimeTable_C_OnRuleMoveDown_Params
{
	class UWidget_Train_TimeTable_Rule_C*              RuleWidget;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.CheckCurrentStop
struct UWidget_Train_TimeTable_C_CheckCurrentStop_Params
{
};

// Function Widget_Train_TimeTable.Widget_Train_TimeTable_C.ExecuteUbergraph_Widget_Train_TimeTable
struct UWidget_Train_TimeTable_C_ExecuteUbergraph_Widget_Train_TimeTable_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
