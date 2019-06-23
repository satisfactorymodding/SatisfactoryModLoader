#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_WalkBackSlowly_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ReceiveExecute
struct UBTT_WalkBackSlowly_C_ReceiveExecute_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.WalkBackComplete
struct UBTT_WalkBackSlowly_C_WalkBackComplete_Params
{
};

// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ReceiveAbort
struct UBTT_WalkBackSlowly_C_ReceiveAbort_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_WalkBackSlowly.BTT_WalkBackSlowly_C.ExecuteUbergraph_BTT_WalkBackSlowly
struct UBTT_WalkBackSlowly_C_ExecuteUbergraph_BTT_WalkBackSlowly_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
