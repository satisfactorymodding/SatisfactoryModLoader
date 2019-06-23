#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActiveSchematicContainer_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.GetPodTimerText
struct UWidget_ActiveSchematicContainer_C_GetPodTimerText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShowPodTimerText
struct UWidget_ActiveSchematicContainer_C_ShowPodTimerText_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.RemoveSchematicCostWidget
struct UWidget_ActiveSchematicContainer_C_RemoveSchematicCostWidget_Params
{
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.AddSchematicCostWidget
struct UWidget_ActiveSchematicContainer_C_AddSchematicCostWidget_Params
{
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.MatchWidgetWithSchematicCost
struct UWidget_ActiveSchematicContainer_C_MatchWidgetWithSchematicCost_Params
{
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShowSchematicWidget
struct UWidget_ActiveSchematicContainer_C_ShowSchematicWidget_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShouldShowSchematic
struct UWidget_ActiveSchematicContainer_C_ShouldShowSchematic_Params
{
	bool                                               ShouldShow;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.GetSchematicName
struct UWidget_ActiveSchematicContainer_C_GetSchematicName_Params
{
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.Construct
struct UWidget_ActiveSchematicContainer_C_Construct_Params
{
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.UpdateSchematic
struct UWidget_ActiveSchematicContainer_C_UpdateSchematic_Params
{
	class UClass*                                      activeSchematic;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ExecuteUbergraph_Widget_ActiveSchematicContainer
struct UWidget_ActiveSchematicContainer_C_ExecuteUbergraph_Widget_ActiveSchematicContainer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
