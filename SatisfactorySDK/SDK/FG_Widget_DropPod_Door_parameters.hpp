#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_DropPod_Door_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetHasBeenOpened
struct UWidget_DropPod_Door_C_SetHasBeenOpened_Params
{
	bool                                               HasBeenOpened;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetLEDVisibility
struct UWidget_DropPod_Door_C_SetLEDVisibility_Params
{
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetHandleAngle
struct UWidget_DropPod_Door_C_SetHandleAngle_Params
{
	float                                              Angle;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.Construct
struct UWidget_DropPod_Door_C_Construct_Params
{
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.Tick
struct UWidget_DropPod_Door_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_DropPod_Door_C_BndEvt__Slider_0_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__HandleSlider_K2Node_ComponentBoundEvent_1_OnMouseCaptureEndEvent__DelegateSignature
struct UWidget_DropPod_Door_C_BndEvt__HandleSlider_K2Node_ComponentBoundEvent_1_OnMouseCaptureEndEvent__DelegateSignature_Params
{
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__HandleSlider_K2Node_ComponentBoundEvent_2_OnControllerCaptureEndEvent__DelegateSignature
struct UWidget_DropPod_Door_C_BndEvt__HandleSlider_K2Node_ComponentBoundEvent_2_OnControllerCaptureEndEvent__DelegateSignature_Params
{
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.OnDoorOpen_Event
struct UWidget_DropPod_Door_C_OnDoorOpen_Event_Params
{
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.Destruct
struct UWidget_DropPod_Door_C_Destruct_Params
{
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.ExecuteUbergraph_Widget_DropPod_Door
struct UWidget_DropPod_Door_C_ExecuteUbergraph_Widget_DropPod_Door_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.OnDoorOpen__DelegateSignature
struct UWidget_DropPod_Door_C_OnDoorOpen__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
