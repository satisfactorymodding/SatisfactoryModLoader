// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_MinerMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_MinerMk1.Build_MinerMk1_C.GetExtractedResource
// ()
// Parameters:
// class UClass*                  Resource                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABuild_MinerMk1_C::GetExtractedResource(class UClass** Resource)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.GetExtractedResource");

	ABuild_MinerMk1_C_GetExtractedResource_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Resource != nullptr)
		*Resource = params.Resource;
}


// Function Build_MinerMk1.Build_MinerMk1_C.GetMiningParticles
// ()
// Parameters:
// class UParticleSystem*         FirstParticle                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// class UParticleSystem*         SecondParticle                 (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// bool                           foundParticle                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABuild_MinerMk1_C::GetMiningParticles(class UParticleSystem** FirstParticle, class UParticleSystem** SecondParticle, bool* foundParticle)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.GetMiningParticles");

	ABuild_MinerMk1_C_GetMiningParticles_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (FirstParticle != nullptr)
		*FirstParticle = params.FirstParticle;
	if (SecondParticle != nullptr)
		*SecondParticle = params.SecondParticle;
	if (foundParticle != nullptr)
		*foundParticle = params.foundParticle;
}


// Function Build_MinerMk1.Build_MinerMk1_C.UserConstructionScript
// ()

void ABuild_MinerMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.UserConstructionScript");

	ABuild_MinerMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk1.Build_MinerMk1_C.GainedSignificance
// ()

void ABuild_MinerMk1_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.GainedSignificance");

	ABuild_MinerMk1_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk1.Build_MinerMk1_C.StartProductionLoopEffects
// ()

void ABuild_MinerMk1_C::StartProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.StartProductionLoopEffects");

	ABuild_MinerMk1_C_StartProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk1.Build_MinerMk1_C.StopProductionLoopEffects
// ()

void ABuild_MinerMk1_C::StopProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.StopProductionLoopEffects");

	ABuild_MinerMk1_C_StopProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk1.Build_MinerMk1_C.LostSignificance
// ()

void ABuild_MinerMk1_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.LostSignificance");

	ABuild_MinerMk1_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk1.Build_MinerMk1_C.ReceiveDestroyed
// ()

void ABuild_MinerMk1_C::ReceiveDestroyed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.ReceiveDestroyed");

	ABuild_MinerMk1_C_ReceiveDestroyed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk1.Build_MinerMk1_C.ExecuteUbergraph_Build_MinerMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_MinerMk1_C::ExecuteUbergraph_Build_MinerMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk1.Build_MinerMk1_C.ExecuteUbergraph_Build_MinerMk1");

	ABuild_MinerMk1_C_ExecuteUbergraph_Build_MinerMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
