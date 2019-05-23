#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_Container_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateNotifications
struct UWidget_Codex_Container_C_UpdateNotifications_Params
{
	class UWidget_CodexButton_C*                       forButton;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.OnFilterButtonPressed
struct UWidget_Codex_Container_C_OnFilterButtonPressed_Params
{
	class UWidget_CodexButton_C*                       ButtonPressed;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.SelectButtonWithMessage
struct UWidget_Codex_Container_C_SelectButtonWithMessage_Params
{
	class UClass*                                      inMessage;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.CheckShouldOpenMessage
struct UWidget_Codex_Container_C_CheckShouldOpenMessage_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateMessageText
struct UWidget_Codex_Container_C_UpdateMessageText_Params
{
	struct FText                                       senderMail;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       Sender;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.PopulateList
struct UWidget_Codex_Container_C_PopulateList_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.GetActiveTabFeedback
struct UWidget_Codex_Container_C_GetActiveTabFeedback_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.GetMessageVisiblity
struct UWidget_Codex_Container_C_GetMessageVisiblity_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.Construct
struct UWidget_Codex_Container_C_Construct_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.CloseCodex
struct UWidget_Codex_Container_C_CloseCodex_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.Tick
struct UWidget_Codex_Container_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.MarkAllAsRead
struct UWidget_Codex_Container_C_MarkAllAsRead_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.ExecuteUbergraph_Widget_Codex_Container
struct UWidget_Codex_Container_C_ExecuteUbergraph_Widget_Codex_Container_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
