#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_OptionsSlider_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetPercent
struct UWidget_OptionsSlider_C_GetPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.SetNormalizedValue
struct UWidget_OptionsSlider_C_SetNormalizedValue_Params
{
	float                                              CurrentUnadjustedValue;                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetAdjustedValue
struct UWidget_OptionsSlider_C_GetAdjustedValue_Params
{
	float                                              Normalized_Value;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Adjusted_Value;                                           // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.SetProgressBarPercentage
struct UWidget_OptionsSlider_C_SetProgressBarPercentage_Params
{
	float                                              Percent;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetProgressBarPercentage
struct UWidget_OptionsSlider_C_GetProgressBarPercentage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetValueText
struct UWidget_OptionsSlider_C_GetValueText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.BndEvt__OptionSlider_K2Node_ComponentBoundEvent_104_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_OptionsSlider_C_BndEvt__OptionSlider_K2Node_ComponentBoundEvent_104_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.OnRowHovered
struct UWidget_OptionsSlider_C_OnRowHovered_Params
{
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.OnRowUnhovered
struct UWidget_OptionsSlider_C_OnRowUnhovered_Params
{
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.ExecuteUbergraph_Widget_OptionsSlider
struct UWidget_OptionsSlider_C_ExecuteUbergraph_Widget_OptionsSlider_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_OptionsSlider.Widget_OptionsSlider_C.GetNewValue__DelegateSignature
struct UWidget_OptionsSlider_C_GetNewValue__DelegateSignature_Params
{
	float                                              VolumeLevel;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
