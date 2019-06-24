#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SelfDrivingController_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SelfDrivingController.BP_SelfDrivingController_C.UserConstructionScript
struct ABP_SelfDrivingController_C_UserConstructionScript_Params
{
};

// Function BP_SelfDrivingController.BP_SelfDrivingController_C.OnPossess
struct ABP_SelfDrivingController_C_OnPossess_Params
{
	class APawn**                                      PossessedPawn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SelfDrivingController.BP_SelfDrivingController_C.OnUnpossess
struct ABP_SelfDrivingController_C_OnUnpossess_Params
{
	class APawn**                                      UnpossessedPawn;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SelfDrivingController.BP_SelfDrivingController_C.ExecuteUbergraph_BP_SelfDrivingController
struct ABP_SelfDrivingController_C_ExecuteUbergraph_BP_SelfDrivingController_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
