// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_CrabEggParts_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_CrabEggParts.BP_CrabEggParts_C.UserConstructionScript
// ()

void ABP_CrabEggParts_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CrabEggParts.BP_CrabEggParts_C.UserConstructionScript");

	ABP_CrabEggParts_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CrabEggParts.BP_CrabEggParts_C.ReceiveBeginPlay
// ()

void ABP_CrabEggParts_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CrabEggParts.BP_CrabEggParts_C.ReceiveBeginPlay");

	ABP_CrabEggParts_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CrabEggParts.BP_CrabEggParts_C.ExecuteUbergraph_BP_CrabEggParts
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CrabEggParts_C::ExecuteUbergraph_BP_CrabEggParts(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CrabEggParts.BP_CrabEggParts_C.ExecuteUbergraph_BP_CrabEggParts");

	ABP_CrabEggParts_C_ExecuteUbergraph_BP_CrabEggParts_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
