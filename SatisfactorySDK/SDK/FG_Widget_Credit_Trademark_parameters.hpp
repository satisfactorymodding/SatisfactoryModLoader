#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Credit_Trademark_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.ShowHideText
struct UWidget_Credit_Trademark_C_ShowHideText_Params
{
};

// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.SetText
struct UWidget_Credit_Trademark_C_SetText_Params
{
	struct FText                                       mText;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.PreConstruct
struct UWidget_Credit_Trademark_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.Construct
struct UWidget_Credit_Trademark_C_Construct_Params
{
};

// Function Widget_Credit_Trademark.Widget_Credit_Trademark_C.ExecuteUbergraph_Widget_Credit_Trademark
struct UWidget_Credit_Trademark_C_ExecuteUbergraph_Widget_Credit_Trademark_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
