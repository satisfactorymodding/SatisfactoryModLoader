#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HotbarContainer_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.Construct
struct UWidget_HotbarContainer_C_Construct_Params
{
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.Destruct
struct UWidget_HotbarContainer_C_Destruct_Params
{
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnHotbarUpdated
struct UWidget_HotbarContainer_C_OnHotbarUpdated_Params
{
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnHotbarLayoutUpdated
struct UWidget_HotbarContainer_C_OnHotbarLayoutUpdated_Params
{
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.ShowNotification
struct UWidget_HotbarContainer_C_ShowNotification_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.ListenForPurchasedSchematics
struct UWidget_HotbarContainer_C_ListenForPurchasedSchematics_Params
{
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnPurchasedSchematic
struct UWidget_HotbarContainer_C_OnPurchasedSchematic_Params
{
	class UClass*                                      purchasedSchematic;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.StopListenForPurchasedSchematics
struct UWidget_HotbarContainer_C_StopListenForPurchasedSchematics_Params
{
};

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.ExecuteUbergraph_Widget_HotbarContainer
struct UWidget_HotbarContainer_C_ExecuteUbergraph_Widget_HotbarContainer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
