#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AudioMessage_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_AudioMessage.Widget_AudioMessage_C.SetSenderInfo
struct UWidget_AudioMessage_C_SetSenderInfo_Params
{
	class UClass*                                      inSender;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AudioMessage.Widget_AudioMessage_C.GetDarkGray
struct UWidget_AudioMessage_C_GetDarkGray_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_AudioMessage.Widget_AudioMessage_C.PlayNextDialogue
struct UWidget_AudioMessage_C_PlayNextDialogue_Params
{
};

// Function Widget_AudioMessage.Widget_AudioMessage_C.Construct
struct UWidget_AudioMessage_C_Construct_Params
{
};

// Function Widget_AudioMessage.Widget_AudioMessage_C.ShowContent
struct UWidget_AudioMessage_C_ShowContent_Params
{
};

// Function Widget_AudioMessage.Widget_AudioMessage_C.Destruct
struct UWidget_AudioMessage_C_Destruct_Params
{
};

// Function Widget_AudioMessage.Widget_AudioMessage_C.ExecuteUbergraph_Widget_AudioMessage
struct UWidget_AudioMessage_C_ExecuteUbergraph_Widget_AudioMessage_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
