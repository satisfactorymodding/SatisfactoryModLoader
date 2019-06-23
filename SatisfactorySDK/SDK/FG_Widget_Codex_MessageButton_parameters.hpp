#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_MessageButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.CheckIsSelected
struct UWidget_Codex_MessageButton_C_CheckIsSelected_Params
{
	bool                                               mIsSelected;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.WasMessageReadColorFeedback
struct UWidget_Codex_MessageButton_C_WasMessageReadColorFeedback_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.WasMessageReadFeedbackVisibility
struct UWidget_Codex_MessageButton_C_WasMessageReadFeedbackVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.GetSelectedMessageFeedbackVisibility
struct UWidget_Codex_MessageButton_C_GetSelectedMessageFeedbackVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.MessageWasClicked
struct UWidget_Codex_MessageButton_C_MessageWasClicked_Params
{
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.GetMessageName
struct UWidget_Codex_MessageButton_C_GetMessageName_Params
{
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.PreConstruct
struct UWidget_Codex_MessageButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.BndEvt__mMessageButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
struct UWidget_Codex_MessageButton_C_BndEvt__mMessageButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.BndEvt__mMessageButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_Codex_MessageButton_C_BndEvt__mMessageButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.ExecuteUbergraph_Widget_Codex_MessageButton
struct UWidget_Codex_MessageButton_C_ExecuteUbergraph_Widget_Codex_MessageButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_MessageButton.Widget_Codex_MessageButton_C.OnClicked__DelegateSignature
struct UWidget_Codex_MessageButton_C_OnClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
