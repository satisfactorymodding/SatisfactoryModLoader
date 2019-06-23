#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_KeyBindFocus_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnKeyUp
struct UWidget_KeyBindFocus_C_OnKeyUp_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.HandleInput
struct UWidget_KeyBindFocus_C_HandleInput_Params
{
	struct FInputEvent                                 InputEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FKey                                        keyPressed;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 Handled;                                                  // (Parm, OutParm)
};

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnMouseWheel
struct UWidget_KeyBindFocus_C_OnMouseWheel_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.GetKeyRebindText
struct UWidget_KeyBindFocus_C_GetKeyRebindText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnKeyDown
struct UWidget_KeyBindFocus_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnMouseButtonDown
struct UWidget_KeyBindFocus_C_OnMouseButtonDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.Construct
struct UWidget_KeyBindFocus_C_Construct_Params
{
};

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.ExecuteUbergraph_Widget_KeyBindFocus
struct UWidget_KeyBindFocus_C_ExecuteUbergraph_Widget_KeyBindFocus_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
