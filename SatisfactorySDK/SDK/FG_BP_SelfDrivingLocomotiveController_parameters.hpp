#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SelfDrivingLocomotiveController_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.UserConstructionScript
struct ABP_SelfDrivingLocomotiveController_C_UserConstructionScript_Params
{
};

// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.ReceiveBeginPlay
struct ABP_SelfDrivingLocomotiveController_C_ReceiveBeginPlay_Params
{
};

// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.OnPossess
struct ABP_SelfDrivingLocomotiveController_C_OnPossess_Params
{
	class APawn**                                      PossessedPawn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.OnUnpossess
struct ABP_SelfDrivingLocomotiveController_C_OnUnpossess_Params
{
	class APawn**                                      UnpossessedPawn;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.ExecuteUbergraph_BP_SelfDrivingLocomotiveController
struct ABP_SelfDrivingLocomotiveController_C_ExecuteUbergraph_BP_SelfDrivingLocomotiveController_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
