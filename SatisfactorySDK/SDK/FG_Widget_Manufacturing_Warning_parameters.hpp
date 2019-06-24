#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Manufacturing_Warning_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.HideWarning
struct UWidget_Manufacturing_Warning_C_HideWarning_Params
{
};

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.UpdateWarning
struct UWidget_Manufacturing_Warning_C_UpdateWarning_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.SetText
struct UWidget_Manufacturing_Warning_C_SetText_Params
{
	struct FText                                       InText;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.GetWarningText
struct UWidget_Manufacturing_Warning_C_GetWarningText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.Construct
struct UWidget_Manufacturing_Warning_C_Construct_Params
{
};

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.PreConstruct
struct UWidget_Manufacturing_Warning_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing_Warning.Widget_Manufacturing_Warning_C.ExecuteUbergraph_Widget_Manufacturing_Warning
struct UWidget_Manufacturing_Warning_C_ExecuteUbergraph_Widget_Manufacturing_Warning_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
