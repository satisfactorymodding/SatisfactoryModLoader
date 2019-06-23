#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ColorPicker.Widget_ColorPicker_C.GetResetButtonVisibility
struct UWidget_ColorPicker_C_GetResetButtonVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.GetOneDimensionalIndex
struct UWidget_ColorPicker_C_GetOneDimensionalIndex_Params
{
	int                                                ColorIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                shadeIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Index;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.GetSavedColorFromIndexes
struct UWidget_ColorPicker_C_GetSavedColorFromIndexes_Params
{
	int                                                ColorIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                shadeIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 SavedColor;                                               // (Parm, OutParm)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.CalculateSaturationAndValueFromIndex
struct UWidget_ColorPicker_C_CalculateSaturationAndValueFromIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Saturation;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.CalculateHueFromIndex
struct UWidget_ColorPicker_C_CalculateHueFromIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Hue;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.FirstTimeFillColors
struct UWidget_ColorPicker_C_FirstTimeFillColors_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.GetFinalColor
struct UWidget_ColorPicker_C_GetFinalColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.CloseColorPicker
struct UWidget_ColorPicker_C_CloseColorPicker_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.Construct
struct UWidget_ColorPicker_C_Construct_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.Init
struct UWidget_ColorPicker_C_Init_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.ExitColorPicker
struct UWidget_ColorPicker_C_ExitColorPicker_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mCancelButton_K2Node_ComponentBoundEvent_36_OnClicked__DelegateSignature
struct UWidget_ColorPicker_C_BndEvt__mCancelButton_K2Node_ComponentBoundEvent_36_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.Tick
struct UWidget_ColorPicker_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mResetButton_K2Node_ComponentBoundEvent_31_OnClicked__DelegateSignature
struct UWidget_ColorPicker_C_BndEvt__mResetButton_K2Node_ComponentBoundEvent_31_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_331_OnClicked__DelegateSignature
struct UWidget_ColorPicker_C_BndEvt__mAcceptButton_K2Node_ComponentBoundEvent_331_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
struct UWidget_ColorPicker_C_BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_ColorPicker_C_BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mReset_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
struct UWidget_ColorPicker_C_BndEvt__mReset_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.BndEvt__mAccept_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UWidget_ColorPicker_C_BndEvt__mAccept_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.ExecuteUbergraph_Widget_ColorPicker
struct UWidget_ColorPicker_C_ExecuteUbergraph_Widget_ColorPicker_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker.Widget_ColorPicker_C.mOnColorPicked__DelegateSignature
struct UWidget_ColorPicker_C_mOnColorPicked__DelegateSignature_Params
{
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
