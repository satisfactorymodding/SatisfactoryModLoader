// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_SmelterMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_SmelterMk1.Build_SmelterMk1_C.SpawnProductionParticles
// ()

void ABuild_SmelterMk1_C::SpawnProductionParticles()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.SpawnProductionParticles");

	ABuild_SmelterMk1_C_SpawnProductionParticles_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.UserConstructionScript
// ()

void ABuild_SmelterMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.UserConstructionScript");

	ABuild_SmelterMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.LostSignificance
// ()

void ABuild_SmelterMk1_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.LostSignificance");

	ABuild_SmelterMk1_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.StartProductionLoopEffects
// ()

void ABuild_SmelterMk1_C::StartProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.StartProductionLoopEffects");

	ABuild_SmelterMk1_C_StartProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.StartIdlingLoopEffects
// ()

void ABuild_SmelterMk1_C::StartIdlingLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.StartIdlingLoopEffects");

	ABuild_SmelterMk1_C_StartIdlingLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.StopIdlingLoopEffects
// ()

void ABuild_SmelterMk1_C::StopIdlingLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.StopIdlingLoopEffects");

	ABuild_SmelterMk1_C_StopIdlingLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.StopProductionLoopEffects
// ()

void ABuild_SmelterMk1_C::StopProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.StopProductionLoopEffects");

	ABuild_SmelterMk1_C_StopProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.GainedSignificance
// ()

void ABuild_SmelterMk1_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.GainedSignificance");

	ABuild_SmelterMk1_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SmelterMk1.Build_SmelterMk1_C.ExecuteUbergraph_Build_SmelterMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_SmelterMk1_C::ExecuteUbergraph_Build_SmelterMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SmelterMk1.Build_SmelterMk1_C.ExecuteUbergraph_Build_SmelterMk1");

	ABuild_SmelterMk1_C_ExecuteUbergraph_Build_SmelterMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
