// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_CrabHatcher_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Controller_CrabHatcher.Controller_CrabHatcher_C.UpdateThreatNearby
// ()

void AController_CrabHatcher_C::UpdateThreatNearby()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_CrabHatcher.Controller_CrabHatcher_C.UpdateThreatNearby");

	AController_CrabHatcher_C_UpdateThreatNearby_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_CrabHatcher.Controller_CrabHatcher_C.UserConstructionScript
// ()

void AController_CrabHatcher_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_CrabHatcher.Controller_CrabHatcher_C.UserConstructionScript");

	AController_CrabHatcher_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_CrabHatcher.Controller_CrabHatcher_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_1_ActorPerceptionUpdatedDelegate__DelegateSignature
// ()
// Parameters:
// class AActor*                  Actor                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FAIStimulus             Stimulus                       (BlueprintVisible, BlueprintReadOnly, Parm)

void AController_CrabHatcher_C::BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_1_ActorPerceptionUpdatedDelegate__DelegateSignature(class AActor* Actor, const struct FAIStimulus& Stimulus)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_CrabHatcher.Controller_CrabHatcher_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_1_ActorPerceptionUpdatedDelegate__DelegateSignature");

	AController_CrabHatcher_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_1_ActorPerceptionUpdatedDelegate__DelegateSignature_Params params;
	params.Actor = Actor;
	params.Stimulus = Stimulus;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_CrabHatcher.Controller_CrabHatcher_C.TryRemovePlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      inPlayer                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_CrabHatcher_C::TryRemovePlayer(class AFGCharacterPlayer* inPlayer)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_CrabHatcher.Controller_CrabHatcher_C.TryRemovePlayer");

	AController_CrabHatcher_C_TryRemovePlayer_Params params;
	params.inPlayer = inPlayer;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_CrabHatcher.Controller_CrabHatcher_C.TryAddPlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      inPlayer                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_CrabHatcher_C::TryAddPlayer(class AFGCharacterPlayer* inPlayer)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_CrabHatcher.Controller_CrabHatcher_C.TryAddPlayer");

	AController_CrabHatcher_C_TryAddPlayer_Params params;
	params.inPlayer = inPlayer;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_CrabHatcher.Controller_CrabHatcher_C.ExecuteUbergraph_Controller_CrabHatcher
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_CrabHatcher_C::ExecuteUbergraph_Controller_CrabHatcher(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_CrabHatcher.Controller_CrabHatcher_C.ExecuteUbergraph_Controller_CrabHatcher");

	AController_CrabHatcher_C_ExecuteUbergraph_Controller_CrabHatcher_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
