#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ChatWindow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ChatWindow.Widget_ChatWindow_C.ExitChat
struct UWidget_ChatWindow_C_ExitChat_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.OnPlayerBeginTypeMessage
struct UWidget_ChatWindow_C_OnPlayerBeginTypeMessage_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.UpdateVisibility
struct UWidget_ChatWindow_C_UpdateVisibility_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.OnChatMessageReceived
struct UWidget_ChatWindow_C_OnChatMessageReceived_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.SetInputWindowVisibility
struct UWidget_ChatWindow_C_SetInputWindowVisibility_Params
{
	bool                                               Visible;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.GetInputWindowVisibility
struct UWidget_ChatWindow_C_GetInputWindowVisibility_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.CacheChatMessages
struct UWidget_ChatWindow_C_CacheChatMessages_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.IsLastMessageFresh
struct UWidget_ChatWindow_C_IsLastMessageFresh_Params
{
	bool                                               IsFresh;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.RemoveMessageWidget
struct UWidget_ChatWindow_C_RemoveMessageWidget_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.AddMessageWidget
struct UWidget_ChatWindow_C_AddMessageWidget_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.MatchWidgetsAndMessages
struct UWidget_ChatWindow_C_MatchWidgetsAndMessages_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.Construct
struct UWidget_ChatWindow_C_Construct_Params
{
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.OnRemovedFromFocusPath
struct UWidget_ChatWindow_C_OnRemovedFromFocusPath_Params
{
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.OnMouseEnter
struct UWidget_ChatWindow_C_OnMouseEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.OnMouseLeave
struct UWidget_ChatWindow_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ChatWindow.Widget_ChatWindow_C.ExecuteUbergraph_Widget_ChatWindow
struct UWidget_ChatWindow_C_ExecuteUbergraph_Widget_ChatWindow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
