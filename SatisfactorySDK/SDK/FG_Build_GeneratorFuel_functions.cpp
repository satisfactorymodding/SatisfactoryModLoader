// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_GeneratorFuel_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_GeneratorFuel.Build_GeneratorFuel_C.UserConstructionScript
// ()

void ABuild_GeneratorFuel_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorFuel.Build_GeneratorFuel_C.UserConstructionScript");

	ABuild_GeneratorFuel_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorFuel.Build_GeneratorFuel_C.ReceiveUpdateEffects
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_GeneratorFuel_C::ReceiveUpdateEffects(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorFuel.Build_GeneratorFuel_C.ReceiveUpdateEffects");

	ABuild_GeneratorFuel_C_ReceiveUpdateEffects_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorFuel.Build_GeneratorFuel_C.GainedSignificance
// ()

void ABuild_GeneratorFuel_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorFuel.Build_GeneratorFuel_C.GainedSignificance");

	ABuild_GeneratorFuel_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorFuel.Build_GeneratorFuel_C.StartProductionLoopEffects
// ()

void ABuild_GeneratorFuel_C::StartProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorFuel.Build_GeneratorFuel_C.StartProductionLoopEffects");

	ABuild_GeneratorFuel_C_StartProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorFuel.Build_GeneratorFuel_C.StopProductionLoopEffects
// ()

void ABuild_GeneratorFuel_C::StopProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorFuel.Build_GeneratorFuel_C.StopProductionLoopEffects");

	ABuild_GeneratorFuel_C_StopProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorFuel.Build_GeneratorFuel_C.LostSignificance
// ()

void ABuild_GeneratorFuel_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorFuel.Build_GeneratorFuel_C.LostSignificance");

	ABuild_GeneratorFuel_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorFuel.Build_GeneratorFuel_C.ExecuteUbergraph_Build_GeneratorFuel
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_GeneratorFuel_C::ExecuteUbergraph_Build_GeneratorFuel(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorFuel.Build_GeneratorFuel_C.ExecuteUbergraph_Build_GeneratorFuel");

	ABuild_GeneratorFuel_C_ExecuteUbergraph_Build_GeneratorFuel_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
