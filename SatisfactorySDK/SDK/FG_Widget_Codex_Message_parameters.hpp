#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_Message_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Codex_Message.Widget_Codex_Message_C.ClearMessage
struct UWidget_Codex_Message_C_ClearMessage_Params
{
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.GenerateAudioMessage
struct UWidget_Codex_Message_C_GenerateAudioMessage_Params
{
	class UClass*                                      inClass;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Text;                                                     // (Parm, OutParm)
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.GetAttachedFilesVisibility
struct UWidget_Codex_Message_C_GetAttachedFilesVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.GetScrollButtonVisibility
struct UWidget_Codex_Message_C_GetScrollButtonVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.SetupImage
struct UWidget_Codex_Message_C_SetupImage_Params
{
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.Construct
struct UWidget_Codex_Message_C_Construct_Params
{
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.AddContent
struct UWidget_Codex_Message_C_AddContent_Params
{
	class UClass*                                      contentClass;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.BndEvt__mScrollButton_K2Node_ComponentBoundEvent_40_OnClicked__DelegateSignature
struct UWidget_Codex_Message_C_BndEvt__mScrollButton_K2Node_ComponentBoundEvent_40_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_Codex_Message_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_Codex_Message.Widget_Codex_Message_C.ExecuteUbergraph_Widget_Codex_Message
struct UWidget_Codex_Message_C_ExecuteUbergraph_Widget_Codex_Message_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
