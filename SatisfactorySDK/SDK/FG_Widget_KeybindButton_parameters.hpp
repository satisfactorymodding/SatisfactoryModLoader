#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_KeybindButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_KeybindButton.Widget_KeybindButton_C.UpdateKeyMapping
struct UWidget_KeybindButton_C_UpdateKeyMapping_Params
{
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.RebindKey
struct UWidget_KeybindButton_C_RebindKey_Params
{
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.KeyBindingOverrideConfirmed
struct UWidget_KeybindButton_C_KeyBindingOverrideConfirmed_Params
{
	bool                                               Confirmed;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.GetHoverColor
struct UWidget_KeybindButton_C_GetHoverColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.HandleInput
struct UWidget_KeybindButton_C_HandleInput_Params
{
	struct FInputEvent                                 InputEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FKey                                        keyPressed;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.Construct
struct UWidget_KeybindButton_C_Construct_Params
{
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_25_OnButtonClickedEvent__DelegateSignature
struct UWidget_KeybindButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_25_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonReleasedEvent__DelegateSignature
struct UWidget_KeybindButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonReleasedEvent__DelegateSignature_Params
{
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_KeybindButton_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.ShowKeyBindWidget
struct UWidget_KeybindButton_C_ShowKeyBindWidget_Params
{
};

// Function Widget_KeybindButton.Widget_KeybindButton_C.ExecuteUbergraph_Widget_KeybindButton
struct UWidget_KeybindButton_C_ExecuteUbergraph_Widget_KeybindButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
