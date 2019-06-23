// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_OilRefinery_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_OilRefinery.Build_OilRefinery_C.UserConstructionScript
// ()

void ABuild_OilRefinery_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.UserConstructionScript");

	ABuild_OilRefinery_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilRefinery.Build_OilRefinery_C.StartIdlingLoopEffects
// ()

void ABuild_OilRefinery_C::StartIdlingLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.StartIdlingLoopEffects");

	ABuild_OilRefinery_C_StartIdlingLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilRefinery.Build_OilRefinery_C.StopIdlingLoopEffects
// ()

void ABuild_OilRefinery_C::StopIdlingLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.StopIdlingLoopEffects");

	ABuild_OilRefinery_C_StopIdlingLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilRefinery.Build_OilRefinery_C.StartProductionLoopEffects
// ()

void ABuild_OilRefinery_C::StartProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.StartProductionLoopEffects");

	ABuild_OilRefinery_C_StartProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilRefinery.Build_OilRefinery_C.StopProductionLoopEffects
// ()

void ABuild_OilRefinery_C::StopProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.StopProductionLoopEffects");

	ABuild_OilRefinery_C_StopProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilRefinery.Build_OilRefinery_C.GainedSignificance
// ()

void ABuild_OilRefinery_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.GainedSignificance");

	ABuild_OilRefinery_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilRefinery.Build_OilRefinery_C.LostSignificance
// ()

void ABuild_OilRefinery_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.LostSignificance");

	ABuild_OilRefinery_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilRefinery.Build_OilRefinery_C.ExecuteUbergraph_Build_OilRefinery
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_OilRefinery_C::ExecuteUbergraph_Build_OilRefinery(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilRefinery.Build_OilRefinery_C.ExecuteUbergraph_Build_OilRefinery");

	ABuild_OilRefinery_C_ExecuteUbergraph_Build_OilRefinery_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
