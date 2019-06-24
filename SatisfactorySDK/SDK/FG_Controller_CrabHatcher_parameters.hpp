#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_CrabHatcher_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Controller_CrabHatcher.Controller_CrabHatcher_C.UpdateThreatNearby
struct AController_CrabHatcher_C_UpdateThreatNearby_Params
{
};

// Function Controller_CrabHatcher.Controller_CrabHatcher_C.UserConstructionScript
struct AController_CrabHatcher_C_UserConstructionScript_Params
{
};

// Function Controller_CrabHatcher.Controller_CrabHatcher_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_1_ActorPerceptionUpdatedDelegate__DelegateSignature
struct AController_CrabHatcher_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_1_ActorPerceptionUpdatedDelegate__DelegateSignature_Params
{
	class AActor*                                      Actor;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FAIStimulus                                 Stimulus;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Controller_CrabHatcher.Controller_CrabHatcher_C.TryRemovePlayer
struct AController_CrabHatcher_C_TryRemovePlayer_Params
{
	class AFGCharacterPlayer*                          inPlayer;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_CrabHatcher.Controller_CrabHatcher_C.TryAddPlayer
struct AController_CrabHatcher_C_TryAddPlayer_Params
{
	class AFGCharacterPlayer*                          inPlayer;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Controller_CrabHatcher.Controller_CrabHatcher_C.ExecuteUbergraph_Controller_CrabHatcher
struct AController_CrabHatcher_C_ExecuteUbergraph_Controller_CrabHatcher_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
