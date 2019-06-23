#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PowerCircuitStatus_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PowerCircuitStatus.Widget_PowerCircuitStatus_C.IsConnectedVisibility
struct UWidget_PowerCircuitStatus_C_IsConnectedVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PowerCircuitStatus.Widget_PowerCircuitStatus_C.IsConnected
struct UWidget_PowerCircuitStatus_C_IsConnected_Params
{
	bool                                               IsConnected;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PowerCircuitStatus.Widget_PowerCircuitStatus_C.GetCircuitText
struct UWidget_PowerCircuitStatus_C_GetCircuitText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
