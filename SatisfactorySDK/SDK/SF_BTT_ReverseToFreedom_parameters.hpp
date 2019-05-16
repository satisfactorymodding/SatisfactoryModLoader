#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BTT_ReverseToFreedom_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_ReverseToFreedom.BTT_ReverseToFreedom_C.ReverseComplete
struct UBTT_ReverseToFreedom_C_ReverseComplete_Params
{
};

// Function BTT_ReverseToFreedom.BTT_ReverseToFreedom_C.ReceiveExecuteAI
struct UBTT_ReverseToFreedom_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_ReverseToFreedom.BTT_ReverseToFreedom_C.ExecuteUbergraph_BTT_ReverseToFreedom
struct UBTT_ReverseToFreedom_C_ExecuteUbergraph_BTT_ReverseToFreedom_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
