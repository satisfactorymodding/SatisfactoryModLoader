// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Shroom_01_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Shroom_01.BP_Shroom_01_C.GetDestroyAudioEvent
// ()
// Parameters:
// class UAkAudioEvent*           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UAkAudioEvent* ABP_Shroom_01_C::GetDestroyAudioEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Shroom_01.BP_Shroom_01_C.GetDestroyAudioEvent");

	ABP_Shroom_01_C_GetDestroyAudioEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Shroom_01.BP_Shroom_01_C.GetDestroyEffect
// ()
// Parameters:
// class UParticleSystem*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UParticleSystem* ABP_Shroom_01_C::GetDestroyEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Shroom_01.BP_Shroom_01_C.GetDestroyEffect");

	ABP_Shroom_01_C_GetDestroyEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Shroom_01.BP_Shroom_01_C.GetForceThreshold
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_Shroom_01_C::GetForceThreshold()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Shroom_01.BP_Shroom_01_C.GetForceThreshold");

	ABP_Shroom_01_C_GetForceThreshold_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Shroom_01.BP_Shroom_01_C.UserConstructionScript
// ()

void ABP_Shroom_01_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Shroom_01.BP_Shroom_01_C.UserConstructionScript");

	ABP_Shroom_01_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
