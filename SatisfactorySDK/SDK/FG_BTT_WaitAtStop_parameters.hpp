#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_WaitAtStop_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_WaitAtStop.BTT_WaitAtStop_C.ReceiveExecuteAI
struct UBTT_WaitAtStop_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_WaitAtStop.BTT_WaitAtStop_C.Done
struct UBTT_WaitAtStop_C_Done_Params
{
};

// Function BTT_WaitAtStop.BTT_WaitAtStop_C.ExecuteUbergraph_BTT_WaitAtStop
struct UBTT_WaitAtStop_C_ExecuteUbergraph_BTT_WaitAtStop_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
