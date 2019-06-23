#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_PayOffGrid_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.DropInventorySlotStack
struct UWidget_TradingPost_PayOffGrid_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C*                     InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               Result;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.SetUpPayOffSlots
struct UWidget_TradingPost_PayOffGrid_C_SetUpPayOffSlots_Params
{
	class UClass*                                      mSchematic;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.Construct
struct UWidget_TradingPost_PayOffGrid_C_Construct_Params
{
};

// Function Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C.ExecuteUbergraph_Widget_TradingPost_PayOffGrid
struct UWidget_TradingPost_PayOffGrid_C_ExecuteUbergraph_Widget_TradingPost_PayOffGrid_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
