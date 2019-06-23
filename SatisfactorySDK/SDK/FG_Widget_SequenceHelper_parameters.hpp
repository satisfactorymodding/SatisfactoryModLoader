#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SequenceHelper_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SequenceHelper.Widget_SequenceHelper_C.OnKeyDown
struct UWidget_SequenceHelper_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SequenceHelper.Widget_SequenceHelper_C.Construct
struct UWidget_SequenceHelper_C_Construct_Params
{
};

// Function Widget_SequenceHelper.Widget_SequenceHelper_C.Destruct
struct UWidget_SequenceHelper_C_Destruct_Params
{
};

// Function Widget_SequenceHelper.Widget_SequenceHelper_C.OnClickedWithRef_Event_1
struct UWidget_SequenceHelper_C_OnClickedWithRef_Event_1_Params
{
	class UWidget_Button_C*                            ClickedButton;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SequenceHelper.Widget_SequenceHelper_C.CustomEvent_1
struct UWidget_SequenceHelper_C_CustomEvent_1_Params
{
};

// Function Widget_SequenceHelper.Widget_SequenceHelper_C.ExecuteUbergraph_Widget_SequenceHelper
struct UWidget_SequenceHelper_C_ExecuteUbergraph_Widget_SequenceHelper_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
