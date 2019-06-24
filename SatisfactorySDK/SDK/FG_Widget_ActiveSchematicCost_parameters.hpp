#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActiveSchematicCost_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.GetNumIngredientsPaidOff
struct UWidget_ActiveSchematicCost_C_GetNumIngredientsPaidOff_Params
{
	int                                                NumItems;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.GetIngredient
struct UWidget_ActiveSchematicCost_C_GetIngredient_Params
{
	struct FItemAmount                                 ingredient;                                               // (Parm, OutParm)
};

// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.UpdateTimer
struct UWidget_ActiveSchematicCost_C_UpdateTimer_Params
{
};

// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.Construct
struct UWidget_ActiveSchematicCost_C_Construct_Params
{
};

// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.Destruct
struct UWidget_ActiveSchematicCost_C_Destruct_Params
{
};

// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.ExecuteUbergraph_Widget_ActiveSchematicCost
struct UWidget_ActiveSchematicCost_C_ExecuteUbergraph_Widget_ActiveSchematicCost_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
