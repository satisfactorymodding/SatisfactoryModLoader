#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_LookAngleDiff_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTS_LookAngleDiff.BTS_LookAngleDiff_C.ReceiveTick
struct UBTS_LookAngleDiff_C_ReceiveTick_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTS_LookAngleDiff.BTS_LookAngleDiff_C.ExecuteUbergraph_BTS_LookAngleDiff
struct UBTS_LookAngleDiff_C_ExecuteUbergraph_BTS_LookAngleDiff_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
