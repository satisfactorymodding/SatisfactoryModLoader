#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupContentResolutionTimer_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.GetShouldOkayBeEnabled
struct UWidget_PopupContentResolutionTimer_C_GetShouldOkayBeEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Get_TimerText
struct UWidget_PopupContentResolutionTimer_C_Get_TimerText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Construct
struct UWidget_PopupContentResolutionTimer_C_Construct_Params
{
};

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.TriggerCancel
struct UWidget_PopupContentResolutionTimer_C_TriggerCancel_Params
{
};

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.SetOptionalTextElements
struct UWidget_PopupContentResolutionTimer_C_SetOptionalTextElements_Params
{
	struct FText*                                      Title;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText*                                      Desc;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.Destruct
struct UWidget_PopupContentResolutionTimer_C_Destruct_Params
{
};

// Function Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C.ExecuteUbergraph_Widget_PopupContentResolutionTimer
struct UWidget_PopupContentResolutionTimer_C_ExecuteUbergraph_Widget_PopupContentResolutionTimer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
