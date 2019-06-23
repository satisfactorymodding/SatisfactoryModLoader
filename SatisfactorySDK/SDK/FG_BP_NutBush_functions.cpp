// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_NutBush_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_NutBush.BP_NutBush_C.GetDestroyAudioEvent
// ()
// Parameters:
// class UAkAudioEvent*           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UAkAudioEvent* ABP_NutBush_C::GetDestroyAudioEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NutBush.BP_NutBush_C.GetDestroyAudioEvent");

	ABP_NutBush_C_GetDestroyAudioEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_NutBush.BP_NutBush_C.GetDestroyEffect
// ()
// Parameters:
// class UParticleSystem*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UParticleSystem* ABP_NutBush_C::GetDestroyEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NutBush.BP_NutBush_C.GetDestroyEffect");

	ABP_NutBush_C_GetDestroyEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_NutBush.BP_NutBush_C.GetForceThreshold
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_NutBush_C::GetForceThreshold()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NutBush.BP_NutBush_C.GetForceThreshold");

	ABP_NutBush_C_GetForceThreshold_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_NutBush.BP_NutBush_C.GetMeshComponent
// ()
// Parameters:
// class UStaticMeshComponent*    ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UStaticMeshComponent* ABP_NutBush_C::GetMeshComponent()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NutBush.BP_NutBush_C.GetMeshComponent");

	ABP_NutBush_C_GetMeshComponent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_NutBush.BP_NutBush_C.IsChainsawable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_NutBush_C::IsChainsawable()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NutBush.BP_NutBush_C.IsChainsawable");

	ABP_NutBush_C_IsChainsawable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_NutBush.BP_NutBush_C.UserConstructionScript
// ()

void ABP_NutBush_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NutBush.BP_NutBush_C.UserConstructionScript");

	ABP_NutBush_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
