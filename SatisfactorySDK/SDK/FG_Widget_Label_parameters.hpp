#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Label_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Label.Widget_Label_C.SetLabelText
struct UWidget_Label_C_SetLabelText_Params
{
	struct FText                                       LabelText;                                                // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Label.Widget_Label_C.PreConstruct
struct UWidget_Label_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Label.Widget_Label_C.ExecuteUbergraph_Widget_Label
struct UWidget_Label_C_ExecuteUbergraph_Widget_Label_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
