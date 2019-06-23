// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_GeneratorCoal_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_GeneratorCoal.Build_GeneratorCoal_C.UserConstructionScript
// ()

void ABuild_GeneratorCoal_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorCoal.Build_GeneratorCoal_C.UserConstructionScript");

	ABuild_GeneratorCoal_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorCoal.Build_GeneratorCoal_C.GainedSignificance
// ()

void ABuild_GeneratorCoal_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorCoal.Build_GeneratorCoal_C.GainedSignificance");

	ABuild_GeneratorCoal_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorCoal.Build_GeneratorCoal_C.StartProductionLoopEffects
// ()

void ABuild_GeneratorCoal_C::StartProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorCoal.Build_GeneratorCoal_C.StartProductionLoopEffects");

	ABuild_GeneratorCoal_C_StartProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorCoal.Build_GeneratorCoal_C.StopProductionLoopEffects
// ()

void ABuild_GeneratorCoal_C::StopProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorCoal.Build_GeneratorCoal_C.StopProductionLoopEffects");

	ABuild_GeneratorCoal_C_StopProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorCoal.Build_GeneratorCoal_C.LostSignificance
// ()

void ABuild_GeneratorCoal_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorCoal.Build_GeneratorCoal_C.LostSignificance");

	ABuild_GeneratorCoal_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_GeneratorCoal.Build_GeneratorCoal_C.ExecuteUbergraph_Build_GeneratorCoal
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_GeneratorCoal_C::ExecuteUbergraph_Build_GeneratorCoal(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_GeneratorCoal.Build_GeneratorCoal_C.ExecuteUbergraph_Build_GeneratorCoal");

	ABuild_GeneratorCoal_C_ExecuteUbergraph_Build_GeneratorCoal_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
