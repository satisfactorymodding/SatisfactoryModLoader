#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Lever_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Lever.Widget_Lever_C.LeverShake
struct UWidget_Lever_C_LeverShake_Params
{
	int                                                MaxOrMinSelectionIndex;                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.OnShake
struct UWidget_Lever_C_OnShake_Params
{
};

// Function Widget_Lever.Widget_Lever_C.SetShowButton
struct UWidget_Lever_C_SetShowButton_Params
{
	bool                                               ShowButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.StartLerp
struct UWidget_Lever_C_StartLerp_Params
{
};

// Function Widget_Lever.Widget_Lever_C.GetCurrentSelectionPosOnSlider
struct UWidget_Lever_C_GetCurrentSelectionPosOnSlider_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.GetCalculatedCurve
struct UWidget_Lever_C_GetCalculatedCurve_Params
{
	class UCurveFloat*                                 CurveFloat;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              InTime;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.GetSliderMinClamp
struct UWidget_Lever_C_GetSliderMinClamp_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.GetSliderMaxClamp
struct UWidget_Lever_C_GetSliderMaxClamp_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.SetHandle
struct UWidget_Lever_C_SetHandle_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.PreConstruct
struct UWidget_Lever_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.Construct
struct UWidget_Lever_C_Construct_Params
{
};

// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_3_OnMouseCaptureEndEvent__DelegateSignature
struct UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_3_OnMouseCaptureEndEvent__DelegateSignature_Params
{
};

// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_4_OnControllerCaptureEndEvent__DelegateSignature
struct UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_4_OnControllerCaptureEndEvent__DelegateSignature_Params
{
};

// Function Widget_Lever.Widget_Lever_C.LerpLever
struct UWidget_Lever_C_LerpLever_Params
{
};

// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_5_OnMouseCaptureBeginEvent__DelegateSignature
struct UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_5_OnMouseCaptureBeginEvent__DelegateSignature_Params
{
};

// Function Widget_Lever.Widget_Lever_C.BndEvt__LeverHandle_K2Node_ComponentBoundEvent_6_OnControllerCaptureBeginEvent__DelegateSignature
struct UWidget_Lever_C_BndEvt__LeverHandle_K2Node_ComponentBoundEvent_6_OnControllerCaptureBeginEvent__DelegateSignature_Params
{
};

// Function Widget_Lever.Widget_Lever_C.ExecuteUbergraph_Widget_Lever
struct UWidget_Lever_C_ExecuteUbergraph_Widget_Lever_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Lever.Widget_Lever_C.OnNewSelection__DelegateSignature
struct UWidget_Lever_C_OnNewSelection__DelegateSignature_Params
{
	int                                                SelectionIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
