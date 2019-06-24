#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Inventory_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Inventory.Widget_Inventory_C.GetAllInventorySlots
struct UWidget_Inventory_C_GetAllInventorySlots_Params
{
	TArray<class UWidget_InventorySlot_C*>             InventorySlots;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_Inventory.Widget_Inventory_C.GetSqrtOfLinearSize
struct UWidget_Inventory_C_GetSqrtOfLinearSize_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Inventory.Widget_Inventory_C.GetWidth
struct UWidget_Inventory_C_GetWidth_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Inventory.Widget_Inventory_C.CreateAllSlots
struct UWidget_Inventory_C_CreateAllSlots_Params
{
};

// Function Widget_Inventory.Widget_Inventory_C.ClearAllSlots
struct UWidget_Inventory_C_ClearAllSlots_Params
{
};

// Function Widget_Inventory.Widget_Inventory_C.CalcIndex
struct UWidget_Inventory_C_CalcIndex_Params
{
	int                                                X;                                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Y;                                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Width;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                idx;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Inventory.Widget_Inventory_C.CreateSlot
struct UWidget_Inventory_C_CreateSlot_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Row;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                Column;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_InventorySlot_C*                     Result;                                                   // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Inventory.Widget_Inventory_C.Init
struct UWidget_Inventory_C_Init_Params
{
	class UFGInventoryComponent*                       component;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Inventory.Widget_Inventory_C.OnInventoryResized
struct UWidget_Inventory_C_OnInventoryResized_Params
{
	int                                                oldSize;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                newSize;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Inventory.Widget_Inventory_C.Destruct
struct UWidget_Inventory_C_Destruct_Params
{
};

// Function Widget_Inventory.Widget_Inventory_C.ExecuteUbergraph_Widget_Inventory
struct UWidget_Inventory_C_ExecuteUbergraph_Widget_Inventory_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
