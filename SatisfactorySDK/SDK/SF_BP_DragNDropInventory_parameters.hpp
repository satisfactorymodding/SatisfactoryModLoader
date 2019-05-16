#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_DragNDropInventory_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_DragNDropInventory.BP_DragNDropInventory_C.Dragged
struct UBP_DragNDropInventory_C_Dragged_Params
{
	struct FPointerEvent*                              PointerEvent;                                             // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_DragNDropInventory.BP_DragNDropInventory_C.DragCancelled
struct UBP_DragNDropInventory_C_DragCancelled_Params
{
	struct FPointerEvent*                              PointerEvent;                                             // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_DragNDropInventory.BP_DragNDropInventory_C.Drop
struct UBP_DragNDropInventory_C_Drop_Params
{
	struct FPointerEvent*                              PointerEvent;                                             // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_DragNDropInventory.BP_DragNDropInventory_C.ExecuteUbergraph_BP_DragNDropInventory
struct UBP_DragNDropInventory_C_ExecuteUbergraph_BP_DragNDropInventory_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
