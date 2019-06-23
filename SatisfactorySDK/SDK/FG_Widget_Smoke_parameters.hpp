#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Smoke_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Smoke.Widget_Smoke_C.Construct
struct UWidget_Smoke_C_Construct_Params
{
};

// Function Widget_Smoke.Widget_Smoke_C.OnAnimEnd
struct UWidget_Smoke_C_OnAnimEnd_Params
{
};

// Function Widget_Smoke.Widget_Smoke_C.Tick
struct UWidget_Smoke_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Smoke.Widget_Smoke_C.PreConstruct
struct UWidget_Smoke_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Smoke.Widget_Smoke_C.ExecuteUbergraph_Widget_Smoke
struct UWidget_Smoke_C_ExecuteUbergraph_Widget_Smoke_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
