#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_CheckNextAttackInPattern_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.PerformConditionCheckAI
struct UBTD_CheckNextAttackInPattern_C_PerformConditionCheckAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.ReceiveExecutionStartAI
struct UBTD_CheckNextAttackInPattern_C_ReceiveExecutionStartAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.ExecuteUbergraph_BTD_CheckNextAttackInPattern
struct UBTD_CheckNextAttackInPattern_C_ExecuteUbergraph_BTD_CheckNextAttackInPattern_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
