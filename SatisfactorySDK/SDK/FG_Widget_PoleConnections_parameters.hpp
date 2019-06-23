#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PoleConnections_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PoleConnections.Widget_PoleConnections_C.SetStyle
struct UWidget_PoleConnections_C_SetStyle_Params
{
	bool                                               UseBackground;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PoleConnections.Widget_PoleConnections_C.GetColorAndOpacity_1
struct UWidget_PoleConnections_C_GetColorAndOpacity_1_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PoleConnections.Widget_PoleConnections_C.GetText_1
struct UWidget_PoleConnections_C_GetText_1_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PoleConnections.Widget_PoleConnections_C.Construct
struct UWidget_PoleConnections_C_Construct_Params
{
};

// Function Widget_PoleConnections.Widget_PoleConnections_C.UpdateConnections
struct UWidget_PoleConnections_C_UpdateConnections_Params
{
};

// Function Widget_PoleConnections.Widget_PoleConnections_C.Destruct
struct UWidget_PoleConnections_C_Destruct_Params
{
};

// Function Widget_PoleConnections.Widget_PoleConnections_C.PreConstruct
struct UWidget_PoleConnections_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PoleConnections.Widget_PoleConnections_C.ExecuteUbergraph_Widget_PoleConnections
struct UWidget_PoleConnections_C_ExecuteUbergraph_Widget_PoleConnections_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
