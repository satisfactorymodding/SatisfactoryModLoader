#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SessionRow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SessionRow.Widget_SessionRow_C.SetDisabled
struct UWidget_SessionRow_C_SetDisabled_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetPointerVisibility
struct UWidget_SessionRow_C_GetPointerVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SessionRow.Widget_SessionRow_C.OnButtonClicked
struct UWidget_SessionRow_C_OnButtonClicked_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetMostRecentSaveFromSession
struct UWidget_SessionRow_C_GetMostRecentSaveFromSession_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetLastSaveTime
struct UWidget_SessionRow_C_GetLastSaveTime_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetSessionName
struct UWidget_SessionRow_C_GetSessionName_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetLastSaveName
struct UWidget_SessionRow_C_GetLastSaveName_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.PopulateSavesFromSession
struct UWidget_SessionRow_C_PopulateSavesFromSession_Params
{
	struct FSessionSaveStruct                          session;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SessionRow.Widget_SessionRow_C.OnFocusReceived
struct UWidget_SessionRow_C_OnFocusReceived_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetSaveTextColor
struct UWidget_SessionRow_C_GetSaveTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetIconColor
struct UWidget_SessionRow_C_GetIconColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SessionRow.Widget_SessionRow_C.GetButtonHoverColor
struct UWidget_SessionRow_C_GetButtonHoverColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mButton_K2Node_ComponentBoundEvent_120_OnButtonClickedEvent__DelegateSignature
struct UWidget_SessionRow_C_BndEvt__mButton_K2Node_ComponentBoundEvent_120_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_SessionRow_C_BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.Construct
struct UWidget_SessionRow_C_Construct_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.PreConstruct
struct UWidget_SessionRow_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mLoadButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
struct UWidget_SessionRow_C_BndEvt__mLoadButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mDeleteSessionButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
struct UWidget_SessionRow_C_BndEvt__mDeleteSessionButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.ConfirmDeleteSessionPopUp
struct UWidget_SessionRow_C_ConfirmDeleteSessionPopUp_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.Event DeleteSession
struct UWidget_SessionRow_C_Event_DeleteSession_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature
struct UWidget_SessionRow_C_BndEvt__mSessionRowButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_SessionRow.Widget_SessionRow_C.ExecuteUbergraph_Widget_SessionRow
struct UWidget_SessionRow_C_ExecuteUbergraph_Widget_SessionRow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
