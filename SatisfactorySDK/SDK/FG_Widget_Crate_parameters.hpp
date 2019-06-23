#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Crate_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Crate.Widget_Crate_C.DropInventorySlotStack
struct UWidget_Crate_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Crate.Widget_Crate_C.Cleanup
struct UWidget_Crate_C_Cleanup_Params
{
};

// Function Widget_Crate.Widget_Crate_C.Init
struct UWidget_Crate_C_Init_Params
{
};

// Function Widget_Crate.Widget_Crate_C.Tick
struct UWidget_Crate_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Crate.Widget_Crate_C.Construct
struct UWidget_Crate_C_Construct_Params
{
};

// Function Widget_Crate.Widget_Crate_C.Destruct
struct UWidget_Crate_C_Destruct_Params
{
};

// Function Widget_Crate.Widget_Crate_C.OnGrabAll
struct UWidget_Crate_C_OnGrabAll_Params
{
};

// Function Widget_Crate.Widget_Crate_C.ExecuteUbergraph_Widget_Crate
struct UWidget_Crate_C_ExecuteUbergraph_Widget_Crate_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
