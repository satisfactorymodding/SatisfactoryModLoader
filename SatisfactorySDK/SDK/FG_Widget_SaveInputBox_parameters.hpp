#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SaveInputBox_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.SetButtonColor
struct UWidget_SaveInputBox_C_SetButtonColor_Params
{
	struct FSlateColor                                 Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.Construct
struct UWidget_SaveInputBox_C_Construct_Params
{
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_SaveInputBox_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.BndEvt__mSaveInputBox_K2Node_ComponentBoundEvent_1_OnEditableTextBoxChangedEvent__DelegateSignature
struct UWidget_SaveInputBox_C_BndEvt__mSaveInputBox_K2Node_ComponentBoundEvent_1_OnEditableTextBoxChangedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.BndEvt__mSaveInputBox_K2Node_ComponentBoundEvent_2_OnEditableTextBoxCommittedEvent__DelegateSignature
struct UWidget_SaveInputBox_C_BndEvt__mSaveInputBox_K2Node_ComponentBoundEvent_2_OnEditableTextBoxCommittedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.CheckUserFocus
struct UWidget_SaveInputBox_C_CheckUserFocus_Params
{
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.Destruct
struct UWidget_SaveInputBox_C_Destruct_Params
{
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.ExecuteUbergraph_Widget_SaveInputBox
struct UWidget_SaveInputBox_C_ExecuteUbergraph_Widget_SaveInputBox_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.OnUnfocused__DelegateSignature
struct UWidget_SaveInputBox_C_OnUnfocused__DelegateSignature_Params
{
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.OnFocused__DelegateSignature
struct UWidget_SaveInputBox_C_OnFocused__DelegateSignature_Params
{
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.OnTextCommited__DelegateSignature
struct UWidget_SaveInputBox_C_OnTextCommited__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveInputBox.Widget_SaveInputBox_C.OnTextChanged__DelegateSignature
struct UWidget_SaveInputBox_C_OnTextChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
