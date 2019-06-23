#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_EnemyController_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_EnemyController.BP_EnemyController_C.UserConstructionScript
struct ABP_EnemyController_C_UserConstructionScript_Params
{
};

// Function BP_EnemyController.BP_EnemyController_C.OnPossess
struct ABP_EnemyController_C_OnPossess_Params
{
	class APawn**                                      PossessedPawn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_EnemyController.BP_EnemyController_C.OnAggroTargetLost
struct ABP_EnemyController_C_OnAggroTargetLost_Params
{
	class AActor**                                     lostActor;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_EnemyController.BP_EnemyController_C.ExecuteUbergraph_BP_EnemyController
struct ABP_EnemyController_C_ExecuteUbergraph_BP_EnemyController_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
