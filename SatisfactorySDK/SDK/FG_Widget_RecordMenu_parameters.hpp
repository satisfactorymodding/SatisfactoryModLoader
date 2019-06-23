#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RecordMenu_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RecordMenu.Widget_RecordMenu_C.SetNameAtIndex
struct UWidget_RecordMenu_C_SetNameAtIndex_Params
{
	struct FText                                       Name;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	int                                                Int;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.UpdateLabels
struct UWidget_RecordMenu_C_UpdateLabels_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.GetPositionInCircle
struct UWidget_RecordMenu_C_GetPositionInCircle_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   Translation;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.GetPauseEnabled
struct UWidget_RecordMenu_C_GetPauseEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.Construct
struct UWidget_RecordMenu_C_Construct_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.ToggleRecording
struct UWidget_RecordMenu_C_ToggleRecording_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.Destruct
struct UWidget_RecordMenu_C_Destruct_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.ClearPathRecording
struct UWidget_RecordMenu_C_ClearPathRecording_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.PauseClicked
struct UWidget_RecordMenu_C_PauseClicked_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.AutoPilotClicked
struct UWidget_RecordMenu_C_AutoPilotClicked_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.PathVisibilityClicked
struct UWidget_RecordMenu_C_PathVisibilityClicked_Params
{
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.Tick
struct UWidget_RecordMenu_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RecordMenu.Widget_RecordMenu_C.ExecuteUbergraph_Widget_RecordMenu
struct UWidget_RecordMenu_C_ExecuteUbergraph_Widget_RecordMenu_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
