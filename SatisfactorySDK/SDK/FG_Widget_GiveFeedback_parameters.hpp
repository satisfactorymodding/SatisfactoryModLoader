#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GiveFeedback_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.PopulateTypeFeedbackOptions
struct UWidget_GiveFeedback_C_PopulateTypeFeedbackOptions_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.PopulateSatisfactorySelectOptions
struct UWidget_GiveFeedback_C_PopulateSatisfactorySelectOptions_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.OnKeyDown
struct UWidget_GiveFeedback_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.Construct
struct UWidget_GiveFeedback_C_Construct_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
struct UWidget_GiveFeedback_C_BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.CloseFeedback
struct UWidget_GiveFeedback_C_CloseFeedback_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__THANKSDUDE_K2Node_ComponentBoundEvent_147_OnClicked__DelegateSignature
struct UWidget_GiveFeedback_C_BndEvt__THANKSDUDE_K2Node_ComponentBoundEvent_147_OnClicked__DelegateSignature_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__mTypeFeedbackSelect_K2Node_ComponentBoundEvent_1_onSelectionChanged__DelegateSignature
struct UWidget_GiveFeedback_C_BndEvt__mTypeFeedbackSelect_K2Node_ComponentBoundEvent_1_onSelectionChanged__DelegateSignature_Params
{
	class FString                                      SelectedOption;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Details_text_K2Node_ComponentBoundEvent_4_OnMultiLineEditableTextChangedEvent__DelegateSignature
struct UWidget_GiveFeedback_C_BndEvt__Details_text_K2Node_ComponentBoundEvent_4_OnMultiLineEditableTextChangedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature
struct UWidget_GiveFeedback_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature
struct UWidget_GiveFeedback_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.SendFeedbackAfterConfirm
struct UWidget_GiveFeedback_C_SendFeedbackAfterConfirm_Params
{
	bool                                               mConfirmBool;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
struct UWidget_GiveFeedback_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_GiveFeedback.Widget_GiveFeedback_C.ExecuteUbergraph_Widget_GiveFeedback
struct UWidget_GiveFeedback_C_ExecuteUbergraph_Widget_GiveFeedback_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
