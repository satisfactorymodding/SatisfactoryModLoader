#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CrystalStationContainer_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.DropInventorySlotStack
struct UWidget_CrystalStationContainer_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Cleanup
struct UWidget_CrystalStationContainer_C_Cleanup_Params
{
};

// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Destruct
struct UWidget_CrystalStationContainer_C_Destruct_Params
{
};

// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Init
struct UWidget_CrystalStationContainer_C_Init_Params
{
};

// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.Construct
struct UWidget_CrystalStationContainer_C_Construct_Params
{
};

// Function Widget_CrystalStationContainer.Widget_CrystalStationContainer_C.ExecuteUbergraph_Widget_CrystalStationContainer
struct UWidget_CrystalStationContainer_C_ExecuteUbergraph_Widget_CrystalStationContainer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
