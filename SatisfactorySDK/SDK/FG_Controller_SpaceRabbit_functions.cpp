// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_SpaceRabbit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.isThreat
// ()
// Parameters:
// struct FName                   inTag                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           isThreat                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void AController_SpaceRabbit_C::isThreat(const struct FName& inTag, bool* isThreat)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.isThreat");

	AController_SpaceRabbit_C_isThreat_Params params;
	params.inTag = inTag;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (isThreat != nullptr)
		*isThreat = params.isThreat;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.ReactToSound
// ()
// Parameters:
// class AActor*                  inActor                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 soundLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   Tag                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           didReact                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void AController_SpaceRabbit_C::ReactToSound(class AActor* inActor, const struct FVector& soundLocation, const struct FName& Tag, bool* didReact)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.ReactToSound");

	AController_SpaceRabbit_C_ReactToSound_Params params;
	params.inActor = inActor;
	params.soundLocation = soundLocation;
	params.Tag = Tag;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (didReact != nullptr)
		*didReact = params.didReact;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.SetNewThreat
// ()
// Parameters:
// class AFGCharacterPlayer*      newThreat                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_SpaceRabbit_C::SetNewThreat(class AFGCharacterPlayer* newThreat)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.SetNewThreat");

	AController_SpaceRabbit_C_SetNewThreat_Params params;
	params.newThreat = newThreat;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.GetCurrentThreat
// ()
// Parameters:
// class AFGCharacterPlayer*      outThreat                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void AController_SpaceRabbit_C::GetCurrentThreat(class AFGCharacterPlayer** outThreat)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.GetCurrentThreat");

	AController_SpaceRabbit_C_GetCurrentThreat_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (outThreat != nullptr)
		*outThreat = params.outThreat;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.UserConstructionScript
// ()

void AController_SpaceRabbit_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.UserConstructionScript");

	AController_SpaceRabbit_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.OnPossess
// ()
// Parameters:
// class APawn**                  PossessedPawn                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_SpaceRabbit_C::OnPossess(class APawn** PossessedPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.OnPossess");

	AController_SpaceRabbit_C_OnPossess_Params params;
	params.PossessedPawn = PossessedPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature
// ()
// Parameters:
// class AActor*                  Actor                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FAIStimulus             Stimulus                       (BlueprintVisible, BlueprintReadOnly, Parm)

void AController_SpaceRabbit_C::BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature(class AActor* Actor, const struct FAIStimulus& Stimulus)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature");

	AController_SpaceRabbit_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature_Params params;
	params.Actor = Actor;
	params.Stimulus = Stimulus;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.StartPanic
// ()

void AController_SpaceRabbit_C::StartPanic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.StartPanic");

	AController_SpaceRabbit_C_StartPanic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.ExecuteUbergraph_Controller_SpaceRabbit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_SpaceRabbit_C::ExecuteUbergraph_Controller_SpaceRabbit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_SpaceRabbit.Controller_SpaceRabbit_C.ExecuteUbergraph_Controller_SpaceRabbit");

	AController_SpaceRabbit_C_ExecuteUbergraph_Controller_SpaceRabbit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
