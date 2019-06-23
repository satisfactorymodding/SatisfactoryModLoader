#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Popup_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Popup.Widget_Popup_C.CancelClicked
struct UWidget_Popup_C_CancelClicked_Params
{
};

// Function Widget_Popup.Widget_Popup_C.OkClicked
struct UWidget_Popup_C_OkClicked_Params
{
};

// Function Widget_Popup.Widget_Popup_C.CheckButtonState
struct UWidget_Popup_C_CheckButtonState_Params
{
};

// Function Widget_Popup.Widget_Popup_C.OnKeyUp
struct UWidget_Popup_C_OnKeyUp_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Popup.Widget_Popup_C.DoClosePopup
struct UWidget_Popup_C_DoClosePopup_Params
{
	bool                                               ConfirmClicked;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Popup.Widget_Popup_C.Init
struct UWidget_Popup_C_Init_Params
{
};

// Function Widget_Popup.Widget_Popup_C.Construct
struct UWidget_Popup_C_Construct_Params
{
};

// Function Widget_Popup.Widget_Popup_C.Tick
struct UWidget_Popup_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Popup.Widget_Popup_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_Popup_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Popup.Widget_Popup_C.ExecuteUbergraph_Widget_Popup
struct UWidget_Popup_C_ExecuteUbergraph_Widget_Popup_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
