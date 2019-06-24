#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SessionSaveRow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.SetSelected
struct UWidget_SessionSaveRow_C_SetSelected_Params
{
	bool                                               isSelected;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetIconColor
struct UWidget_SessionSaveRow_C_GetIconColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetTextColor
struct UWidget_SessionSaveRow_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetPlayDurationTextColor
struct UWidget_SessionSaveRow_C_GetPlayDurationTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetIconBGColor
struct UWidget_SessionSaveRow_C_GetIconBGColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetHoverColor
struct UWidget_SessionSaveRow_C_GetHoverColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetPlayDuration
struct UWidget_SessionSaveRow_C_GetPlayDuration_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetSaveTimeText
struct UWidget_SessionSaveRow_C_GetSaveTimeText_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.GetSaveNameText
struct UWidget_SessionSaveRow_C_GetSaveNameText_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
struct UWidget_SessionSaveRow_C_BndEvt__mSaveButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature
struct UWidget_SessionSaveRow_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.ConfirmDeleteSavePopUp
struct UWidget_SessionSaveRow_C_ConfirmDeleteSavePopUp_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.PreConstruct
struct UWidget_SessionSaveRow_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.Event DeleteSave
struct UWidget_SessionSaveRow_C_Event_DeleteSave_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_SessionSaveRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature
struct UWidget_SessionSaveRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_8_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_SessionSaveRow_C_BndEvt__mSaveRowButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SessionSaveRow.Widget_SessionSaveRow_C.ExecuteUbergraph_Widget_SessionSaveRow
struct UWidget_SessionSaveRow_C_ExecuteUbergraph_Widget_SessionSaveRow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
