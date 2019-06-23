#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ChatMessageRow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.SetTextMessage
struct UWidget_ChatMessageRow_C_SetTextMessage_Params
{
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.SetPlayerNameColor
struct UWidget_ChatMessageRow_C_SetPlayerNameColor_Params
{
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.SetPlayerIconColor
struct UWidget_ChatMessageRow_C_SetPlayerIconColor_Params
{
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.SetPlayerName
struct UWidget_ChatMessageRow_C_SetPlayerName_Params
{
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.GetPlayerNameColor
struct UWidget_ChatMessageRow_C_GetPlayerNameColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.GetPlayerName
struct UWidget_ChatMessageRow_C_GetPlayerName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.GetChatText
struct UWidget_ChatMessageRow_C_GetChatText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.Construct
struct UWidget_ChatMessageRow_C_Construct_Params
{
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.RemoveWidgetAfterDelay
struct UWidget_ChatMessageRow_C_RemoveWidgetAfterDelay_Params
{
	float                                              Delay;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ChatMessageRow.Widget_ChatMessageRow_C.ExecuteUbergraph_Widget_ChatMessageRow
struct UWidget_ChatMessageRow_C_ExecuteUbergraph_Widget_ChatMessageRow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
