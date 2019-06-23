#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InviteNotification_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_InviteNotification.Widget_InviteNotification_C.Construct
struct UWidget_InviteNotification_C_Construct_Params
{
};

// Function Widget_InviteNotification.Widget_InviteNotification_C.OnInviteReceived
struct UWidget_InviteNotification_C_OnInviteReceived_Params
{
	struct FPendingInvite                              receivedInvite;                                           // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_InviteNotification.Widget_InviteNotification_C.ExecuteUbergraph_Widget_InviteNotification
struct UWidget_InviteNotification_C_ExecuteUbergraph_Widget_InviteNotification_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
