// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_NonFlyingBird_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.UserConstructionScript
// ()

void AController_NonFlyingBird_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.UserConstructionScript");

	AController_NonFlyingBird_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.OnPossess
// ()
// Parameters:
// class APawn**                  PossessedPawn                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_NonFlyingBird_C::OnPossess(class APawn** PossessedPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.OnPossess");

	AController_NonFlyingBird_C_OnPossess_Params params;
	params.PossessedPawn = PossessedPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.TryToJump
// ()

void AController_NonFlyingBird_C::TryToJump()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.TryToJump");

	AController_NonFlyingBird_C_TryToJump_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature
// ()
// Parameters:
// class AActor*                  Actor                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FAIStimulus             Stimulus                       (BlueprintVisible, BlueprintReadOnly, Parm)

void AController_NonFlyingBird_C::BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature(class AActor* Actor, const struct FAIStimulus& Stimulus)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature");

	AController_NonFlyingBird_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature_Params params;
	params.Actor = Actor;
	params.Stimulus = Stimulus;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.StartPanic
// ()

void AController_NonFlyingBird_C::StartPanic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.StartPanic");

	AController_NonFlyingBird_C_StartPanic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.ExecuteUbergraph_Controller_NonFlyingBird
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_NonFlyingBird_C::ExecuteUbergraph_Controller_NonFlyingBird(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_NonFlyingBird.Controller_NonFlyingBird_C.ExecuteUbergraph_Controller_NonFlyingBird");

	AController_NonFlyingBird_C_ExecuteUbergraph_Controller_NonFlyingBird_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
