// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Manta_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Manta.BP_Manta_C.UserConstructionScript
// ()

void ABP_Manta_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.UserConstructionScript");

	ABP_Manta_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.GainedSignificance
// ()

void ABP_Manta_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.GainedSignificance");

	ABP_Manta_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.LostSignificance
// ()

void ABP_Manta_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.LostSignificance");

	ABP_Manta_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.ExecuteUbergraph_BP_Manta
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Manta_C::ExecuteUbergraph_BP_Manta(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.ExecuteUbergraph_BP_Manta");

	ABP_Manta_C_ExecuteUbergraph_BP_Manta_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
