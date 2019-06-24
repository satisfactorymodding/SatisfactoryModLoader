// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_OilPump_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_OilPump.Build_OilPump_C.GetExtractedResource
// ()
// Parameters:
// class UClass*                  Resource                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABuild_OilPump_C::GetExtractedResource(class UClass** Resource)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.GetExtractedResource");

	ABuild_OilPump_C_GetExtractedResource_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Resource != nullptr)
		*Resource = params.Resource;
}


// Function Build_OilPump.Build_OilPump_C.SetDisplayText
// ()
// Parameters:
// struct FText                   newText                        (BlueprintVisible, BlueprintReadOnly, Parm)

void ABuild_OilPump_C::SetDisplayText(const struct FText& newText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.SetDisplayText");

	ABuild_OilPump_C_SetDisplayText_Params params;
	params.newText = newText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.UserConstructionScript
// ()

void ABuild_OilPump_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.UserConstructionScript");

	ABuild_OilPump_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.StopIdlingLoopEffects
// ()

void ABuild_OilPump_C::StopIdlingLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.StopIdlingLoopEffects");

	ABuild_OilPump_C_StopIdlingLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.StopProductionLoopEffects
// ()

void ABuild_OilPump_C::StopProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.StopProductionLoopEffects");

	ABuild_OilPump_C_StopProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.LostSignificance
// ()

void ABuild_OilPump_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.LostSignificance");

	ABuild_OilPump_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.GainedSignificance
// ()

void ABuild_OilPump_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.GainedSignificance");

	ABuild_OilPump_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.StartIdlingLoopEffects
// ()

void ABuild_OilPump_C::StartIdlingLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.StartIdlingLoopEffects");

	ABuild_OilPump_C_StartIdlingLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.StartProductionLoopEffects
// ()

void ABuild_OilPump_C::StartProductionLoopEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.StartProductionLoopEffects");

	ABuild_OilPump_C_StartProductionLoopEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_OilPump.Build_OilPump_C.ExecuteUbergraph_Build_OilPump
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_OilPump_C::ExecuteUbergraph_Build_OilPump(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_OilPump.Build_OilPump_C.ExecuteUbergraph_Build_OilPump");

	ABuild_OilPump_C_ExecuteUbergraph_Build_OilPump_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
