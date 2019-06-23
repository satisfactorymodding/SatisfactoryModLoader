#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_SpaceGiraffe_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Controller_SpaceGiraffe.Controller_SpaceGiraffe_C.UserConstructionScript
struct AController_SpaceGiraffe_C_UserConstructionScript_Params
{
};

// Function Controller_SpaceGiraffe.Controller_SpaceGiraffe_C.OnPossess
struct AController_SpaceGiraffe_C_OnPossess_Params
{
	class APawn**                                      PossessedPawn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_SpaceGiraffe.Controller_SpaceGiraffe_C.ReceiveBeginPlay
struct AController_SpaceGiraffe_C_ReceiveBeginPlay_Params
{
};

// Function Controller_SpaceGiraffe.Controller_SpaceGiraffe_C.StartPanic
struct AController_SpaceGiraffe_C_StartPanic_Params
{
};

// Function Controller_SpaceGiraffe.Controller_SpaceGiraffe_C.StopPanic
struct AController_SpaceGiraffe_C_StopPanic_Params
{
};

// Function Controller_SpaceGiraffe.Controller_SpaceGiraffe_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_2_ActorPerceptionUpdatedDelegate__DelegateSignature
struct AController_SpaceGiraffe_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_2_ActorPerceptionUpdatedDelegate__DelegateSignature_Params
{
	class AActor*                                      Actor;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FAIStimulus                                 Stimulus;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Controller_SpaceGiraffe.Controller_SpaceGiraffe_C.ExecuteUbergraph_Controller_SpaceGiraffe
struct AController_SpaceGiraffe_C_ExecuteUbergraph_Controller_SpaceGiraffe_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
