// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CostEffectActor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_CostEffectActor.BP_CostEffectActor_C.UserConstructionScript
// ()

void ABP_CostEffectActor_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CostEffectActor.BP_CostEffectActor_C.UserConstructionScript");

	ABP_CostEffectActor_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CostEffectActor.BP_CostEffectActor_C.ReceiveBeginPlay
// ()

void ABP_CostEffectActor_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CostEffectActor.BP_CostEffectActor_C.ReceiveBeginPlay");

	ABP_CostEffectActor_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CostEffectActor.BP_CostEffectActor_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CostEffectActor_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CostEffectActor.BP_CostEffectActor_C.ReceiveTick");

	ABP_CostEffectActor_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CostEffectActor.BP_CostEffectActor_C.ExecuteUbergraph_BP_CostEffectActor
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CostEffectActor_C::ExecuteUbergraph_BP_CostEffectActor(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CostEffectActor.BP_CostEffectActor_C.ExecuteUbergraph_BP_CostEffectActor");

	ABP_CostEffectActor_C_ExecuteUbergraph_BP_CostEffectActor_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CostEffectActor.BP_CostEffectActor_C.OnReachedTarget__DelegateSignature
// ()

void ABP_CostEffectActor_C::OnReachedTarget__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CostEffectActor.BP_CostEffectActor_C.OnReachedTarget__DelegateSignature");

	ABP_CostEffectActor_C_OnReachedTarget__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
