#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Window_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Window.Widget_Window_C.GetDividerButtonSlotVisibility
struct UWidget_Window_C_GetDividerButtonSlotVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.GetNavigationVisibiliy
struct UWidget_Window_C_GetNavigationVisibiliy_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.GetCloseButtonVisibility
struct UWidget_Window_C_GetCloseButtonVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.GetInventoryBodyVisibility
struct UWidget_Window_C_GetInventoryBodyVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.GetTopButtonSlotVisibility
struct UWidget_Window_C_GetTopButtonSlotVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.OnDrop
struct UWidget_Window_C_OnDrop_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.SetTitle
struct UWidget_Window_C_SetTitle_Params
{
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Window.Widget_Window_C.Construct
struct UWidget_Window_C_Construct_Params
{
};

// Function Widget_Window.Widget_Window_C.OnEscapePressed
struct UWidget_Window_C_OnEscapePressed_Params
{
};

// Function Widget_Window.Widget_Window_C.Destruct
struct UWidget_Window_C_Destruct_Params
{
};

// Function Widget_Window.Widget_Window_C.BndEvt__mCloseButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_Window_C_BndEvt__mCloseButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Window.Widget_Window_C.Tick
struct UWidget_Window_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.OnConstructAnimFinished
struct UWidget_Window_C_OnConstructAnimFinished_Params
{
};

// Function Widget_Window.Widget_Window_C.ExecuteUbergraph_Widget_Window
struct UWidget_Window_C_ExecuteUbergraph_Widget_Window_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Window.Widget_Window_C.OnClose__DelegateSignature
struct UWidget_Window_C_OnClose__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
