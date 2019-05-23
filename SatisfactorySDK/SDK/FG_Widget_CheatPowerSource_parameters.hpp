#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CheatPowerSource_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.OnGetPowerCircuit
struct UWidget_CheatPowerSource_C_OnGetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.SetDynamicPowerSliderValue
struct UWidget_CheatPowerSource_C_SetDynamicPowerSliderValue_Params
{
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.SetBasePowerSliderValue
struct UWidget_CheatPowerSource_C_SetBasePowerSliderValue_Params
{
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetTotalProductionText
struct UWidget_CheatPowerSource_C_GetTotalProductionText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsagePercentColor
struct UWidget_CheatPowerSource_C_GetDynamicUsagePercentColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsageText
struct UWidget_CheatPowerSource_C_GetDynamicUsageText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicUsagePercent
struct UWidget_CheatPowerSource_C_GetDynamicUsagePercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetBasePowerText
struct UWidget_CheatPowerSource_C_GetBasePowerText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.GetDynamicPowerText
struct UWidget_CheatPowerSource_C_GetDynamicPowerText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_CheatPowerSource_C_BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.BndEvt__mDynamicPowerSlider_K2Node_ComponentBoundEvent_233_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_CheatPowerSource_C_BndEvt__mDynamicPowerSlider_K2Node_ComponentBoundEvent_233_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.Init
struct UWidget_CheatPowerSource_C_Init_Params
{
};

// Function Widget_CheatPowerSource.Widget_CheatPowerSource_C.ExecuteUbergraph_Widget_CheatPowerSource
struct UWidget_CheatPowerSource_C_ExecuteUbergraph_Widget_CheatPowerSource_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
