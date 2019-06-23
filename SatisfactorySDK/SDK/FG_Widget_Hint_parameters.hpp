#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Hint_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Hint.Widget_Hint_C.PreConstruct
struct UWidget_Hint_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Hint.Widget_Hint_C.Construct
struct UWidget_Hint_C_Construct_Params
{
};

// Function Widget_Hint.Widget_Hint_C.ExecuteUbergraph_Widget_Hint
struct UWidget_Hint_C_ExecuteUbergraph_Widget_Hint_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
