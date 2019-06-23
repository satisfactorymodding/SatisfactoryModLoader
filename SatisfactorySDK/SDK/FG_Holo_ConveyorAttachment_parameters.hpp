#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Holo_ConveyorAttachment_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.UserConstructionScript
struct AHolo_ConveyorAttachment_C_UserConstructionScript_Params
{
};

// Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.ReceiveConfigureComponents
struct AHolo_ConveyorAttachment_C_ReceiveConfigureComponents_Params
{
	class AFGBuildable**                               inBuildable;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.ExecuteUbergraph_Holo_ConveyorAttachment
struct AHolo_ConveyorAttachment_C_ExecuteUbergraph_Holo_ConveyorAttachment_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
