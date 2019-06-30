#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_SetLocomotiveBrakes_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_SetLocomotiveBrakes.BTT_SetLocomotiveBrakes_C.ReceiveExecuteAI
struct UBTT_SetLocomotiveBrakes_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_SetLocomotiveBrakes.BTT_SetLocomotiveBrakes_C.ExecuteUbergraph_BTT_SetLocomotiveBrakes
struct UBTT_SetLocomotiveBrakes_C_ExecuteUbergraph_BTT_SetLocomotiveBrakes_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
