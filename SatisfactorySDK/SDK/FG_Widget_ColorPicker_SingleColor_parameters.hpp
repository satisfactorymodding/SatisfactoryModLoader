#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_SingleColor_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.SetupStartColor
struct UWidget_ColorPicker_SingleColor_C_SetupStartColor_Params
{
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.PreConstruct
struct UWidget_ColorPicker_SingleColor_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_ColorPicker_SingleColor_C_BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_ColorPicker_SingleColor_C_BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.ExecuteUbergraph_Widget_ColorPicker_SingleColor
struct UWidget_ColorPicker_SingleColor_C_ExecuteUbergraph_Widget_ColorPicker_SingleColor_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_SingleColor.Widget_ColorPicker_SingleColor_C.OnClose__DelegateSignature
struct UWidget_ColorPicker_SingleColor_C_OnClose__DelegateSignature_Params
{
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
