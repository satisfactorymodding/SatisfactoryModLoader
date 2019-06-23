#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_Hub_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.FromSecondsToText
struct UWidget_ActorDetails_Hub_C_FromSecondsToText_Params
{
	float                                              Seconds;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Result;                                                   // (Parm, OutParm)
};

// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateInfo
struct UWidget_ActorDetails_Hub_C_UpdateInfo_Params
{
};

// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.Construct
struct UWidget_ActorDetails_Hub_C_Construct_Params
{
};

// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateInfoEvent
struct UWidget_ActorDetails_Hub_C_UpdateInfoEvent_Params
{
};

// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateMAMInfo
struct UWidget_ActorDetails_Hub_C_UpdateMAMInfo_Params
{
};

// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.ExecuteUbergraph_Widget_ActorDetails_Hub
struct UWidget_ActorDetails_Hub_C_ExecuteUbergraph_Widget_ActorDetails_Hub_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
