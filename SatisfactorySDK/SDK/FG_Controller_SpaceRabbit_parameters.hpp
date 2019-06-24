#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_SpaceRabbit_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.isThreat
struct AController_SpaceRabbit_C_isThreat_Params
{
	struct FName                                       inTag;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               isThreat;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.ReactToSound
struct AController_SpaceRabbit_C_ReactToSound_Params
{
	class AActor*                                      inActor;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     soundLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       Tag;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               didReact;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.SetNewThreat
struct AController_SpaceRabbit_C_SetNewThreat_Params
{
	class AFGCharacterPlayer*                          newThreat;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.GetCurrentThreat
struct AController_SpaceRabbit_C_GetCurrentThreat_Params
{
	class AFGCharacterPlayer*                          outThreat;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.UserConstructionScript
struct AController_SpaceRabbit_C_UserConstructionScript_Params
{
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.OnPossess
struct AController_SpaceRabbit_C_OnPossess_Params
{
	class APawn**                                      PossessedPawn;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature
struct AController_SpaceRabbit_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature_Params
{
	class AActor*                                      Actor;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FAIStimulus                                 Stimulus;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.StartPanic
struct AController_SpaceRabbit_C_StartPanic_Params
{
};

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.ExecuteUbergraph_Controller_SpaceRabbit
struct AController_SpaceRabbit_C_ExecuteUbergraph_Controller_SpaceRabbit_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
