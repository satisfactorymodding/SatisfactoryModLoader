#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SwitchButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SwitchButton.Widget_SwitchButton_C.SetIcon
struct UWidget_SwitchButton_C_SetIcon_Params
{
	class UTexture*                                    TextureSending;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UTexture*                                    TextureReceiving;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SwitchButton.Widget_SwitchButton_C.SetButtonBrush
struct UWidget_SwitchButton_C_SetButtonBrush_Params
{
	bool                                               mButtonState;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SwitchButton.Widget_SwitchButton_C.BndEvt__Button_2_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_SwitchButton_C_BndEvt__Button_2_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_SwitchButton.Widget_SwitchButton_C.Construct
struct UWidget_SwitchButton_C_Construct_Params
{
};

// Function Widget_SwitchButton.Widget_SwitchButton_C.PreConstruct
struct UWidget_SwitchButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SwitchButton.Widget_SwitchButton_C.ExecuteUbergraph_Widget_SwitchButton
struct UWidget_SwitchButton_C_ExecuteUbergraph_Widget_SwitchButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SwitchButton.Widget_SwitchButton_C.OnClicked__DelegateSignature
struct UWidget_SwitchButton_C_OnClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
