#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AreaSelection_Button_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.IsMediaPlayerValid
struct UWidget_AreaSelection_Button_C_IsMediaPlayerValid_Params
{
	bool                                               IsValid;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SetBorderTint
struct UWidget_AreaSelection_Button_C_SetBorderTint_Params
{
	struct FSlateColor                                 Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.DeselectAnim
struct UWidget_AreaSelection_Button_C_DeselectAnim_Params
{
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SelectAnim
struct UWidget_AreaSelection_Button_C_SelectAnim_Params
{
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.SetSelected
struct UWidget_AreaSelection_Button_C_SetSelected_Params
{
	bool                                               isSelected;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.PreConstruct
struct UWidget_AreaSelection_Button_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.Construct
struct UWidget_AreaSelection_Button_C_Construct_Params
{
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_AreaSelection_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_AreaSelection_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_AreaSelection_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.ExecuteUbergraph_Widget_AreaSelection_Button
struct UWidget_AreaSelection_Button_C_ExecuteUbergraph_Widget_AreaSelection_Button_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AreaSelection_Button.Widget_AreaSelection_Button_C.OnClicked__DelegateSignature
struct UWidget_AreaSelection_Button_C_OnClicked__DelegateSignature_Params
{
	TEnumAsByte<EStartingLocations>                    StartingLoc;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
