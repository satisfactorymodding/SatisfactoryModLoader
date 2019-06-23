#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_TargetLedgeCheck_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTS_TargetLedgeCheck.BTS_TargetLedgeCheck_C.GetKeyLocation
struct UBTS_TargetLedgeCheck_C_GetKeyLocation_Params
{
	struct FBlackboardKeySelector                      Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FVector                                     Location;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BTS_TargetLedgeCheck.BTS_TargetLedgeCheck_C.ReceiveTickAI
struct UBTS_TargetLedgeCheck_C_ReceiveTickAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTS_TargetLedgeCheck.BTS_TargetLedgeCheck_C.ExecuteUbergraph_BTS_TargetLedgeCheck
struct UBTS_TargetLedgeCheck_C_ExecuteUbergraph_BTS_TargetLedgeCheck_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
