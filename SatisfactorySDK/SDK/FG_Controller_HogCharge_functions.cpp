// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_HogCharge_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Controller_HogCharge.Controller_HogCharge_C.UserConstructionScript
// ()

void AController_HogCharge_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_HogCharge.Controller_HogCharge_C.UserConstructionScript");

	AController_HogCharge_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_HogCharge.Controller_HogCharge_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_2_ActorPerceptionUpdatedDelegate__DelegateSignature
// ()
// Parameters:
// class AActor*                  Actor                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FAIStimulus             Stimulus                       (BlueprintVisible, BlueprintReadOnly, Parm)

void AController_HogCharge_C::BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_2_ActorPerceptionUpdatedDelegate__DelegateSignature(class AActor* Actor, const struct FAIStimulus& Stimulus)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_HogCharge.Controller_HogCharge_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_2_ActorPerceptionUpdatedDelegate__DelegateSignature");

	AController_HogCharge_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_2_ActorPerceptionUpdatedDelegate__DelegateSignature_Params params;
	params.Actor = Actor;
	params.Stimulus = Stimulus;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_HogCharge.Controller_HogCharge_C.StartPanic
// ()

void AController_HogCharge_C::StartPanic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_HogCharge.Controller_HogCharge_C.StartPanic");

	AController_HogCharge_C_StartPanic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_HogCharge.Controller_HogCharge_C.ExecuteUbergraph_Controller_HogCharge
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_HogCharge_C::ExecuteUbergraph_Controller_HogCharge(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_HogCharge.Controller_HogCharge_C.ExecuteUbergraph_Controller_HogCharge");

	AController_HogCharge_C_ExecuteUbergraph_Controller_HogCharge_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
