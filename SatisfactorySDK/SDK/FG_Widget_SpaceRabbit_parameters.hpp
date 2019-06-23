#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SpaceRabbit_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.DropInventorySlotStack
struct UWidget_SpaceRabbit_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Cleanup
struct UWidget_SpaceRabbit_C_Cleanup_Params
{
};

// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Init
struct UWidget_SpaceRabbit_C_Init_Params
{
};

// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Construct
struct UWidget_SpaceRabbit_C_Construct_Params
{
};

// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.Destruct
struct UWidget_SpaceRabbit_C_Destruct_Params
{
};

// Function Widget_SpaceRabbit.Widget_SpaceRabbit_C.ExecuteUbergraph_Widget_SpaceRabbit
struct UWidget_SpaceRabbit_C_ExecuteUbergraph_Widget_SpaceRabbit_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
