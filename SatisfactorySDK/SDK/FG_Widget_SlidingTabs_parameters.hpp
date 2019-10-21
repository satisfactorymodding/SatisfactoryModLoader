#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SlidingTabs_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetActiveButton
struct UWidget_SlidingTabs_C_SetActiveButton_Params
{
};

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetupIndexOffset
struct UWidget_SlidingTabs_C_SetupIndexOffset_Params
{
};

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetActiveIndex
struct UWidget_SlidingTabs_C_SetActiveIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               Animate;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.Construct
struct UWidget_SlidingTabs_C_Construct_Params
{
};

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SlideLerp
struct UWidget_SlidingTabs_C_SlideLerp_Params
{
};

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.PreConstruct
struct UWidget_SlidingTabs_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.ExecuteUbergraph_Widget_SlidingTabs
struct UWidget_SlidingTabs_C_ExecuteUbergraph_Widget_SlidingTabs_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
