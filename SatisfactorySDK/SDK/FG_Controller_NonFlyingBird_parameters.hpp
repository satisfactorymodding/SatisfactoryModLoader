#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_NonFlyingBird_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.UserConstructionScript
struct AController_NonFlyingBird_C_UserConstructionScript_Params
{
};

// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.OnPossess
struct AController_NonFlyingBird_C_OnPossess_Params
{
	class APawn**                                      PossessedPawn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.TryToJump
struct AController_NonFlyingBird_C_TryToJump_Params
{
};

// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature
struct AController_NonFlyingBird_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature_Params
{
	class AActor*                                      Actor;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FAIStimulus                                 Stimulus;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.StartPanic
struct AController_NonFlyingBird_C_StartPanic_Params
{
};

// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.ExecuteUbergraph_Controller_NonFlyingBird
struct AController_NonFlyingBird_C_ExecuteUbergraph_Controller_NonFlyingBird_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
