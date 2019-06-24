#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_FrontEnd_Button_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetActiveWidgetInSwitcher
struct UWidget_FrontEnd_Button_C_SetActiveWidgetInSwitcher_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ClearListOfSelections
struct UWidget_FrontEnd_Button_C_ClearListOfSelections_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonTextColor
struct UWidget_FrontEnd_Button_C_GetButtonTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonColor
struct UWidget_FrontEnd_Button_C_GetButtonColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetFocused
struct UWidget_FrontEnd_Button_C_SetFocused_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.OnFocusReceived
struct UWidget_FrontEnd_Button_C_OnFocusReceived_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ShowButton
struct UWidget_FrontEnd_Button_C_ShowButton_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.HideButton
struct UWidget_FrontEnd_Button_C_HideButton_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.GetButtonText
struct UWidget_FrontEnd_Button_C_GetButtonText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.Construct
struct UWidget_FrontEnd_Button_C_Construct_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.Destruct
struct UWidget_FrontEnd_Button_C_Destruct_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_FrontEnd_Button_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.BndEvt__PauseMenuButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_FrontEnd_Button_C_BndEvt__PauseMenuButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.PreConstruct
struct UWidget_FrontEnd_Button_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.SetSelected
struct UWidget_FrontEnd_Button_C_SetSelected_Params
{
	bool                                               isSelected;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.ExecuteUbergraph_Widget_FrontEnd_Button
struct UWidget_FrontEnd_Button_C_ExecuteUbergraph_Widget_FrontEnd_Button_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FrontEnd_Button.Widget_FrontEnd_Button_C.OnClicked__DelegateSignature
struct UWidget_FrontEnd_Button_C_OnClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
