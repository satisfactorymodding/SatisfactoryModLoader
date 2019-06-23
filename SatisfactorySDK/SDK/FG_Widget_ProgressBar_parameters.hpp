#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ProgressBar_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ProgressBar.Widget_ProgressBar_C.GetCurveType
struct UWidget_ProgressBar_C_GetCurveType_Params
{
	class UCurveFloat*                                 Curve;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ProgressBar.Widget_ProgressBar_C.SetProgressBarFillColor
struct UWidget_ProgressBar_C_SetProgressBarFillColor_Params
{
	float                                              InputValue;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ProgressBar.Widget_ProgressBar_C.LerpBar
struct UWidget_ProgressBar_C_LerpBar_Params
{
	float                                              StartValue;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              EndValue;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              LerpTime;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ProgressBar.Widget_ProgressBar_C.PreConstruct
struct UWidget_ProgressBar_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ProgressBar.Widget_ProgressBar_C.ExecuteUbergraph_Widget_ProgressBar
struct UWidget_ProgressBar_C_ExecuteUbergraph_Widget_ProgressBar_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
