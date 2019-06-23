// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SplinedParticles_01_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.SpawnAnts
// ()

void ABP_SplinedParticles_01_C::SpawnAnts()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.SpawnAnts");

	ABP_SplinedParticles_01_C_SpawnAnts_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.UserConstructionScript
// ()

void ABP_SplinedParticles_01_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.UserConstructionScript");

	ABP_SplinedParticles_01_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ReceiveBeginPlay
// ()

void ABP_SplinedParticles_01_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ReceiveBeginPlay");

	ABP_SplinedParticles_01_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SplinedParticles_01_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ReceiveTick");

	ABP_SplinedParticles_01_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ExecuteUbergraph_BP_SplinedParticles_01
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SplinedParticles_01_C::ExecuteUbergraph_BP_SplinedParticles_01(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SplinedParticles_01.BP_SplinedParticles_01_C.ExecuteUbergraph_BP_SplinedParticles_01");

	ABP_SplinedParticles_01_C_ExecuteUbergraph_BP_SplinedParticles_01_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
