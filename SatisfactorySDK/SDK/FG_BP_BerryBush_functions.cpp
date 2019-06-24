// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BerryBush_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_BerryBush.BP_BerryBush_C.GetDestroyAudioEvent
// ()
// Parameters:
// class UAkAudioEvent*           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UAkAudioEvent* ABP_BerryBush_C::GetDestroyAudioEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BerryBush.BP_BerryBush_C.GetDestroyAudioEvent");

	ABP_BerryBush_C_GetDestroyAudioEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_BerryBush.BP_BerryBush_C.GetDestroyEffect
// ()
// Parameters:
// class UParticleSystem*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UParticleSystem* ABP_BerryBush_C::GetDestroyEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BerryBush.BP_BerryBush_C.GetDestroyEffect");

	ABP_BerryBush_C_GetDestroyEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_BerryBush.BP_BerryBush_C.GetForceThreshold
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_BerryBush_C::GetForceThreshold()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BerryBush.BP_BerryBush_C.GetForceThreshold");

	ABP_BerryBush_C_GetForceThreshold_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_BerryBush.BP_BerryBush_C.GetMeshComponent
// ()
// Parameters:
// class UStaticMeshComponent*    ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UStaticMeshComponent* ABP_BerryBush_C::GetMeshComponent()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BerryBush.BP_BerryBush_C.GetMeshComponent");

	ABP_BerryBush_C_GetMeshComponent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_BerryBush.BP_BerryBush_C.IsChainsawable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_BerryBush_C::IsChainsawable()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BerryBush.BP_BerryBush_C.IsChainsawable");

	ABP_BerryBush_C_IsChainsawable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_BerryBush.BP_BerryBush_C.UserConstructionScript
// ()

void ABP_BerryBush_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BerryBush.BP_BerryBush_C.UserConstructionScript");

	ABP_BerryBush_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
