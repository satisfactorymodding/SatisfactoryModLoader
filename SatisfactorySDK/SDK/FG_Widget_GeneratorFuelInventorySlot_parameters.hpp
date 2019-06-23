#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GeneratorFuelInventorySlot_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C.Init
struct UWidget_GeneratorFuelInventorySlot_C_Init_Params
{
	class AFGBuildableGeneratorFuel*                   Generator;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C.GetFuelPercent
struct UWidget_GeneratorFuelInventorySlot_C_GetFuelPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
