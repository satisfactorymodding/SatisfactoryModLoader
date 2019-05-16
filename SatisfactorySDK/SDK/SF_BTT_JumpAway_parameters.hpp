#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BTT_JumpAway_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_JumpAway.BTT_JumpAway_C.ReceiveExecuteAI
struct UBTT_JumpAway_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_JumpAway.BTT_JumpAway_C.BirdHasLanded
struct UBTT_JumpAway_C_BirdHasLanded_Params
{
	class AChar_NonFlyingBird_C*                       birdLanded;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_JumpAway.BTT_JumpAway_C.ExecuteUbergraph_BTT_JumpAway
struct UBTT_JumpAway_C_ExecuteUbergraph_BTT_JumpAway_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
