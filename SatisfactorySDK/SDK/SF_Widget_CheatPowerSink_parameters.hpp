#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CheatPowerSink_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.OnGetPowerCircuit
struct UWidget_CheatPowerSink_C_OnGetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.SetPowerSliderValue
struct UWidget_CheatPowerSink_C_SetPowerSliderValue_Params
{
};

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.GetActualPowerText
struct UWidget_CheatPowerSink_C_GetActualPowerText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.GetPowerText
struct UWidget_CheatPowerSink_C_GetPowerText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_CheatPowerSink_C_BndEvt__mPowerSlider_K2Node_ComponentBoundEvent_92_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.Init
struct UWidget_CheatPowerSink_C_Init_Params
{
};

// Function Widget_CheatPowerSink.Widget_CheatPowerSink_C.ExecuteUbergraph_Widget_CheatPowerSink
struct UWidget_CheatPowerSink_C_ExecuteUbergraph_Widget_CheatPowerSink_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
