#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TabButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TabButton.Widget_TabButton_C.GetButtonEnabled
struct UWidget_TabButton_C_GetButtonEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TabButton.Widget_TabButton_C.Construct
struct UWidget_TabButton_C_Construct_Params
{
};

// Function Widget_TabButton.Widget_TabButton_C.OnThisButtonClicked
struct UWidget_TabButton_C_OnThisButtonClicked_Params
{
};

// Function Widget_TabButton.Widget_TabButton_C.ExecuteUbergraph_Widget_TabButton
struct UWidget_TabButton_C_ExecuteUbergraph_Widget_TabButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
