#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CompassObjectResource_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.GetText_1
struct UWidget_CompassObjectResource_C_GetText_1_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnCompassObjectAddedToPanel
struct UWidget_CompassObjectResource_C_OnCompassObjectAddedToPanel_Params
{
	class UCanvasPanelSlot**                           parentSlot;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.Construct
struct UWidget_CompassObjectResource_C_Construct_Params
{
};

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnCompassObjectUpdated
struct UWidget_CompassObjectResource_C_OnCompassObjectUpdated_Params
{
};

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.Tick
struct UWidget_CompassObjectResource_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnObjectCentered
struct UWidget_CompassObjectResource_C_OnObjectCentered_Params
{
	bool*                                              centered;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.ExecuteUbergraph_Widget_CompassObjectResource
struct UWidget_CompassObjectResource_C_ExecuteUbergraph_Widget_CompassObjectResource_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
