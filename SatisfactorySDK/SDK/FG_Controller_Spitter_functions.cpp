// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Controller_Spitter_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Controller_Spitter.Controller_Spitter_C.UserConstructionScript
// ()

void AController_Spitter_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_Spitter.Controller_Spitter_C.UserConstructionScript");

	AController_Spitter_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_Spitter.Controller_Spitter_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature
// ()
// Parameters:
// class AActor*                  Actor                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FAIStimulus             Stimulus                       (BlueprintVisible, BlueprintReadOnly, Parm)

void AController_Spitter_C::BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature(class AActor* Actor, const struct FAIStimulus& Stimulus)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_Spitter.Controller_Spitter_C.BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature");

	AController_Spitter_C_BndEvt__PerceptionComponent_K2Node_ComponentBoundEvent_0_ActorPerceptionUpdatedDelegate__DelegateSignature_Params params;
	params.Actor = Actor;
	params.Stimulus = Stimulus;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Controller_Spitter.Controller_Spitter_C.ExecuteUbergraph_Controller_Spitter
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AController_Spitter_C::ExecuteUbergraph_Controller_Spitter(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Controller_Spitter.Controller_Spitter_C.ExecuteUbergraph_Controller_Spitter");

	AController_Spitter_C_ExecuteUbergraph_Controller_Spitter_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
